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
// Created by Wangyunlai on 2021/5/14.
//

#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "common/log/log.h"

Tuple::Tuple(const Tuple &other) {
  LOG_PANIC("Copy constructor of tuple is not supported");
  exit(1);
}

Tuple::Tuple(Tuple &&other) noexcept : values_(std::move(other.values_)) {
}

Tuple & Tuple::operator=(Tuple &&other) noexcept {
  if (&other == this) {
    return *this;
  }

  values_.clear();
  values_.swap(other.values_);
  return *this;
}

Tuple::~Tuple() {
}

// add (Value && value)
void Tuple::add(TupleValue *value) {
  values_.emplace_back(value);
}
void Tuple::add(const std::shared_ptr<TupleValue> &other) {
  values_.emplace_back(other);
}
void Tuple::add(int value) {
  add(new IntValue(value));
}

void Tuple::add(float value) {
  add(new FloatValue(value));
}

void Tuple::add(const char *s, int len) {
  add(new StringValue(s, len));
}

////////////////////////////////////////////////////////////////////////////////

std::string TupleField::to_string() const {
  return std::string(table_name_) + "." + field_name_ + std::to_string(type_);
}

////////////////////////////////////////////////////////////////////////////////
void TupleSchema::from_table(const Table *table, TupleSchema &schema) {
  const char *table_name = table->name();
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = 0; i < field_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i);
    if (field_meta->visible()) {
      schema.add(field_meta->type(), table_name, field_meta->name());
    }
  }
}

void TupleSchema::from_select(const char *table_name, const char *field_name, TupleSchema &schema, const TupleSchema &full_schema){
  const int size = full_schema.fields().size();
  for (int i = 0; i < size; i++) {
    const TupleField &field = full_schema.fields()[i];
    if(table_name == nullptr && field_name == nullptr){
      schema.add(field.type(), field.table_name(), field.field_name());
    }
    if(table_name == nullptr && field_name != nullptr){
      if (0 == strcmp(field.field_name(), field_name)) {
        schema.add(field.type(), field.table_name(), field.field_name());
      }
    }
    if(table_name != nullptr && field_name == nullptr){
      if (0 == strcmp(field.table_name(), table_name)) {
        schema.add(field.type(), field.table_name(), field.field_name());
      }
    }
    if(table_name != nullptr && field_name != nullptr){
      if (0 == strcmp(field.table_name(), table_name) && 0 == strcmp(field.field_name(), field_name)){
        schema.add(field.type(), field.table_name(), field.field_name());
      }
    }
  }
}

void TupleSchema::add(AttrType type, const char *table_name, const char *field_name) {
  fields_.emplace_back(type, table_name, field_name);
}

void TupleSchema::add_if_not_exists(AttrType type, const char *table_name, const char *field_name) {
  for (const auto &field: fields_) {
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name)) {
      return;
    }
  }

  add(type, table_name, field_name);
}

void TupleSchema::append(const TupleSchema &other) {
  fields_.reserve(fields_.size() + other.fields_.size());
  for (const auto &field: other.fields_) {
    fields_.emplace_back(field);
  }
}

int TupleSchema::index_of_field(const char *table_name, const char *field_name) const {
  const int size = fields_.size();
  for (int i = 0; i < size; i++) {
    const TupleField &field = fields_[i];
    if (0 == strcmp(field.table_name(), table_name) && 0 == strcmp(field.field_name(), field_name)) {
      return i;
    }
  }
  return -1;
}

void TupleSchema::print(std::ostream &os, bool isMoreTable) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }

  // 判断有多张表还是只有一张表
  std::set<std::string> table_names;
  for (const auto &field: fields_) {
    table_names.insert(field.table_name());
  }

  for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
       iter != end; ++iter) {
    if (table_names.size() > 1 || isMoreTable) {
      os << iter->table_name() << ".";
    }
    os << iter->field_name() << " | ";
  }

  if (table_names.size() > 1 || isMoreTable) {
    os << fields_.back().table_name() << ".";
  }
  os << fields_.back().field_name() << std::endl;
}

/////////////////////////////////////////////////////////////////////////////
TupleSet::TupleSet(TupleSet &&other) : tuples_(std::move(other.tuples_)), schema_(other.schema_){
  other.schema_.clear();
}

TupleSet &TupleSet::operator=(TupleSet &&other) {
  if (this == &other) {
    return *this;
  }

  schema_.clear();
  schema_.append(other.schema_);
  other.schema_.clear();

  tuples_.clear();
  tuples_.swap(other.tuples_);
  return *this;
}

void TupleSet::add(Tuple &&tuple) {
  tuples_.emplace_back(std::move(tuple));
}

