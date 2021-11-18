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
// Created by Wangyunlai on 2021/5/13.
//

#include <limits.h>
#include <string.h>
#include <algorithm>

#include "storage/common/table.h"
#include "storage/common/table_meta.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/default/disk_buffer_pool.h"
#include "storage/common/record_manager.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/common/index.h"
#include "storage/common/bplus_tree_index.h"
#include "storage/trx/trx.h"

Table::Table() : 
    data_buffer_pool_(nullptr),
    file_id_(-1),
    record_handler_(nullptr) {
}

Table::~Table() {
  delete record_handler_;
  record_handler_ = nullptr;

  if (data_buffer_pool_ != nullptr && file_id_ >= 0) {
    data_buffer_pool_->close_file(file_id_);
    data_buffer_pool_ = nullptr;
  }

  LOG_INFO("Table has been closed: %s", name());
}

RC Table::create(const char *path, const char *name, const char *base_dir, int attribute_count, const AttrInfo attributes[]) {

  if (nullptr == name || common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attribute_count <= 0 || nullptr == attributes) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d, attributes=%p",
        name, attribute_count, attributes);
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table记录一个表的元数据
  // 判断表文件是否已经存在

  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (-1 == fd) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s",
                path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", 
       path, errno, strerror(errno));
    return RC::IOERR;
  }

  close(fd);

  // 创建文件
  if ((rc = table_meta_.init(name, attribute_count, attributes)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc; // delete table file
  }

  std::fstream fs;
  fs.open(path, std::ios_base::out | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  std::string data_file = std::string(base_dir) + "/" + name + TABLE_DATA_SUFFIX;
  data_buffer_pool_ = theGlobalDiskBufferPool();
  rc = data_buffer_pool_->create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }

  rc = init_record_handler(base_dir);

  base_dir_ = base_dir;
  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}

RC Table::open(const char *meta_file, const char *base_dir) {
  // 加载元数据文件
  std::fstream fs;
  std::string meta_file_path = std::string(base_dir) + "/" + meta_file;
  fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file, strerror(errno));
    return RC::IOERR;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file);
    return RC::GENERIC_ERROR;
  }
  fs.close();

  // 加载数据文件
  RC rc = init_record_handler(base_dir);

  base_dir_ = base_dir;

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {
    const IndexMeta *index_meta = table_meta_.index(i);
    const FieldMeta *field_meta = table_meta_.field(index_meta->fields()[0]);
    if (field_meta == nullptr) {
      LOG_PANIC("Found invalid index meta info which has a non-exists field. table=%s, index=%s, field=%s",
                name(), index_meta->name(), index_meta->fields()[0]);
      return RC::GENERIC_ERROR;
    }

    BplusTreeIndex *index = new BplusTreeIndex();
    std::string index_file = index_data_file(base_dir, name(), index_meta->name());
    rc = index->open(index_file.c_str(), *index_meta, *field_meta);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%d:%s",
                name(), index_meta->name(), index_file.c_str(), rc, strrc(rc));
      return rc;
    }
    indexes_.push_back(index);
  }
  return rc;
}

RC Table::drop (const char *path, const char *name){
  for(std::vector<Index *>::const_iterator iter = indexes_.cbegin(); iter != indexes_.cend(); iter++){
    IndexMeta meta = (*iter)->index_meta();
    std::string table_index_file_path = index_data_file(base_dir_.c_str(), name, meta.name()); 
    if(remove(table_index_file_path.c_str()) == 0){
      std::cout << "drop table index path :" << table_index_file_path << std::endl;
    }
    delete *iter;
  }
  std::string table_file_path = table_meta_file(path, name); 
  std::string table_data_file = std::string(path) + "/" + std::string(name) + TABLE_DATA_SUFFIX;
  if(remove(table_file_path.c_str()) == 0){
    std::cout << "drop table path :" << table_file_path << std::endl;
  }else{
    return RC::GENERIC_ERROR;
  }
  if(remove(table_data_file.c_str()) == 0){
    std::cout << "drop table data path :" << table_data_file << std::endl;
  }else{
    return RC::GENERIC_ERROR;
  } 
  return RC::SUCCESS;
}

