/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Longda on 2021/4/13.
//

#include <string>
#include <sstream>

#include "execute_stage.h"

#include "common/io/io.h"
#include "common/log/log.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "event/execution_plan_event.h"
#include "sql/executor/execution_node.h"
#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"

using namespace common;

RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node);

RC table_Join_execute(TupleSet &table1, TupleSet &table2, const Selects &selects, TupleSet &result_tupleSet);
bool filter_tuple(const std::shared_ptr<TupleValue> &values1, const std::shared_ptr<TupleValue> values2, CompOp op);
TupleSet get_final_result(const Selects &selects, TupleSet &full_tupleSet);

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag) {}

//! Destructor
ExecuteStage::~ExecuteStage() {}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag) {
  ExecuteStage *stage = new (std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties() {
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize() {
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event) {
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context) {
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SQLStageEvent *sql_event = exe_event->sql_event();
  sql_event->done_immediate();

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event) {
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SessionEvent *session_event = exe_event->sql_event()->session_event();
  Query *sql = exe_event->sqls();
  const char *current_db = session_event->get_client()->session->get_current_db().c_str();

  CompletionCallback *cb = new (std::nothrow) CompletionCallback(this, nullptr);
  if (cb == nullptr) {
    LOG_ERROR("Failed to new callback for ExecutionPlanEvent");
    exe_event->done_immediate();
    return;
  }
  exe_event->push_callback(cb);

  switch (sql->flag) {
    case SCF_SELECT: { // select
      RC rc = RC::SUCCESS;
      char response[256];
      rc = do_select(current_db, sql, exe_event->sql_event()->session_event());
      if(rc != RC::SUCCESS){
        snprintf(response, sizeof(response), "%s\n", "FAILURE");
        session_event->set_response(response);
      }
      exe_event->done_immediate();
    }
    break;

    case SCF_INSERT:
    case SCF_UPDATE:
    case SCF_DELETE:
    case SCF_CREATE_TABLE:
    case SCF_SHOW_TABLES:
    case SCF_DESC_TABLE:
    case SCF_DROP_TABLE:
    case SCF_CREATE_INDEX:
    case SCF_CREATE_UNIQUE_INDEX:
    case SCF_DROP_INDEX: 
    case SCF_LOAD_DATA: {
      StorageEvent *storage_event = new (std::nothrow) StorageEvent(exe_event);
      if (storage_event == nullptr) {
        LOG_ERROR("Failed to new StorageEvent");
        event->done_immediate();
        return;
      }

      default_storage_stage_->handle_event(storage_event);
    }
    break;
    case SCF_SYNC: {
      RC rc = DefaultHandler::get_default().sync();
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_BEGIN: {
      session_event->get_client()->session->set_trx_multi_operation_mode(true);
      session_event->set_response(strrc(RC::SUCCESS));
      exe_event->done_immediate();
    }
    break;
    case SCF_COMMIT: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->commit();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_ROLLBACK: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->rollback();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_HELP: {
      const char *response = "show tables;\n"
          "desc `table name`;\n"
          "create table `table name` (`column name` `column type`, ...);\n"
          "create index `index name` on `table` (`column`);\n"
          "insert into `table` values(`value1`,`value2`);\n"
          "update `table` set column=value [where `column`=`value`];\n"
          "delete from `table` [where `column`=`value`];\n"
          "select [ * | `columns` ] from `table`;\n";
      session_event->set_response(response);
      exe_event->done_immediate();
    }
    break;
    case SCF_EXIT: {
      // do nothing
      const char *response = "Unsupported\n";
      session_event->set_response(response);
      exe_event->done_immediate();
    }
    break;
    default: {
      exe_event->done_immediate();
      LOG_ERROR("Unsupported command=%d\n", sql->flag);
    }
  }
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right) {
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
}

// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分. 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Selects &selects = sql->sstr.selection;
  // 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
  std::vector<SelectExeNode *> select_nodes;
  for (size_t i = 0; i < selects.relation_num; i++) {
    const char *table_name = selects.relations[i];
    SelectExeNode *select_node = new SelectExeNode;
    rc = create_selection_executor(trx, selects, db, table_name, *select_node);

    if (rc != RC::SUCCESS) {
      delete select_node;
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    }
    select_nodes.push_back(select_node);
  }

  if (select_nodes.empty()) {
    LOG_ERROR("No table given");
    end_trx_if_need(session, trx, false);
    return RC::SQL_SYNTAX;
  }

  std::vector<TupleSet> tuple_sets;
  for (SelectExeNode *&node: select_nodes) {
    TupleSet tuple_set;
    rc = node->execute(tuple_set);
    if (rc != RC::SUCCESS) {
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }

  for (SelectExeNode *& tmp_node: select_nodes) {
    // 此处对tuple_sets进行处理，更新返回的内容
    if (selects.poly_num > 0){
      std::cout <<  "poly_num:  " << selects.poly_num << std::endl;
      std::stringstream ss;
      if (tuple_sets.size() > 1) {
        // 本次查询了多张表，需要做join操作
      } else {
        // 当前只查询一张表，直接返回结果即可
        std::cout << "0-print" << std::endl;
        tuple_sets.front().print_poly_new(ss,selects);
        std::cout << "1-print" << std::endl;
        // tuple_sets.front().schema().print(ss);
      }
    for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
    }
    // std::cout << ss.str() << std::endl;
    session_event->set_response(ss.str());
    end_trx_if_need(session, trx, true);
    return rc;
    }else{
      std::stringstream ss;
      if (tuple_sets.size() > 1) { //这时候取到的数据是所有过滤掉单表限制的 tuple
        TupleSet join_result_tupleSet, result_tupleSet;
        // 本次查询了多张表，需要做join操作
        for(int i = tuple_sets.size() - 1; i >= 0; i--){
          if(i == tuple_sets.size() - 1){
              rc = table_Join_execute(tuple_sets[i], tuple_sets[i - 1], selects, join_result_tupleSet);
              i--;
          }else{
              rc = table_Join_execute(join_result_tupleSet, tuple_sets[i], selects, join_result_tupleSet);
          }
          if(rc != RC::SUCCESS) {
            std::cout << "join failure" << std::endl;
            return rc;
          }
        }
        result_tupleSet = get_final_result(selects, join_result_tupleSet);
        result_tupleSet.print(ss, true);
      } else {
          // 当前只查询一张表，直接返回结果即可
          tuple_sets.front().print(ss, false);
      }
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      session_event->set_response(ss.str());
      end_trx_if_need(session, trx, true);
      return rc;
    }
  }
}


bool match_table(const Selects &selects, const char *table_name_in_condition, const char *table_name_to_match) {
  if (table_name_in_condition != nullptr) {
    return 0 == strcmp(table_name_in_condition, table_name_to_match);
  }

  return selects.relation_num == 1;
}

static RC schema_add_field(Table *table, const char *field_name, TupleSchema &schema) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }

  schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name());
  return RC::SUCCESS;
}