void TupleSet::clear() {
  tuples_.clear();
  schema_.clear();
}

void TupleSet::print(std::ostream &os, bool isMoreTable) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }
  schema_.print(os, isMoreTable);

  for (const Tuple &item : tuples_) {
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
          iter != end; ++iter) {
      (*iter)->to_string(os);
      os << " | ";
    }
    values.back()->to_string(os);
    os << std::endl;
  }
}

void TupleSet::print_poly(std::ostream &os, std::string poly_type) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }
  if (poly_type.find("1") != -1){
    poly_type.pop_back();
    os << poly_type;
    os << "(";
    std::stringstream ss_tmp;
    schema_.print(ss_tmp, false);
    std::string tmp = ss_tmp.str();
    tmp.pop_back();
    if (tmp.find("|") != -1){
      tmp = "1";
    }
    os << tmp;
    os << ")\n";
  }
  else{
    os << poly_type;
    os << "(";
    std::stringstream ss_tmp;
    schema_.print(ss_tmp, false);
    std::string tmp = ss_tmp.str();
    tmp.pop_back();
    if (tmp.find("|") != -1){
      tmp = "*";
    }
    os << tmp;
    os << ")\n";
  }
  

  std::set<std::string> lines;
  std::vector<float> lines1;

  for (const Tuple &item : tuples_) {
    std::stringstream tmp;
    tmp.str("");
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
          iter != end; ++iter) {
      (*iter)->to_string(tmp);
      tmp << " | ";
    }
    values.back()->to_string(tmp);
    // os << std::endl;
    lines.insert(tmp.str());
    if (poly_type == "avg"){
      // if tmp.str().lengh()
      std::string tmp1 = tmp.str();
      // tmp1.pop_back();
      if (tmp1.size() > 0){
        lines1.push_back(std::stof(tmp1));
      }
      
    }
  }
  if(poly_type == "count"){
    int countv = 0;
    countv = lines.size();
    os << std::to_string(countv);
    os << std::endl;
  }
  else if(poly_type == "max"){
    os << *(lines.rbegin());
    os << std::endl;
  }
  else if(poly_type == "min"){
    os << *lines.begin();
    os << std::endl;
  }
  else{//avg
    // add all values
    float avg = 0.0;
    if(lines1.size()>0){
      for(int k=0;k<lines1.size();k++){
        avg = avg+lines1[k];
      }
      avg = avg/lines1.size();
    }
    // os << std::to_string(avg);
    os << avg;
    os << std::endl;
  }
}

int TupleSet::splitStringToVect(const std::string & srcStr, std::vector<std::string> & destVect, const std::string & strFlag) const {
    int pos = srcStr.find(strFlag, 0);
    int startPos = 0;
    int splitN = pos;
    std::string lineText(strFlag);
 
    while (pos > -1)
    {
        lineText = srcStr.substr(startPos, splitN);
        startPos = pos + 1;
        pos = srcStr.find(strFlag, pos + 1);
        splitN = pos - startPos;
        destVect.push_back(lineText);
    }
 
    lineText = srcStr.substr(startPos, srcStr.length() - startPos);
    destVect.push_back(lineText); 
 
    return destVect.size();
}

int TupleSet::in_needlist(std::vector<int> & needattrlist, int flag) const{
  int i;
  for(i=0; i<needattrlist.size();i++){
    if (needattrlist[i] == flag){
      return 1;
    }
  }
  return 0;
}

void TupleSet::get_needattr(std::vector<std::string> & lines, const int needattr, std::vector<int> & needattrlist) const{
  if(needattr != -2){
    //选出第needattr列
    for (const Tuple &item : tuples_) {
      std::stringstream tmp;
      tmp.str("");
      int flag=0;
      const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
      for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
            iter != end; ++iter) {
        if (flag == needattr){
          (*iter)->to_string(tmp);
          // tmp << " | ";
        }
        flag++;
      }
      if (flag == needattr){
        values.back()->to_string(tmp);
      }
      lines.push_back(tmp.str());
    }

  }
  else if(needattrlist.size()>0){
    //选出某几列
    for (const Tuple &item : tuples_) {
      std::stringstream tmp;
      tmp.str("");
      int flag=0;
      const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
      for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
            iter != end; ++iter) {
        if (in_needlist(needattrlist, flag)){
          (*iter)->to_string(tmp);
          tmp << " | ";
        }
        // if (std::find(needattrlist.begin(), needattrlist.end(), flag) != needattrlist.end()){
        //   (*iter)->to_string(tmp);
        //   tmp << " | ";
        // }
        flag++;
      }
      if (in_needlist(needattrlist, flag)){
        values.back()->to_string(tmp);
        lines.push_back(tmp.str());
      }
      else{
        std::string tmp1 = tmp.str();
        tmp1 = tmp1.substr(0, tmp1.length() - 3);
        lines.push_back(tmp1);
      }
    }
  }
  else{
    //all
    for (const Tuple &item : tuples_) {
      std::stringstream tmp;
      tmp.str("");
      const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
      for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
            iter != end; ++iter) {
        (*iter)->to_string(tmp);
        tmp << " | ";
      }
      values.back()->to_string(tmp);
      lines.push_back(tmp.str());
    }

  }
}