RC Table::commit_insert(Trx *trx, const RID &rid) {
  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->commit_insert(this, record);
}

RC Table::rollback_insert(Trx *trx, const RID &rid) {

  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // remove all indexes
  rc = delete_entry_of_indexes(record.data, rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d) while rollback insert, rc=%d:%s",
              rid.page_num, rid.slot_num, rc, strrc(rc));
  } else {
    rc = record_handler_->delete_record(&rid);
  }
  return rc;
}

RC Table::insert_record(Trx *trx, Record *record) {
  RC rc = RC::SUCCESS;

  if (trx != nullptr) {
    trx->init_trx_info(this, *record);
  }
  rc = record_handler_->insert_record(record->data, table_meta_.record_size(), &record->rid);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));
    return rc;
  }

  if (trx != nullptr) {
    rc = trx->insert_record(this, record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to log operation(insertion) to trx");

      RC rc2 = record_handler_->delete_record(&record->rid);
      if (rc2 != RC::SUCCESS) {
        LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                  name(), rc2, strrc(rc2));
      }
      return rc;
    }
  }

  rc = insert_entry_of_indexes(record->data, record->rid);
  if (rc != RC::SUCCESS) {
    RC rc2 = delete_entry_of_indexes(record->data, record->rid, true);
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    rc2 = record_handler_->delete_record(&record->rid);
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    return rc;
  }
  return rc;
}

RC Table::insert_records(Trx *trx, int tuple_num, const InsertsTuple *tuples){
    char *tmp_record_data[MAX_NUM];
    Record records[MAX_NUM];
    for(int i = 0; i < tuple_num; i++){
      RC rc = make_record(tuples[i].value_num, tuples[i].values, tmp_record_data[i]);
      if(rc != RC::SUCCESS){
        return rc;
      }
      records[i].data = tmp_record_data[i];
    }
    for(int i = 0; i < tuple_num; i++){
      RC rc = insert_record(trx, &records[i]);
      if(rc != RC::SUCCESS){
        for(int j = 0; j < i; j++) record_handler_->delete_record(&records[i].rid);
        return rc;
      }
    }
    return RC::SUCCESS;
}

RC Table::insert_record(Trx *trx, int value_num, const Value *values) {
  if (value_num <= 0 || nullptr == values ) {
    LOG_ERROR("Invalid argument. value num=%d, values=%p", value_num, values);
    return RC::INVALID_ARGUMENT;
  }

  char *record_data;
  RC rc = make_record(value_num, values, record_data);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create a record. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  Record record;
  record.data = record_data;
  // record.valid = true;
  rc = insert_record(trx, &record);
  delete[] record_data;
  return rc;
}

const char *Table::name() const {
  return table_meta_.name();
}

const TableMeta &Table::table_meta() const {
  return table_meta_;
}