// 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node) {
  // 列出跟这张表关联的Attr
  TupleSchema schema;
  Table * table = DefaultHandler::get_default().find_table(db, table_name);
  if (nullptr == table) {
    LOG_WARN("No such table [%s] in db [%s]", table_name, db);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  if(selects.relation_num == 1){
    for (int i = selects.attr_num - 1; i >= 0; i--) {
      const RelAttr &attr = selects.attributes[i];
      if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
        if (0 == strcmp("*", attr.attribute_name)) {
          // 列出这张表所有字段
          TupleSchema::from_table(table, schema);
          break; // 没有校验，给出* 之后，再写字段的错误
        } else {
          // 列出这张表相关字段
          RC rc = schema_add_field(table, attr.attribute_name, schema);
          if (rc != RC::SUCCESS) {
            return rc;
          }
        }
      }
    }
  }else if(selects.relation_num > 1){   //多张表，先取出所有record到内存，同时过滤掉单个表的限定条件，再对所有tuple做join
    TupleSchema tmpschema;
    for (int i = selects.attr_num - 1; i >= 0; i--) {
      const RelAttr &attr = selects.attributes[i];
      if(attr.relation_name != nullptr){
        int isContain = 0;
        for (int j = selects.relation_num - 1; j >= 0; j--){
          if(0 == strcmp(attr.relation_name, selects.relations[j])) {
            isContain = 1;
            break;
          }
        }
        if (isContain == 0) {
          std::cout << "select no in selects.relations table" << std::endl;
          return RC::SCHEMA_TABLE_NOT_EXIST;
        }
      }
      if(0 != strcmp("*", attr.attribute_name) && 0 == strcmp(table_name, attr.relation_name)){
        RC rc = schema_add_field(table, attr.attribute_name, tmpschema);
        if (rc != RC::SUCCESS) {
          std::cout << "select no exit " <<  std::string(attr.relation_name) << "." << std::string(attr.attribute_name) << std::endl;
          return rc;
        } 
      } 
    }
    for (int i = selects.condition_num - 1; i >= 0; i--) {
      const Condition &attr = selects.conditions[i];
      if(attr.left_is_attr == 1){
        int isContain = 0;
        for (int j = selects.relation_num - 1; j >= 0; j--){
          if(0 == strcmp(attr.left_attr.relation_name, selects.relations[j])) {
            isContain = 1;
            break;
          }
        }
        if (isContain == 0) {
          std::cout << "condition no in selects.relations table" << std::endl;
          return RC::SCHEMA_TABLE_NOT_EXIST;
        }
        if(0 == strcmp(table_name, attr.left_attr.relation_name)){
          RC rc = schema_add_field(table, attr.left_attr.attribute_name, tmpschema);
          if (rc != RC::SUCCESS) {
            std::cout << "condition no exit " <<  std::string(attr.left_attr.relation_name) << "." << std::string(attr.left_attr.attribute_name) << std::endl;
            return rc;
          } 
        }         
      }
      if(attr.right_is_attr == 1){
        int isContain = 0;
        for (int j = selects.relation_num - 1; j >= 0; j--){
          if(0 == strcmp(attr.right_attr.relation_name, selects.relations[j])) {
            isContain = 1;
            break;
          }
        }
        if (isContain == 0) {
          std::cout << "condition no in selects.relations table" << std::endl;
          return RC::SCHEMA_TABLE_NOT_EXIST;
        }
        if(0 == strcmp(table_name, attr.right_attr.relation_name)){
          RC rc = schema_add_field(table, attr.right_attr.attribute_name, tmpschema);
          if (rc != RC::SUCCESS) {
            std::cout << "condition no exit " <<  std::string(attr.right_attr.relation_name) << "." << std::string(attr.right_attr.attribute_name) << std::endl;
            return rc;
          } 
        } 
      }
    }       

    TupleSchema::from_table(table, schema);
  }

  // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
  std::vector<DefaultConditionFilter *> condition_filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    if ((condition.left_is_attr == 0 && condition.right_is_attr == 0) || // 两边都是值
        (condition.left_is_attr == 1 && condition.right_is_attr == 0 && match_table(selects, condition.left_attr.relation_name, table_name)) ||  // 左边是属性右边是值
        (condition.left_is_attr == 0 && condition.right_is_attr == 1 && match_table(selects, condition.right_attr.relation_name, table_name)) ||  // 左边是值，右边是属性名
        (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
            match_table(selects, condition.left_attr.relation_name, table_name) && match_table(selects, condition.right_attr.relation_name, table_name)) // 左右都是属性名，并且表名都符合
        ) {
      DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
      RC rc = condition_filter->init(*table, condition);
      if (rc != RC::SUCCESS) {
        delete condition_filter;
        for (DefaultConditionFilter * &filter : condition_filters) {
          delete filter;
        }
        return rc;
      }
      condition_filters.push_back(condition_filter);
    }
  }

  return select_node.init(trx, table, std::move(schema), std::move(condition_filters));
}