std::string TupleSet::cal_res(std::vector<std::string> & lines, const std::string polyname) const {
  if (polyname == "avg"){
    float avg = 0.0;
    if(lines.size()>0){
      for(int k=0;k<lines.size();k++){
        avg = avg + std::stof(lines[k]);
      }
      avg = avg/lines.size();
    }
    std::stringstream ss1;
    FloatValue avg_result = FloatValue(avg);
    avg_result.to_string(ss1);
    return ss1.str();
  }
  std::set<std::string> lines1;
  for(int k=0;k<lines.size();k++){
    lines1.insert(lines[k]);
  }
  if(polyname == "count"){
    int countv = 0;
    countv = lines1.size();
    return std::to_string(countv);
    // os << std::to_string(countv);
    // os << std::endl;
  }
  else if(polyname == "max"){
    std::stringstream ss1;
    ss1 << *lines1.rbegin();
    std::string tmp = ss1.str();
    return tmp;
    // os << *(lines.rbegin());
    // os << std::endl;
  }
  else if(polyname == "min"){
    std::stringstream ss1;
    ss1 << *lines1.begin();
    std::string tmp = ss1.str();
    return tmp;
  }
  else{
    // 异常情况
    return "";
  }
}


void TupleSet::print_poly_new(std::ostream &os, const Selects &selects) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }
  // 遍历poly_list
  int i;
  std::vector<std::string> results;
  std::string attri_tmp = "";
  for(i=0;i<selects.poly_num;i++){
    std::cout << "start ======================" << std::endl;
    std::cout << "poly id:" << i << std::endl;
    std::vector<std::string> lines;
    std::vector<int> needattrlist;
    int needattr = -2;
    
    // 针对关联attribute计算result
    if (selects.poly_list[i].attr_num != 1){
      // 异常情况
      std::cout << "there are more than one attri" << std::endl;
    }
    const Poly &po = selects.poly_list[i];
    std::cout << "get po " << std::endl;
    std::cout << "po.attr_num " << po.attr_num << std::endl;
    std::cout << "po.poly_name " << po.poly_name << std::endl;
    std::cout << "==========" << std::endl;

    std::stringstream ss0;
    ss0 << po.poly_name;
    attri_tmp = attri_tmp + ss0.str();
    attri_tmp = attri_tmp + "(";
    // std::cout << "attri_tmp: " << attri_tmp << std::endl;
    const RelAttr &attr = po.attributes[0];
    // std::cout << "get attr" << std::endl;

    std::stringstream ss;
    ss << attr.attribute_name;
    std::string attri = ss.str();
    // std::cout << "attri " << attri << std::endl;
    if (attri.find("*") != -1){
      // 获得selects.poly_list[i].attributes[0]->relation_name对应的所有attributes
      if(attr.relation_name){
        std::stringstream ss1;
        ss1 << attr.relation_name;
        std::string tbl = ss1.str();
        //std::string tbl = attr.relation_name;
        attri_tmp = attri_tmp+tbl;
        attri_tmp = attri_tmp+".*)";
        //筛选tbl
        std::stringstream ss_tmp;
        schema_.print(ss_tmp,false);
        std::string tmp = ss_tmp.str();
        tmp.pop_back();
        tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
        if (tmp.find("|") != -1){
          std::vector<std::string> spl;
          int attrnum = splitStringToVect(tmp, spl, "|");
          for (int k=0;k<attrnum; k++){
            if (spl[k].find(tbl) != -1){
              needattrlist.push_back(k);
            }
          }
          //根据needattrlist查找出需要的那几列到lines里面
          get_needattr(lines,needattr,needattrlist);
        }
        else if(tmp.find(tbl) != -1){
          //all
          get_needattr(lines,needattr,needattrlist);
        }
        else{
          //没选出需要的列，异常
        }
      }
      else{
        //all
        attri_tmp = attri_tmp + "*)";
        get_needattr(lines,needattr,needattrlist);
      }
    }
    else{//指定了某个具体的列
      std::string needattrname;
      if(attr.relation_name){
        std::stringstream ss1;
        ss1 << attr.relation_name;
        std::string tbl = ss1.str();
        //std::string tbl = attr.relation_name;
        //std::string attri = attr.attribute_name;
        attri_tmp = attri_tmp+tbl;
        attri_tmp = attri_tmp+".";
        attri_tmp = attri_tmp+attri;
        attri_tmp = attri_tmp+")";
        needattrname = tbl+"."+attri;
        std::cout << "needattrname " << needattrname << std::endl;
        //筛选tbl.attr
      }
      else{
        //std::string attri = attr.attribute_name;
        attri_tmp = attri_tmp+attri;
        attri_tmp = attri_tmp+")";
        needattrname = attri;
        std::cout << "needattrname " << needattrname << std::endl;
        //筛选 attr
      }
      std::stringstream ss_tmp;
      schema_.print(ss_tmp,false);
      std::string tmp = ss_tmp.str();
      tmp.pop_back();
      tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
      std::cout << "schema_: " << tmp << std::endl;
      if (tmp.find("|") != -1){
        std::vector<std::string> spl;
        int attrnum = splitStringToVect(tmp, spl, "|");
        for (int k=0;k<attrnum; k++){
          if (spl[k] == needattrname){
            needattr = k;
            break;
          }
        }
      }
      //else 只有一列：肯定是我们需要的那列
      //根据needattr查找出需要的那1列到lines里面/或者all
      std::cout << "0_get_needattr " << needattr << std::endl;
      get_needattr(lines,needattr,needattrlist);
      std::cout << "1_get_needattr: " << needattr << std::endl;
      if (lines.size()>0){
        std::cout << "lines example: " << lines[0] << std::endl;
      }
      // 针对lines计算结果
    }
    std::string res;
    res = cal_res(lines, po.poly_name);
    results.push_back(res);

    if (i < selects.poly_num-1){
      attri_tmp = attri_tmp + " | ";
    }
  }
  os << attri_tmp;
  os << "\n";
  for (int k=0;k<results.size();k++){
    os << results[k];
    if (k != results.size()-1){
      os << " | ";
    }
  }
  os << std::endl;

}