RC Table::make_record(int value_num, const Value *values, char * &record_out) {
  // 检查字段类型是否一致
  if (value_num + table_meta_.sys_field_num() != table_meta_.field_num()) {
    return RC::SCHEMA_FIELD_MISSING;
  }

  const int normal_field_start_index = table_meta_.sys_field_num();
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value &value = values[i];
    std::cerr<<"---field->type():"<<field->type()<<std::endl;
    std::cerr<<"---value.type:"<<value.type<<std::endl;
    if ( field->type() != value.type && field->is_nullable() == false ) {
      if(field->type() == TEXTS && value.type == CHARS)
        continue;
      LOG_ERROR("Invalid value type. field name=%s, type=%d, but given=%d",
        field->name(), field->type(), value.type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }

  // 复制所有字段的值
  int record_size = table_meta_.record_size();
  char *record = new char [record_size];

  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value &value = values[i];
    if(value.type == AttrType::NULLS && field->is_nullable()){
      switch (field->type())
      {
      case AttrType::INTS:{
          int null_int = OB_INT_MIN;
          int *vdata = &null_int;
          memcpy(record + field->offset(), vdata, field->len());
      }
        break;
      case AttrType::FLOATS:{
          float null_float = OB_FLT_MIN;
          float *vdata = &null_float;
          memcpy(record + field->offset(), vdata, field->len());       
      }
        break;
      case AttrType::CHARS:{
          char vdata[4] = "NUL";
          memcpy(record + field->offset(), vdata, field->len()); 
      }
        break;
      case AttrType::TEXTS:{
          int null_int = OB_INT_MIN;
          int *vdata = &null_int;
          memcpy(record + field->offset(), vdata, field->len()); 
      }
        break;
      case AttrType::DATES:{
          int null_date = 0;
          int *vdata = &null_date;
          memcpy(record + field->offset(), vdata, field->len());
      }
        break;      
      default:
        break;
      }
      continue;
    }

    if(field->type() == AttrType::FLOATS && value.type == AttrType::INTS){
      int *vdata = (int *)value.data;
      float i2fdata = (float)(*vdata * 1.0);
      memcpy(record + field->offset(), &i2fdata, field->len());
    }
    else if(field->type() == AttrType::TEXTS){
      //分配一个页
      RC ret = RC::SUCCESS;
      BPPageHandle page_handle;
      if ((ret = data_buffer_pool_->allocate_page(file_id_, &page_handle)) != RC::SUCCESS) {
        LOG_ERROR("Failed to allocate page while inserting record. file_it:%d, ret:%d",
                file_id_, ret);
        return ret;
      }
      //把text内容复制进去
      char *data;
      ret = data_buffer_pool_->get_data(&page_handle, &data);
      if (ret != RC::SUCCESS) {
        LOG_ERROR("Failed to get page data. ret=%d:%s", ret, strrc(ret));
        return ret;
      }
      int len = strlen((char *)value.data);
      std::cerr<<"---len:"<<len<<std::endl;
      if(len > 4096) 
        len = 4096;  
      memcpy(data, value.data, len);

      std::cerr<<"---memcpy suc1"<<std::endl;
      //把得到的page_id+offset填入属性框
      int page_id = page_handle.frame->page.page_num;
      int addr = (file_id_<<22) + (page_id<<12) + len;
      memcpy(record + field->offset(), &addr, field->len());
      std::cerr<<"---memcpy suc2"<<std::endl;
    }
    else{
      memcpy(record + field->offset(), value.data, field->len());
    }
  }

  record_out = record;
  return RC::SUCCESS;
}

RC Table::init_record_handler(const char *base_dir) {
  std::string data_file = std::string(base_dir) + "/" + table_meta_.name() + TABLE_DATA_SUFFIX;
  if (nullptr == data_buffer_pool_) {
    data_buffer_pool_ = theGlobalDiskBufferPool();
  }

  int data_buffer_pool_file_id;
  RC rc = data_buffer_pool_->open_file(data_file.c_str(), &data_buffer_pool_file_id);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s",
              data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler();
  rc = record_handler_->init(*data_buffer_pool_, data_buffer_pool_file_id);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  file_id_ = data_buffer_pool_file_id;
  return rc;
}

/**
 * 为了不把Record暴露出去，封装一下
 */
class RecordReaderScanAdapter {
public:
  explicit RecordReaderScanAdapter(void (*record_reader)(const char *data, void *context), void *context)
      : record_reader_(record_reader), context_(context){
  }

  void consume(const Record *record) {
    record_reader_(record->data, context_);
  }
private:
  void (*record_reader_)(const char *, void *);
  void *context_;
};
static RC scan_record_reader_adapter(Record *record, void *context) {
  RecordReaderScanAdapter &adapter = *(RecordReaderScanAdapter *)context;
  adapter.consume(record);
  return RC::SUCCESS;
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context, void (*record_reader)(const char *data, void *context)) {
  RecordReaderScanAdapter adapter(record_reader, context);
  return scan_record(trx, filter, limit, (void *)&adapter, scan_record_reader_adapter);
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context, RC (*record_reader)(Record *record, void *context)) {
  if (nullptr == record_reader) {
    return RC::INVALID_ARGUMENT;
  }

  if (0 == limit) {
    return RC::SUCCESS;
  }

  if (limit < 0) {
    limit = INT_MAX;
  }

  IndexScanner *index_scanner = find_index_for_scan(filter);

  if (index_scanner != nullptr) {
    return scan_record_by_index(trx, index_scanner, filter, limit, context, record_reader);
  }
  
  RC rc = RC::SUCCESS;
  RecordFileScanner scanner;
  rc = scanner.open_scan(*data_buffer_pool_, file_id_, filter);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. file id=%d. rc=%d:%s", file_id_, rc, strrc(rc));
    return rc;
  }

  int record_count = 0;
  Record record;
  rc = scanner.get_first_record(&record);
  for ( ; RC::SUCCESS == rc && record_count < limit; rc = scanner.get_next_record(&record)) {
    if (trx == nullptr || trx->is_visible(this, &record)) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        break;
      }
      record_count++;
    }
  }

  if (RC::RECORD_EOF == rc) {
    rc = RC::SUCCESS;
  } else {
    LOG_ERROR("failed to scan record. file id=%d, rc=%d:%s", file_id_, rc, strrc(rc));
  }
  scanner.close_scan();
  return rc;
}