RC table_Join_execute(TupleSet &table1, TupleSet &table2, const Selects &selects, TupleSet &result_tupleSet){
  int flag = 1; //如果没有过滤条件，就全量
  //合并两个内外表的 Schema
  TupleSchema  schema = table1.get_schema();
  schema.append(table2.get_schema());

  result_tupleSet.set_schema(schema);
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    if((condition.left_is_attr == 1 && condition.right_is_attr == 1)){
      std::cout << "compare " + std::string(condition.left_attr.relation_name) + "." + std::string(condition.left_attr.attribute_name);
      std::cout << " = " + std::string(condition.right_attr.relation_name) + "." + std::string(condition.right_attr.attribute_name) << std::endl;
      int tuple1_index = table1.get_schema().index_of_field(condition.left_attr.relation_name, condition.left_attr.attribute_name);
      int tuple2_index = table2.get_schema().index_of_field(condition.right_attr.relation_name, condition.right_attr.attribute_name);
      //例如 t1.id = t2.id 的情况 如果不存在就试 t2.id = t1.id
      if(tuple1_index < 0 || tuple2_index < 0){
        tuple2_index = table2.get_schema().index_of_field(condition.left_attr.relation_name, condition.left_attr.attribute_name);
        tuple1_index = table1.get_schema().index_of_field(condition.right_attr.relation_name, condition.right_attr.attribute_name);
      }
      std::cout << tuple1_index << "+" << tuple2_index << std::endl;
      if(tuple1_index > -1 && tuple2_index > -1){
        std::cout << "compare success" << std::endl;
        TupleField tuple1_field = table1.get_schema().field(tuple1_index);
        TupleField tuple2_field = table2.get_schema().field(tuple2_index);
        if(tuple1_field.type() != tuple2_field.type()) return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        flag = 0;
        //比较两个 tuple 
        int table1_size = table1.size();
        int table2_size = table2.size();
        for(size_t table1_ite = 0; table1_ite < table1_size; table1_ite++){
          for(size_t table2_ite = 0; table2_ite < table2_size; table2_ite++){
            const std::vector<std::shared_ptr<TupleValue>> &values1 = table1.get(table1_ite).values();
            const std::vector<std::shared_ptr<TupleValue>> &values2 = table2.get(table2_ite).values();
            if(filter_tuple(values1[tuple1_index], values2[tuple2_index], condition.comp)){
                Tuple new_tuple;
                for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values1.begin(), end = values1.end();
                  iter != end; ++iter){
                    new_tuple.add(*iter);
                }
                for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values2.begin(), end = values2.end();
                  iter != end; ++iter){
                    new_tuple.add(*iter);
                }
                //合并插入新的 tupleset
                result_tupleSet.add(std::move(new_tuple));
            }
          }
        }
      }
    }
  }
  if (flag) {  //没有筛选条件，全量笛卡尔积
    int table1_size = table1.size();
    int table2_size = table2.size();
    for(size_t table1_ite = 0; table1_ite < table1_size; table1_ite++){
      for(size_t table2_ite = 0; table2_ite < table2_size; table2_ite++){
        const std::vector<std::shared_ptr<TupleValue>> &values1 = table1.get(table1_ite).values();
        const std::vector<std::shared_ptr<TupleValue>> &values2 = table2.get(table2_ite).values();
        Tuple new_tuple;
        for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values1.begin(), end = values1.end();
          iter != end; ++iter){
            new_tuple.add(*iter);
        }
        for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values2.begin(), end = values2.end();
          iter != end; ++iter){
            new_tuple.add(*iter);
        }
        //合并插入新的 tupleset
        result_tupleSet.add(std::move(new_tuple));
      }
    }
  }
  return RC::SUCCESS;
}