void TupleSet::set_schema(const TupleSchema &schema) {
  schema_ = schema;
}

const TupleSchema &TupleSet::get_schema() const {
  return schema_;
}

bool TupleSet::is_empty() const {
  return tuples_.empty();
}

int TupleSet::size() const {
  return tuples_.size();
}

const Tuple &TupleSet::get(int index) const {
  return tuples_[index];
}

const std::vector<Tuple> &TupleSet::tuples() const {
  return tuples_;
}

/////////////////////////////////////////////////////////////////////////////
TupleRecordConverter::TupleRecordConverter(Table *table, TupleSet &tuple_set) :
      table_(table), tuple_set_(tuple_set){
}

void TupleRecordConverter::add_record(const char *record) {
  const TupleSchema &schema = tuple_set_.schema();
  Tuple tuple;
  const TableMeta &table_meta = table_->table_meta();
  for (const TupleField &field : schema.fields()) {
    const FieldMeta *field_meta = table_meta.field(field.field_name());
    assert(field_meta != nullptr);
    switch (field_meta->type()) {
      case DATES: {
        int value = *(int*)(record + field_meta->offset());
        
        std::cerr<<"---int_value:"<<value<<std::endl;
        char date[20];
        int a=0;
        a = value % 10;
        date[9] = (char)(48+a);
        value /= 10;
        a = value % 10;
        date[8] = (char)(48+a);
        date[7] = '-';
        value /= 10;
        a = value % 10; 
        date[6] = (char)(48+a);
        value /= 10;
        a = value % 10;
        date[5] = (char)(48+a);
        date[4] = '-';
        value /= 10;
        a = value % 10;
        date[3] = (char)(48+a);
        value /= 10;
        a = value % 10;
        date[2] = (char)(48+a);
        value /= 10;
        a = value % 10;
        date[1] = (char)(48+a);
        value /= 10;
        a = value % 10;
        date[0] = (char)(48+a);
        date[10] = '\0';
        tuple.add(date, strlen(date));
        std::cerr<<"---date:"<<date<<std::endl;
      }
      break;
      case INTS: {
        int value = *(int*)(record + field_meta->offset());
        tuple.add(value);
      }
      break;
      case FLOATS: {
        float value = *(float *)(record + field_meta->offset());
        tuple.add(value);
      }
        break;
      case CHARS: {
        const char *s = record + field_meta->offset();  // 现在当做Cstring来处理
        tuple.add(s, strlen(s));
      }
      break;
      default: {
        LOG_PANIC("Unsupported field type. type=%d", field_meta->type());
      }
    }
  }

  tuple_set_.add(std::move(tuple));
}