RC Table::scan_record_by_index(Trx *trx, IndexScanner *scanner, ConditionFilter *filter, int limit, void *context,
                               RC (*record_reader)(Record *, void *)) {
  RC rc = RC::SUCCESS;
  RID rid;
  Record record;
  int record_count = 0;
  while (record_count < limit) {
    rc = scanner->next_entry(&rid);
    if (rc != RC::SUCCESS) {
      if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
        break;
      }
      LOG_ERROR("Failed to scan table by index. rc=%d:%s", rc, strrc(rc));
      break;
    }

    rc = record_handler_->get_record(&rid, &record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to fetch record of rid=%d:%d, rc=%d:%s", rid.page_num, rid.slot_num, rc, strrc(rc));
      break;
    }

    if ((trx == nullptr || trx->is_visible(this, &record)) && (filter == nullptr || filter->filter(record))) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        LOG_TRACE("Record reader break the table scanning. rc=%d:%s", rc, strrc(rc));
        break;
      }
    }

    record_count++;
  }

  scanner->destroy();
  return rc;
}

class IndexInserter {
public:
  explicit IndexInserter(Index *index) : index_(index) {
  }

  RC insert_index(const Record *record) {
    return index_->insert_entry(record->data, &record->rid);
  }
private:
  Index * index_;
};

static RC insert_index_record_reader_adapter(Record *record, void *context) {
  IndexInserter &inserter = *(IndexInserter *)context;
  return inserter.insert_index(record);
}

RC Table::create_index(Trx *trx, const char *index_name, char * const attribute_names[], size_t attribute_count, int is_unique) {
  if (index_name == nullptr || common::is_blank(index_name)) {
    return RC::INVALID_ARGUMENT;
  }
  for(int i = 0; i < attribute_count; i++){
    if(common::is_blank(attribute_names[i]) || attribute_names[i] == nullptr)
       return RC::INVALID_ARGUMENT;
  }

  if (table_meta_.index(index_name) != nullptr) {
    return RC::SCHEMA_INDEX_EXIST;
  }

  if(table_meta_.find_index_by_fields(attribute_names, attribute_count) != nullptr)
    return RC::INVALID_ARGUMENT;

  const FieldMeta *field_metas[MAX_NUM];
  for(int i = 0; i < attribute_count; i++){
    field_metas[i] = table_meta_.field(attribute_names[i]);
    if (!field_metas[i]) {
      return RC::SCHEMA_FIELD_MISSING;
    }
  }

  
  IndexMeta new_index_meta;
  RC rc = new_index_meta.init(index_name, field_metas, attribute_count, is_unique);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  for(int i = 0; i < new_index_meta.fields_count(); i++){
    LOG_ERROR("索引对应的 filed_name = %s", new_index_meta.fields()[i]);
  }

  // 创建索引相关数据
  BplusTreeIndex *index = new BplusTreeIndex();
  std::string index_file = index_data_file(base_dir_.c_str(), name(), index_name);
  rc = index->create(index_file.c_str(), new_index_meta, *field_metas[0]);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  IndexInserter index_inserter(index);
  rc = scan_record(trx, nullptr, -1, &index_inserter, insert_index_record_reader_adapter);
  if (rc != RC::SUCCESS) {
    // rollback
    delete index;
    LOG_ERROR("Failed to insert index to all records. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }
  indexes_.push_back(index);

  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }
  // 创建元数据临时文件
  std::string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR; // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR;
  }
  fs.close();

  // 覆盖原始元数据文件
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). " \
              "system error=%d:%s", tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
    return RC::IOERR;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("add a new index (%s) on the table (%s)", index_name, name());

  return rc;
}

