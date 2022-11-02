//
// Created by lianyu on 2022/10/12.
//

#include "log_record.h"
#include "common/log/log.h"

#define LOG_INS_REC_NODATA_SIZE (sizeof(LogInsertRecord) - sizeof(char *))
#define LOG_DEL_REC_NODATA_SIZE (sizeof(LogDeleteRecord) - sizeof(char *))

LogRecord::LogRecord(Type type, int32_t lsn, int32_t  prev_lsn, int32_t trx_id, int data_len /* = 0 */, Record *rec /* = nullptr */)
{
  hdr_.trx_id_ = trx_id;
  hdr_.lsn_ = -1;
  hdr_.prev_lsn_ = prev_lsn;
  hdr_.type_ = type;

  switch (type) {
    case Type::BEGIN:
    case Type::ABORT:
    case Type::COMMIT: {
      hdr_.size_ = HEADER_SIZE;
    } break;
    case Type::INSERT: {
      if (!rec || !rec->data()) {
        LOG_ERROR("Record is null");
      } else {
        hdr_.size_ = data_len + LOG_INS_REC_NODATA_SIZE;

        log_record_.ins.rid_ = rec->rid();
        log_record_.ins.record_size_ = data_len;
        log_record_.ins.record_data_ = new char[hdr_.size_ - LOG_INS_REC_NODATA_SIZE];
        memcpy(log_record_.ins.record_data_, rec->data(), data_len);
      }
    } break;
    case Type::MARKDELETE:
    case Type::APPLYDELETE:
    case Type::ROLLBACKDELETE: {
      if (!rec) {
        LOG_ERROR("Record is null");
      } else {
        hdr_.size_ = data_len + LOG_DEL_REC_NODATA_SIZE;

        log_record_.del.rid_ = rec->rid();
        log_record_.del.record_size_ = data_len;
        log_record_.del.record_data_ = new char[hdr_.size_ - LOG_DEL_REC_NODATA_SIZE];
        memcpy(log_record_.del.record_data_, rec->data(), data_len);
      }
    } break;
    default:
      LOG_ERROR("type is error");
      break;
  }
}

int LogRecord::serialize_to(char *address)
{
  memcpy(address, &hdr_, LogRecord::HEADER_SIZE);
  int pos = LogRecord::HEADER_SIZE;

  switch (hdr_.type_) {
    case Type::INSERT: {
      memcpy(address + pos, &log_record_.ins.rid_, sizeof(RID));
      pos += sizeof(RID);
      memcpy(address + pos, &log_record_.ins.record_size_, sizeof(int32_t));
      pos += sizeof(sizeof(int32_t));
      memcpy(address + pos, log_record_.ins.record_data_, log_record_.ins.record_size_);
      pos += log_record_.ins.record_size_;
    } break;
    case Type::MARKDELETE:
    case Type::APPLYDELETE:
    case Type::ROLLBACKDELETE: {
      memcpy(address + pos, &log_record_.del.rid_, sizeof(RID));
      pos += sizeof(RID);
      memcpy(address + pos, &log_record_.del.record_size_, sizeof(int32_t));
      pos += sizeof(sizeof(int32_t));
      memcpy(address + pos, log_record_.del.record_data_, log_record_.del.record_size_);
      pos += log_record_.del.record_size_;
    } break;
    case Type::UPDATE: {

    } break;
    default: {
    }
  }
  return pos;
}

LogRecord::~LogRecord()
{

}