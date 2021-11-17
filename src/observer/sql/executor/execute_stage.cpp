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
RC table_Join_execute(TupleSet &table1, TupleSet &table2, const Selects &selects,TupleSet &return_tupleSet);
bool filter_tuple(const std::shared_ptr<TupleValue> &values1, const std::shared_ptr<TupleValue> &values2, CompOp op);
TupleSet get_final_result(const Selects &selects, TupleSet &full_tupleSet);
RC get_ploy_tupleSet(const Poly poly_list[], int poly_num, TupleSet &full_tupleSet, TupleSet &resultTupleSet);
TupleSet group_by_field(const Selects &selects, TupleSet &full_tupleSet);
RC filter_sub_selects(TupleSet &full_tupleSet, Condition condition, TupleSet &sub_tupleSet, TupleSet &result_tupleSet);
RC filter_sub_selects(TupleSet &full_tupleSet, Condition condition, TupleSet &left_tupleSet, TupleSet &right_tupleSet, TupleSet &result_tupleSet);
void selects_print(const Selects &selects);
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

RC do_sub_select(Trx *trx, const char *db, const Selects &selects, TupleSet &result_tupleSet){
  RC rc = RC::SUCCESS;
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
      return rc;
    }
    select_nodes.push_back(select_node);
  }

  if (select_nodes.empty()) {
    LOG_ERROR("No table given");
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
      return rc;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }

  std::stringstream ss;
  if (tuple_sets.size() > 1) { //这时候取到的数据是所有过滤掉单表限制的 tuple
    result_tupleSet.set_is_need_print_multi_table(true);
    TupleSet join_result_tupleSet;
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
    rc = join_result_tupleSet.order_by_field_and_type(selects.order_by.attributes, selects.order_by.order_type, selects.order_by.attr_num);
    if(selects.poly_num > 0 && selects.attr_num > 0 && selects.group_by.attr_num == selects.attr_num){
      result_tupleSet = group_by_field(selects, join_result_tupleSet);
    }else{
      result_tupleSet = get_final_result(selects, join_result_tupleSet);
    }

  } else { //单张表
    result_tupleSet.set_is_need_print_multi_table(false);
    TupleSet sub_result_tupleSet;
    bool is_need_sub_select = false;
    LOG_ERROR("poly_num = %d, attr_num = %d, group_by_num = %d",selects.poly_num,selects.attr_num,selects.group_by.attr_num);
    LOG_ERROR("一共有 %d 个 condition",selects.condition_num);
    for(int condition_index = 0; condition_index < selects.condition_num; condition_index++){
      Condition condition = selects.conditions[condition_index];
      TupleSet left_sub_select_tupleSet, right_sub_select_tupleSet;
      if(condition.right_sub_select != nullptr){
        LOG_ERROR("开始做右子查询");
        rc = do_sub_select(trx, db, *condition.right_sub_select, right_sub_select_tupleSet);
        if(rc != SUCCESS) return rc;
      }
      // if(condition.left_sub_select != nullptr){
      //     LOG_ERROR("开始做左子查询");
      //     rc = do_sub_select(trx, db, *condition.left_sub_select, left_sub_select_tupleSet);
      //     if(rc != SUCCESS) return rc;
      // }
      //condition.left_sub_select == nullptr && 
      if(condition.right_sub_select != nullptr){
        rc = filter_sub_selects(tuple_sets.front(),condition,right_sub_select_tupleSet,sub_result_tupleSet);
        if(rc != SUCCESS) return rc;
        is_need_sub_select = true;
      }
      // if(condition.left_sub_select != nullptr && condition.right_sub_select != nullptr){
      //   rc = filter_sub_selects(tuple_sets.front(),condition,left_sub_select_tupleSet,right_sub_select_tupleSet,sub_result_tupleSet);
      //   if(rc != SUCCESS) return rc;
      //   is_need_sub_select = true;
      // }
    }

    if(is_need_sub_select){
      if(selects.poly_num > 0 && selects.attr_num == 0){ //给单张表做聚合
        rc = get_ploy_tupleSet(selects.poly_list, selects.poly_num, sub_result_tupleSet, result_tupleSet);
        if(rc != SUCCESS) return rc;
      }else if(selects.poly_num > 0 && selects.attr_num > 0 && selects.group_by.attr_num == selects.attr_num){
        result_tupleSet = group_by_field(selects, sub_result_tupleSet);   
      }else{
        rc = sub_result_tupleSet.order_by_field_and_type(selects.order_by.attributes, selects.order_by.order_type, selects.order_by.attr_num);
        result_tupleSet = get_final_result(selects, sub_result_tupleSet);
      }
    }else{
      if(selects.poly_num > 0 && selects.attr_num == 0){ //给单张表做聚合
        rc = get_ploy_tupleSet(selects.poly_list, selects.poly_num, tuple_sets.front(), result_tupleSet);
        if(rc != SUCCESS) return rc;
      }else if(selects.poly_num > 0 && selects.attr_num > 0 && selects.group_by.attr_num == selects.attr_num){
        LOG_ERROR("单表做Group by");
        result_tupleSet = group_by_field(selects, tuple_sets.front());       
      } else {
        rc = tuple_sets.front().order_by_field_and_type(selects.order_by.attributes, selects.order_by.order_type, selects.order_by.attr_num);
        result_tupleSet = get_final_result(selects, tuple_sets.front());
      }
    }
    result_tupleSet.print(ss);
    std::cout << ss.str() << std::endl;
  }

  for (SelectExeNode *& tmp_node: select_nodes) {
    delete tmp_node;
  }
  return RC::SUCCESS;
}
// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分. 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Selects &selects = sql->sstr.selection;
  selects_print(selects);
  TupleSet result_tupleSet;
  rc = do_sub_select(trx,db,selects,result_tupleSet);
  if(rc != SUCCESS){
    end_trx_if_need(session, trx, false);
    return rc;
  }
  std::stringstream ss;
  result_tupleSet.print(ss);
  result_tupleSet.clear();
  session_event->set_response(ss.str());
  end_trx_if_need(session, trx, true);
  return rc;
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
  Table * table = DefaultHandler::get_default().find_table(db, table_name);
  if (nullptr == table) {
    LOG_WARN("No such table [%s] in db [%s]", table_name, db);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  
  TupleSchema schema;
  TupleSchema::from_table(table, schema);
  if(selects.relation_num == 1){
    TupleSchema tmpschema;
    for (int i = selects.attr_num - 1; i >= 0; i--) {
      const RelAttr &attr = selects.attributes[i];
      if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
        if (0 == strcmp("*", attr.attribute_name)) {
          // 列出这张表所有字段
          TupleSchema::from_table(table, tmpschema);
          break; // 没有校验，给出* 之后，再写字段的错误
        } else {
          // 列出这张表相关字段
          RC rc = schema_add_field(table, attr.attribute_name, tmpschema);
          if (rc != RC::SUCCESS) {
            return rc;
          }
        }
      }else if(attr.relation_name != nullptr && 0 != strcmp(table_name, attr.relation_name) ){
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }
    }
    //校验 order by
    for (int i = selects.order_by.attr_num - 1; i >= 0; i--) {
      const RelAttr &attr = selects.order_by.attributes[i];
      if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
        if (0 == strcmp("*", attr.attribute_name)) {
          // 列出这张表所有字段
          TupleSchema::from_table(table, tmpschema);
          break; // 没有校验，给出* 之后，再写字段的错误
        } else {
          // 列出这张表相关字段
          RC rc = schema_add_field(table, attr.attribute_name, tmpschema);
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
  }

  //校验 order by
  for (int i = selects.order_by.attr_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects.order_by.attributes[i];
    TupleSchema tmpschema;
    if(attr.relation_name != nullptr){
      int isContain = 0;
      for (int j = selects.relation_num - 1; j >= 0; j--){
        if(0 == strcmp(attr.relation_name, selects.relations[j])) {
          isContain = 1;
          break;
        }
      }
      if (isContain == 0) {
        std::cout << "select order by no in selects.relations table" << std::endl;
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }

      if(0 == strcmp(table_name, attr.relation_name)){
        RC rc = schema_add_field(table, attr.attribute_name, tmpschema);
        if (rc != RC::SUCCESS) {
          std::cout << "select order by no exit " <<  std::string(attr.relation_name) << "." << std::string(attr.attribute_name) << std::endl;
          return rc;
        }  
      }
    }else{
      if(selects.relation_num > 1) return RC::SCHEMA_TABLE_NOT_EXIST;
      RC rc = schema_add_field(table, attr.attribute_name, tmpschema);
      if (rc != RC::SUCCESS) {
          std::cout << "select order by no exit " << std::string(attr.attribute_name) << std::endl;
      }
    } 
  }

  //校验 group by
  if(selects.group_by.attr_num > 0) {
    if (selects.attr_num != selects.group_by.attr_num){
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }
  if(selects.poly_num > 0 && selects.attr_num > 0){
    if(selects.attr_num != selects.group_by.attr_num) return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    for (int i = 0; i < selects.group_by.attr_num ; i++) {
      const RelAttr &attr = selects.group_by.attributes[i];
      int flag = 1;
      for(int j = 0; j < selects.attr_num; j++){
        if(attr.relation_name != nullptr){
          if(strcmp(selects.attributes[j].relation_name, attr.relation_name) == 0 && strcmp(selects.attributes[j].attribute_name, attr.attribute_name) == 0){
            flag = 0; break;
          }
        }else {
            if(strcmp(selects.attributes[j].attribute_name, attr.attribute_name) == 0){
            flag = 0; break;
          }        
        }
      }
      if(flag) return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }

  // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
  std::vector<DefaultConditionFilter *> condition_filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    if(condition.right_sub_select != nullptr) continue;
    // if(condition.right_sub_select != nullptr || condition.left_sub_select != nullptr) continue;

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

RC table_Join_execute(TupleSet &table1, TupleSet &table2, const Selects &selects, TupleSet &return_tupleSet){
  std::cout << "ready join table 1, size = " << table1.size() << " table 2, size = " << table2.size() << std::endl;
  TupleSet result_tupleSet;
  result_tupleSet.clear();
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

  return_tupleSet.clear();
  return_tupleSet.set_schema(schema);
  int result_size = result_tupleSet.size();
  for(size_t result_ite = 0; result_ite < result_size; result_ite++){
    const std::vector<std::shared_ptr<TupleValue>> &values = result_tupleSet.get(result_ite).values();
    Tuple new_tuple;
    for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = values.end();
        iter != end; ++iter){
          new_tuple.add(*iter);
      }
    return_tupleSet.add(std::move(new_tuple));
  }
  result_tupleSet.clear();
  return RC::SUCCESS;
}

bool filter_tuple(const std::shared_ptr<TupleValue> &values1, const std::shared_ptr<TupleValue> &values2, CompOp op) {
  
  if((*values1).isNull() || (*values2).isNull()) return false;  

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

  std::cout << "ready find result full_tupleSet size = " << full_tupleSet.size() << std::endl;
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
  full_tupleSet.clear();
  return result_tupleSet;
}


RC get_ploy_tupleSet(const Poly poly_list[], int poly_num, TupleSet &full_tupleSet, TupleSet &resultTupleSet){
  TupleSchema schema;
  int needAttrIndex[MAX_NUM];
  int needAttrCount = 0;
  for(int i = poly_num - 1; i >=0; i--){
      Poly po = poly_list[i];
      if(po.attr_num != 1) return RC::GENERIC_ERROR;
      std::string field_name = std::string(po.poly_attr.poly_name);
      field_name += "(";
      const RelAttr &attr = po.attributes[0];
      if(attr.relation_name != nullptr) field_name = field_name + std::string(attr.relation_name) + ".";
      if(attr.attribute_name != nullptr) field_name = field_name + std::string(attr.attribute_name) + ")";

      char *relation_name;
      if(attr.relation_name == nullptr) relation_name = strdup(full_tupleSet.get_schema().field(0).table_name());
      else relation_name = strdup(attr.relation_name);

      if(po.isAttr && strcmp(attr.attribute_name,"*") != 0){
        int index = full_tupleSet.get_schema().index_of_field(relation_name, attr.attribute_name);
        if(index < 0) return RC::GENERIC_ERROR;
        needAttrIndex[needAttrCount++] = full_tupleSet.get_schema().index_of_field(relation_name, attr.attribute_name);
      }else{
        if(strcmp(attr.attribute_name,"*") == 0 && (po.poly_attr.poly_type != POCOUNT) ) return RC::GENERIC_ERROR;
        needAttrIndex[needAttrCount++] = 0;
      }

      if(po.poly_attr.poly_type == POAVG) schema.add(FLOATS, relation_name, field_name.c_str());
      else if(po.poly_attr.poly_type == POCOUNT) schema.add(INTS, relation_name, field_name.c_str());
      else {
        const TupleField tuple_field = full_tupleSet.get_schema().field(full_tupleSet.get_schema().index_of_field(relation_name, attr.attribute_name));
        schema.add(tuple_field.type(), relation_name, field_name.c_str());
      }
  }
  resultTupleSet.set_schema(schema);
  if(full_tupleSet.size() == 0) return RC::SUCCESS;
  Tuple new_tuple;
  for(int i = poly_num - 1; i >=0; i--){
    int count = 0;
    float avg = 0.0;

    std::shared_ptr<TupleValue> value = full_tupleSet.get(0).get_pointer(needAttrIndex[i]);
    Poly po = poly_list[i];
    for(int j = 0; j < full_tupleSet.size(); j++){
      const std::vector<std::shared_ptr<TupleValue>> &values = full_tupleSet.get(j).values();
      switch (po.poly_attr.poly_type)
      {
      case POAVG:{
        if((*values[needAttrIndex[poly_num - 1 - i]]).isNull()) continue;
        else {
          avg += (*values[needAttrIndex[poly_num - 1 - i]]).getValue();
          count++;
        }
      }break;
      case POCOUNT:{
        if(strcmp(po.attributes[0].attribute_name,"*") == 0 || po.isAttr == 0) count++;
        else if( (*values[needAttrIndex[poly_num - 1 - i]]).isNull() == false ) count++;
      }break;     
      case POMAX:{
        if( (*values[needAttrIndex[poly_num - 1 - i]]).isNull() == false && filter_tuple(values[needAttrIndex[poly_num - 1 - i]], value, GREAT_THAN) ) value = values[needAttrIndex[poly_num - 1 - i]];
      }break;
      case POMIN:{
        if( (*values[needAttrIndex[poly_num - 1 - i]]).isNull() == false && filter_tuple(values[needAttrIndex[poly_num - 1 - i]], value, LESS_THAN) ) value = values[needAttrIndex[poly_num - 1 - i]];
      }break;
      default:
        break;
      }
    }
  
    switch (po.poly_attr.poly_type){
      case POAVG:{
        if((*value).isNull()) new_tuple.add(value);
        else new_tuple.add(avg/(float)count);
      }break;
      case POCOUNT:{
        new_tuple.add(count); 
      }break;     
      case POMAX:{
        new_tuple.add(value);
      }break;
      case POMIN:{
        new_tuple.add(value);
      }break;
      default:
        break;
    }     
  }
  resultTupleSet.add(std::move(new_tuple));
  return RC::SUCCESS;
}

TupleSet group_by_field(const Selects &selects, TupleSet &full_tupleSet){
  RC rc;
  TupleSet result_tupleSet;
  rc = full_tupleSet.order_by_field_and_type(selects.group_by.attributes, selects.group_by.order_type, selects.group_by.attr_num);   
  if(rc != RC::SUCCESS){
    return result_tupleSet;
  }

  std::stringstream bb;
  full_tupleSet.set_is_need_print_multi_table(false);
  full_tupleSet.print(bb);
  std::cout << bb.str() << std::endl;
  

  result_tupleSet.clear();
  TupleSchema schema;
  LOG_ERROR("排序成功");
  int group_by_index[MAX_NUM];
  for(int i = selects.group_by.attr_num - 1; i >=0; i--){
    if(selects.group_by.attributes[i].relation_name == nullptr){
        TupleField field = full_tupleSet.schema().field(0);
        group_by_index[i] = full_tupleSet.schema().index_of_field(field.table_name(), selects.group_by.attributes[i].attribute_name);
    }else{
        group_by_index[i] =  full_tupleSet.get_schema().index_of_field(selects.group_by.attributes[i].relation_name, selects.group_by.attributes[i].attribute_name);
    }
  }
  for(int i = 0; i < full_tupleSet.size();){
    const std::vector<std::shared_ptr<TupleValue>> &values1 = full_tupleSet.get(i).values();
    TupleSet new_tupleSet;
    new_tupleSet.set_schema(full_tupleSet.get_schema());
    Tuple new_tuple1;
    new_tuple1.add(values1);
    new_tupleSet.add(std::move(new_tuple1));
    if(i == full_tupleSet.size() - 1) i++;
    for(int j = i + 1; j < full_tupleSet.size(); j++){
      const std::vector<std::shared_ptr<TupleValue>> &values2 = full_tupleSet.get(j).values();
      int flag = 1; //判断是否匹配成功
      for(int gb_index = 0; gb_index < selects.group_by.attr_num; gb_index++){
        if(filter_tuple(values1[group_by_index[gb_index]], values2[group_by_index[gb_index]], NOT_EQUAL)) {flag = 0; break;}
      }
      if(flag){ //匹配成功加入到 new_tupleSet
        Tuple new_tuple2;
        new_tuple2.add(values2);
        new_tupleSet.add(std::move(new_tuple2));
        i = j;
      }else{ i = j; break; }
    }

    std::stringstream aa;
    new_tupleSet.set_is_need_print_multi_table(false);
    new_tupleSet.print(aa);
    std::cout << aa.str() << std::endl;


    TupleSet sub_tupleSet;
    rc = get_ploy_tupleSet(selects.poly_list, selects.poly_num, new_tupleSet, sub_tupleSet);
    if(rc != SUCCESS) return result_tupleSet;

    std::stringstream ss;
    sub_tupleSet.set_is_need_print_multi_table(false);
    sub_tupleSet.print(ss);
    std::cout << ss.str() << std::endl;

    //初始化 resultSchem{
    LOG_ERROR("一共 %d 条属性", selects.lsn);
    schema.clear();
    Tuple result_tuple;
    for (int index = selects.lsn - 1; index >= 0; index--){
      int value1_index = -1;
      int value2_index = -1;
      for(int attrIndex = selects.attr_num - 1; attrIndex >= 0 ; attrIndex--){
        if(selects.attributes[attrIndex].lsn == index){
          if(selects.attributes[attrIndex].relation_name != nullptr){
            value1_index = full_tupleSet.get_schema().index_of_field(selects.attributes[attrIndex].relation_name, selects.attributes[attrIndex].attribute_name);
            const TupleField *tmpField = &full_tupleSet.get_schema().field(value1_index);
            schema.add_if_not_exists(tmpField->type(), tmpField->table_name(), tmpField->field_name());
          }else{
            const char *table_name = full_tupleSet.get_schema().field(0).table_name();
            value1_index = full_tupleSet.get_schema().index_of_field(table_name, selects.attributes[attrIndex].attribute_name);
            const TupleField *tmpField = &full_tupleSet.get_schema().field(value1_index);  
            schema.add_if_not_exists(tmpField->type(), tmpField->table_name(), tmpField->field_name());        
          }
          break;
        }
      }
      for(int polyIndex = 0; polyIndex < selects.poly_num ; polyIndex++){
        if(selects.poly_list[polyIndex].lsn == index){
          TupleSchema tmpSchema = sub_tupleSet.get_schema();
          const TupleField *tmpField = &tmpSchema.field(selects.poly_num - polyIndex - 1);
          value2_index = selects.poly_num - polyIndex - 1;
          schema.add_if_not_exists(tmpField->type(), tmpField->table_name(), tmpField->field_name());
          break;
        }
      }
      if(value1_index >= 0){
        LOG_ERROR("add value %f ",values1[value1_index]->getValue());
        result_tuple.add(values1[value1_index]);
      }else if(value2_index >= 0){
        const std::vector<std::shared_ptr<TupleValue>> &sub_values = sub_tupleSet.get(0).values();
        LOG_ERROR("add value %f ",sub_values[value2_index]->getValue());
        result_tuple.add(sub_values[value2_index]);
      }
    }
    result_tupleSet.add(std::move(result_tuple));
  }
  result_tupleSet.set_schema(schema);

  LOG_ERROR("resultTupleSet size = %d", result_tupleSet.size());
  std::stringstream cc;
  result_tupleSet.set_is_need_print_multi_table(false);
  result_tupleSet.print(cc);
  std::cout << cc.str() << std::endl;

  return result_tupleSet;
}

RC filter_sub_selects(TupleSet &full_tupleSet, Condition condition, TupleSet &sub_tupleSet, TupleSet &result_tupleSet){
    result_tupleSet.clear();
    result_tupleSet.set_schema(full_tupleSet.get_schema());
    int tuple1_index, tuple2_index = 0;
    if(condition.left_attr.relation_name == nullptr){
      LOG_ERROR("开始做子查询过滤 %s ",condition.left_attr.attribute_name);
      tuple1_index = full_tupleSet.get_schema().index_of_field(full_tupleSet.get_schema().field(0).table_name(), condition.left_attr.attribute_name);
    }else{
      LOG_ERROR("开始做子查询过滤 %s %s",condition.left_attr.relation_name,condition.left_attr.attribute_name);
      tuple1_index = full_tupleSet.get_schema().index_of_field(condition.left_attr.relation_name, condition.left_attr.attribute_name);
    }
    if(tuple1_index < 0) return RC::GENERIC_ERROR;
    if(sub_tupleSet.size() > 1 && condition.comp != OP_NO_IN && condition.comp != OP_IN) return RC::GENERIC_ERROR;
    if(sub_tupleSet.get_schema().fields().size() > 1) return RC::GENERIC_ERROR;
    TupleField tuple1_field = full_tupleSet.get_schema().field(tuple1_index);
    TupleField tuple2_field = sub_tupleSet.get_schema().field(tuple2_index);
    if(tuple1_field.type() != tuple2_field.type()) {
      if((tuple1_field.type() == INTS || tuple1_field.type() == FLOATS) && (tuple2_field.type() != INTS && tuple2_field.type() != FLOATS))
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      else if((tuple2_field.type() == INTS || tuple2_field.type() == FLOATS) && (tuple1_field.type() != INTS && tuple1_field.type() != FLOATS))
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
    //比较两个 tuple 
    int table1_size = full_tupleSet.size();
    int table2_size = sub_tupleSet.size();
    for(size_t table1_ite = 0; table1_ite < table1_size; table1_ite++){
      int flag = 1;
      const std::vector<std::shared_ptr<TupleValue>> &values1 = full_tupleSet.get(table1_ite).values();
      for(size_t table2_ite = 0; table2_ite < table2_size; table2_ite++){
        const std::vector<std::shared_ptr<TupleValue>> &values2 = sub_tupleSet.get(table2_ite).values();
        if(condition.comp != OP_IN && condition.comp != OP_NO_IN){
    
          std::shared_ptr<TupleValue> value1_float = (std::shared_ptr<TupleValue>)new FloatValue(values1[tuple1_index]->getValue());
          std::shared_ptr<TupleValue> value2_float = (std::shared_ptr<TupleValue>)new FloatValue(values2[tuple2_index]->getValue());
          if(filter_tuple(value1_float, value2_float, condition.comp)){
            Tuple new_tuple;
            for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values1.begin(), end = values1.end();
              iter != end; ++iter){
                new_tuple.add(*iter);
            }
            //合并插入新的 tupleset
            result_tupleSet.add(std::move(new_tuple));          
          }
        }

        if(filter_tuple(values1[tuple1_index], values2[tuple2_index], EQUAL_TO)){
          if(condition.comp == OP_IN){
            Tuple new_tuple;
            for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values1.begin(), end = values1.end();
              iter != end; ++iter){
                new_tuple.add(*iter);
            }
            //合并插入新的 tupleset
            result_tupleSet.add(std::move(new_tuple));
            break;
          }
          if(condition.comp == OP_NO_IN){
            flag = 0;
            break;
          }
        }
      }
      if(flag && condition.comp == OP_NO_IN){
        Tuple new_tuple;
        for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values1.begin(), end = values1.end();
          iter != end; ++iter){
            new_tuple.add(*iter);
        }
        //合并插入新的 tupleset
        result_tupleSet.add(std::move(new_tuple));
      }
    }
    return RC::SUCCESS;
}

RC filter_sub_selects(TupleSet &full_tupleSet, Condition condition, TupleSet &left_tupleSet, TupleSet &right_tupleSet, TupleSet &result_tupleSet){
    result_tupleSet.clear();
    result_tupleSet.set_schema(full_tupleSet.get_schema());
    int tuple1_index = 0, tuple2_index = 0;
    if((left_tupleSet.size() > 1 || right_tupleSet.size() > 1) && condition.comp != OP_NO_IN && condition.comp != OP_IN) return RC::GENERIC_ERROR;
    if(left_tupleSet.get_schema().fields().size() > 1 || right_tupleSet.get_schema().fields().size() > 1) return RC::GENERIC_ERROR;
    TupleField tuple1_field = left_tupleSet.get_schema().field(tuple1_index);
    TupleField tuple2_field = right_tupleSet.get_schema().field(tuple2_index);
    if(tuple1_field.type() != tuple2_field.type()) {
      if((tuple1_field.type() == INTS || tuple1_field.type() == FLOATS) && (tuple2_field.type() != INTS && tuple2_field.type() != FLOATS))
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      else if((tuple2_field.type() == INTS || tuple2_field.type() == FLOATS) && (tuple1_field.type() != INTS && tuple1_field.type() != FLOATS))
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
    //比较两个 tuple 
    int table1_size = left_tupleSet.size();
    int table2_size = right_tupleSet.size();
    for(size_t table1_ite = 0; table1_ite < table1_size; table1_ite++){
      int flag = 1;
      const std::vector<std::shared_ptr<TupleValue>> &values1 = left_tupleSet.get(table1_ite).values();
      for(size_t table2_ite = 0; table2_ite < table2_size; table2_ite++){
        const std::vector<std::shared_ptr<TupleValue>> &values2 = right_tupleSet.get(table2_ite).values();
        if(condition.comp != OP_IN && condition.comp != OP_NO_IN){
          std::shared_ptr<TupleValue> value1_float = (std::shared_ptr<TupleValue>)new FloatValue(values1[tuple1_index]->getValue());
          std::shared_ptr<TupleValue> value2_float = (std::shared_ptr<TupleValue>)new FloatValue(values2[tuple2_index]->getValue());
          if(filter_tuple(value1_float, value2_float, condition.comp)){
            int full_tuple_size = full_tupleSet.size();
            for(int full_index = 0; full_index < full_tuple_size; full_tuple_size++){
              Tuple new_tuple;
              const std::vector<std::shared_ptr<TupleValue>> &full_values = full_tupleSet.get(full_index).values();
              for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = full_values.begin(), end = full_values.end();
                iter != end; ++iter){
                  new_tuple.add(*iter);
              }
              //合并插入新的 tupleset
              result_tupleSet.add(std::move(new_tuple));   
            }
            break;       
          }
        }

      //   if(filter_tuple(values1[tuple1_index], values2[tuple2_index], EQUAL_TO)){
      //     if(condition.comp == OP_IN){
      //       Tuple new_tuple;
      //       for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values1.begin(), end = values1.end();
      //         iter != end; ++iter){
      //           new_tuple.add(*iter);
      //       }
      //       //合并插入新的 tupleset
      //       result_tupleSet.add(std::move(new_tuple));
      //       break;
      //     }
      //     if(condition.comp == OP_NO_IN){
      //       flag = 0;
      //       break;
      //     }
      //   }
      // }
      // if(flag && condition.comp == OP_NO_IN){
      //   Tuple new_tuple;
      //   for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values1.begin(), end = values1.end();
      //     iter != end; ++iter){
      //       new_tuple.add(*iter);
      //   }
      //   //合并插入新的 tupleset
      //   result_tupleSet.add(std::move(new_tuple));
      }
    }
    return RC::SUCCESS;
}


void selects_print(const Selects &selects){
  LOG_ERROR("------------------select info -----------------");
  for(int i = 0; i < selects.relation_num; i++) LOG_ERROR("from list %d : %s", i, selects.relations[i]);
  for(int i = 0; i < selects.attr_num; i++){
    RelAttr attr = selects.attributes[i];
    if(attr.relation_name == nullptr){
      LOG_ERROR("attr list %d : %s", i ,attr.attribute_name);
    }else{
      LOG_ERROR("attr list %d : %s.%s", i ,attr.relation_name,attr.attribute_name);
    }
  }
  for (size_t i = 0; i < selects.poly_num; i++)
  {
    Poly po = selects.poly_list[i];
    LOG_ERROR("poly name = %s",po.poly_attr.poly_name);
    for(int j = 0; j < po.attr_num; j++){
      RelAttr attr = po.attributes[j];
      if(attr.relation_name == nullptr){
        LOG_ERROR("  poli attr list %d : %s", j ,attr.attribute_name);
      }else{
        LOG_ERROR("  poli attr list %d : %s.%s", j ,attr.relation_name,attr.attribute_name);
      }
    }
  }

  for (size_t i = 0; i < selects.condition_num; i++){
    Condition condition = selects.conditions[i];
    if(condition.left_is_attr){
      RelAttr attr = condition.left_attr;
      if(attr.relation_name == nullptr){
        LOG_ERROR("Condition left attr : %s", attr.attribute_name);
      }else{
        LOG_ERROR("Condition left attr : %s.%s", attr.relation_name,attr.attribute_name);
      }
    }
    switch (condition.comp)
    {
    case EQUAL_TO:
      LOG_ERROR("=");
      break;
    case LESS_EQUAL:
      LOG_ERROR("<=");
      break;
    case NOT_EQUAL:
      LOG_ERROR("!=");
      break;
    case LESS_THAN:
      LOG_ERROR("<");
      break;
    case GREAT_EQUAL:
      LOG_ERROR(">=");
      break;
    case GREAT_THAN:
      LOG_ERROR(">");
      break;
    case OP_IS:
      LOG_ERROR("is");
      break;
    case OP_NO_IS:
      LOG_ERROR("not is");
      break;
    case OP_IN:
      LOG_ERROR("in");
      break;
    case OP_NO_IN:
      LOG_ERROR("no in");
      break;
    default:
      break;
    }
    if(condition.left_is_attr){
      RelAttr attr = condition.left_attr;
      if(attr.relation_name == nullptr){
        LOG_ERROR("Condition left attr  : %s" , attr.attribute_name);
      }else{
        LOG_ERROR("Condition left attr  : %s.%s", attr.relation_name,attr.attribute_name);
      }
    }
    if(condition.right_is_attr){
      RelAttr attr = condition.right_attr;
      if(attr.relation_name == nullptr){
        LOG_ERROR("Condition right attr  : %s" , attr.attribute_name);
      }else{
        LOG_ERROR("Condition right attr  : %s.%s", attr.relation_name,attr.attribute_name);
      }
    }
    if(condition.left_sub_select != nullptr){
      LOG_ERROR("---------------------left_sub_selects---------------");
      selects_print(*condition.left_sub_select);      
    }
    if(condition.right_sub_select != nullptr){
      LOG_ERROR("---------------------right_sub_selects---------------");
      selects_print(*condition.right_sub_select);
    }   
  }
}