class RecordUpdater {
  public:
  RecordUpdater(Table &table, Trx *trx, const char *attribute_name, const Value *value) : table_(table), trx_(trx), attribute_name_(attribute_name), value_(value){
  }
  RC update_record(Record *record) {
    RC rc = RC::SUCCESS;
    rc = table_.update_record(trx_, record, attribute_name_, value_);
    if (rc == RC::SUCCESS) {
      updated_count_++;
    }
    return rc;
  }

  int updated_count() const {
    return updated_count_;
  }
  private:
  Table & table_;
  Trx *trx_;
  const char *attribute_name_;
  const Value *value_;
  int updated_count_ = 0;
};

static RC record_reader_update_adapter(Record *record, void *context) {
  RecordUpdater &record_updater = *(RecordUpdater *)context;
  return record_updater.update_record(record);
}

RC Table::update_record(Trx *trx, ConditionFilter *filter, const char *attribute_name, const Value *value, int condition_num, const Condition conditions[], int *updated_count) {
  RecordUpdater updater(*this, trx, attribute_name, value);

  const int normal_field_start_index = table_meta_.sys_field_num();
  const int all_field_num = table_meta_.field_num();
  for (int i = 0; i + normal_field_start_index < all_field_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    if (std::string(field->name()) == std::string(attribute_name)) {
      if(field->type() != value->type) {
        LOG_ERROR("Invalid value type. field name=%s, type=%d, but given=%d",
        field->name(), field->type(), value->type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }
  }
  RC rc = scan_record(trx, filter, -1, &updater, record_reader_update_adapter);
  if (updated_count != nullptr) {
    *updated_count = updater.updated_count();
  }
  return rc;
}

RC Table::update_record(Trx *trx, Record *record, const char *attribute_name, const Value *value) {
  RC rc = RC::SUCCESS;
  const int normal_field_start_index = table_meta_.sys_field_num();
  const int all_field_num = table_meta_.field_num();
  for (int i = 0; i + normal_field_start_index < all_field_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    if (std::string(field->name()) == std::string(attribute_name)) {
      if(field->type() != value->type) {
        LOG_ERROR("Invalid value type. field name=%s, type=%d, but given=%d",
        field->name(), field->type(), value->type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      
      //先删除旧索引
      rc = delete_entry_of_indexes(record->data, record->rid, false);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to delete indexes of record (rid=%d.%d). rc=%d:%s",
                record->rid.page_num, record->rid.slot_num, rc, strrc(rc));
        return rc;
      } else {
        char *record_data = record->data;
        memcpy(record_data + field->offset(), value->data, field->len());
        Record new_record;
        new_record.rid = record->rid;
        new_record.data = record_data;
        rc =  record_handler_->update_record(&new_record);
        if(rc != RC::SUCCESS){
          LOG_ERROR("Failed to update record (rid=%d.%d). rc=%d:%s",
                record->rid.page_num, record->rid.slot_num, rc, strrc(rc));
          return rc;
        }else { //插入新索引
          rc = insert_entry_of_indexes(new_record.data, new_record.rid);
          return rc;
        }
      }
    }
  }
  return RC::GENERIC_ERROR;
}

class RecordDeleter {
public:
  RecordDeleter(Table &table, Trx *trx) : table_(table), trx_(trx) {
  }

  RC delete_record(Record *record) {
    RC rc = RC::SUCCESS;
    rc = table_.delete_record(trx_, record);
    if (rc == RC::SUCCESS) {
      deleted_count_++;
    }
    return rc;
  }

  int deleted_count() const {
    return deleted_count_;
  }

private:
  Table & table_;
  Trx *trx_;
  int deleted_count_ = 0;
};

static RC record_reader_delete_adapter(Record *record, void *context) {
  RecordDeleter &record_deleter = *(RecordDeleter *)context;
  return record_deleter.delete_record(record);
}

RC Table::delete_record(Trx *trx, ConditionFilter *filter, int *deleted_count) {
  RecordDeleter deleter(*this, trx);
  RC rc = scan_record(trx, filter, -1, &deleter, record_reader_delete_adapter);
  if (deleted_count != nullptr) {
    *deleted_count = deleter.deleted_count();
  }
  return rc;
}

RC Table::delete_record(Trx *trx, Record *record) {
  RC rc = RC::SUCCESS;
  if (trx != nullptr) {
    rc = trx->delete_record(this, record);
  } else {
    rc = delete_entry_of_indexes(record->data, record->rid, false);// 重复代码 refer to commit_delete
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to delete indexes of record (rid=%d.%d). rc=%d:%s",
                record->rid.page_num, record->rid.slot_num, rc, strrc(rc));
    } else {
      rc = record_handler_->delete_record(&record->rid);
    }
  }
  return rc;
}