bool filter_tuple(const std::shared_ptr<TupleValue> &values1, const std::shared_ptr<TupleValue> values2, CompOp op) {
  
  int cmp_result = (*values1).compare(*values2);

  switch (op) {
    case EQUAL_TO:
      return 0 == cmp_result;
    case LESS_EQUAL:
      return cmp_result <= 0;
    case NOT_EQUAL:
      return cmp_result != 0;
    case LESS_THAN:
      return cmp_result < 0;
    case GREAT_EQUAL:
      return cmp_result >= 0;
    case GREAT_THAN:
      return cmp_result > 0;

    default:
      break;
  }

  LOG_PANIC("Never should print this.");
  return cmp_result;  // should not go here
}

TupleSet get_final_result(const Selects &selects, TupleSet &full_tupleSet){
  TupleSet result_tupleSet;
  result_tupleSet.clear();
  TupleSchema schema;
  for (int i = selects.attr_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects.attributes[i];
    //没有表名的情况，所有表的都要加上
    if (nullptr == attr.relation_name) {
      if (0 == strcmp("*", attr.attribute_name)) {
        // 列出这张表所有字段
        TupleSchema::from_select(nullptr, nullptr, schema, full_tupleSet.get_schema());
        break; // 没有校验，给出* 之后，再写字段的错误
      } else {
        // 列出这张表相关字段
        TupleSchema::from_select(nullptr, attr.attribute_name, schema, full_tupleSet.get_schema());
      }
    }
    //有表名的情况
    if (nullptr != attr.relation_name && nullptr != attr.attribute_name){
      if(0 == strcmp("*", attr.attribute_name)){
        TupleSchema::from_select(attr.relation_name, nullptr, schema, full_tupleSet.get_schema());
      }else{
        TupleSchema::from_select(attr.relation_name, attr.attribute_name, schema, full_tupleSet.get_schema());
      }
    }
  }

  result_tupleSet.set_schema(schema);

  size_t full_tupleSet_size = full_tupleSet.size();
  size_t schema_size = schema.fields().size();
  for(size_t full_ite = 0; full_ite < full_tupleSet_size; full_ite++){
    Tuple new_tuple;
    const std::vector<std::shared_ptr<TupleValue>> &values = full_tupleSet.get(full_ite).values();
    for(int i = 0; i < schema_size; i++){
      const TupleField field = schema.field(i);
      size_t vaule_index = full_tupleSet.get_schema().index_of_field(field.table_name(), field.field_name());
      new_tuple.add(values[vaule_index]);
    }
    result_tupleSet.add(std::move(new_tuple));
  }
  return result_tupleSet;
}