RC Table::commit_delete(Trx *trx, const RID &rid) {
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = delete_entry_of_indexes(record.data, record.rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d). rc=%d:%s",
              rid.page_num, rid.slot_num, rc, strrc(rc));// panic?
  }

  rc = record_handler_->delete_record(&rid);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return rc;
}

RC Table::rollback_delete(Trx *trx, const RID &rid) {
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->rollback_delete(this, record); // update record in place
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid) {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->insert_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      break;
    }
  }
  return rc;
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists) {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}

Index *Table::find_index(const char *index_name) const {
  for (Index *index: indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}

IndexScanner *Table::find_index_for_scan(const DefaultConditionFilter &filter) {
  const ConDesc *field_cond_desc = nullptr;
  const ConDesc *value_cond_desc = nullptr;
  if (filter.left().is_attr && !filter.right().is_attr) {
    field_cond_desc = &filter.left();
    value_cond_desc = &filter.right();
  } else if (filter.right().is_attr && !filter.left().is_attr) {
    field_cond_desc = &filter.right();
    value_cond_desc = &filter.left();
  }
  if (field_cond_desc == nullptr || value_cond_desc == nullptr) {
    return nullptr;
  }

  const FieldMeta *field_meta = table_meta_.find_field_by_offset(field_cond_desc->attr_offset);
  if (nullptr == field_meta) {
    LOG_PANIC("Cannot find field by offset %d. table=%s",
              field_cond_desc->attr_offset, name());
    return nullptr;
  }
  char * fields[1];
  fields[0] = strdup(field_meta->name());
  const IndexMeta *index_meta = table_meta_.find_index_by_fields(fields, 1);
  //先屏蔽多列
  if (nullptr == index_meta || index_meta->fields_count() > 1 || field_meta->is_nullable()) {
    return nullptr;
  }

  Index *index = find_index(index_meta->name());
  if (nullptr == index) {
    return nullptr;
  }

  return index->create_scanner(filter.comp_op(), (const char *)value_cond_desc->value);
}

IndexScanner *Table::find_index_for_scan(const ConditionFilter *filter) {
  if (nullptr == filter) {
    return nullptr;
  }

  // remove dynamic_cast
  const DefaultConditionFilter *default_condition_filter = dynamic_cast<const DefaultConditionFilter *>(filter);
  if (default_condition_filter != nullptr) {
    return find_index_for_scan(*default_condition_filter);
  }

  const CompositeConditionFilter *composite_condition_filter = dynamic_cast<const CompositeConditionFilter *>(filter);
  if (composite_condition_filter != nullptr) {
    int filter_num = composite_condition_filter->filter_num();
    for (int i = 0; i < filter_num; i++) {
      IndexScanner *scanner= find_index_for_scan(&composite_condition_filter->filter(i));
      if (scanner != nullptr) {
        return scanner; // 可以找到一个最优的，比如比较符号是=
      }
    }
  }
  return nullptr;
}

RC Table::sync() {
  RC rc = data_buffer_pool_->flush_all_pages(file_id_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to flush table's data pages. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }

  for (Index *index: indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
                name(), index->index_meta().name(), rc, strrc(rc));
      return rc;
    }
  }
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}
