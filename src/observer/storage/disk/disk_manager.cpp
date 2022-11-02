//
// Created by lianyu on 2022/10/28.
//

#include "disk_manager.h"
#include "common/log/log.h"
#include <fcntl.h>
#include <stdio.h>
#include <map>
#include "rc.h"
#include "common/io/io.h"
#include "storage/buffer/frame.h"

DiskFileIterator::DiskFileIterator()
{}
DiskFileIterator::~DiskFileIterator()
{}
RC DiskFileIterator::init(int file_desc, PageNum start_page /* = 0 */)
{
  DiskDataFile file;
  DiskManager::instance().get_disk_data_file(file_desc, file);
  bitmap_.init(file.file_header_->bitmap, file.file_header_->page_count);
  if (start_page <= 0) {
    current_page_num_ = 0;
  } else {
    current_page_num_ = start_page;
  }
  return RC::SUCCESS;
}

bool DiskFileIterator::has_next()
{
  return bitmap_.next_setted_bit(current_page_num_ + 1) != -1;
}

PageNum DiskFileIterator::next()
{
  PageNum next_page = bitmap_.next_setted_bit(current_page_num_ + 1);
  if (next_page != -1) {
    current_page_num_ = next_page;
  }
  return next_page;
}

RC DiskFileIterator::reset()
{
  current_page_num_ = 0;
  return RC::SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////


static std::atomic<int32_t> current_space_id(0);
#define Flush_SYS_INFO_Time (5)

void flush_sys_info(SYS_INFO info) {
  std::string sys_info_dir = "./miniob/sys.info";
  int fd = open(sys_info_dir.c_str(), O_RDWR);
  lseek(fd, sizeof(SYS_INFO), SEEK_SET);
  size_t write_size = 0;
  if ((write_size = write(fd, &info, sizeof(SYS_INFO))) != sizeof(SYS_INFO)) {
    LOG_ERROR("Failed to write sys_info");
  }
  close(fd);
}

SYS_INFO get_sys_info() {
  SYS_INFO info;
  std::string sys_info_dir = "./miniob/sys.info";
  int fd = open(sys_info_dir.c_str(), O_RDWR | O_CREAT | O_EXCL, S_IREAD | S_IWRITE);
  if (fd < 0) { //已存在，打开
    fd = open(sys_info_dir.c_str(), O_RDWR);
    lseek(fd, sizeof(SYS_INFO), SEEK_SET);
    size_t read_size = 0;
    if ((read_size = read(fd, &info, sizeof(SYS_INFO))) != sizeof(SYS_INFO)) {
      LOG_ERROR("Failed to open sys_info");
    }
  } else { //不存在，创建
    info.max_space_id = 0;
    flush_sys_info(info);
  }
  close(fd);
}

DiskManager::DiskManager()
{
  sys_info_ = get_sys_info();
  current_space_id = (sys_info_.max_space_id / Flush_SYS_INFO_Time) + Flush_SYS_INFO_Time;
  sys_info_.max_space_id = current_space_id;
  flush_sys_info(sys_info_);
}

RC DiskManager::create_data_file(const char *file_name, int &space_id)
{
  int fd = open(file_name, O_RDWR | O_CREAT | O_EXCL, S_IREAD | S_IWRITE);
  if (fd < 0) {
    LOG_ERROR("Failed to create %s, due to %s.", file_name, strerror(errno));
    return RC::SCHEMA_DB_EXIST;
  }

  close(fd);

  /**
   * Here don't care about the failure
   */
  fd = open(file_name, O_RDWR);
  if (fd < 0) {
    LOG_ERROR("Failed to open for readwrite %s, due to %s.", file_name, strerror(errno));
    return RC::IOERR_ACCESS;
  }

  Page page;
  memset(&page, 0, sizeof(Page));

  DiskDataFileHeader *file_header = (DiskDataFileHeader *)page.data;
  file_header->allocated_pages = 1;
  file_header->page_count = 1;


  char *bitmap = file_header->bitmap;
  bitmap[0] |= 0x01;
  if (lseek(fd, 0, SEEK_SET) == -1) {
    LOG_ERROR("Failed to seek file %s to position 0, due to %s .", file_name, strerror(errno));
    close(fd);
    return RC::IOERR_SEEK;
  }

  if (write(fd, &page, sizeof(Page)) < 0) {
    LOG_ERROR("Failed to write header to file %s, due to %s.", file_name, strerror(errno));
    close(fd);
    return RC::IOERR_WRITE;
  }

  close(fd);
  LOG_INFO("Successfully create %s.", file_name);

  sys_info_.max_space_id = current_space_id++;
  space_id = sys_info_.max_space_id;
  if (current_space_id % Flush_SYS_INFO_Time == 0) {
    flush_sys_info(sys_info_);
  }

  return RC::SUCCESS;
}

RC DiskManager::open_data_file(const char *file_name, int &file_desc)
{
  std::string file_name_string(file_name);

  if (opened_files_name_.find(file_name_string) != opened_files_name_.end()) {
    LOG_WARN("file already opened. file name=%s", file_name);
    return RC::FILE_OPEN;
  }

  file_desc = open(file_name, O_RDWR);
  if (file_desc < 0) {
    LOG_ERROR("Failed to open for readwrite %s, due to %s.", file_name, strerror(errno));
    return RC::IOERR_ACCESS;
  }


  DiskDataFile *file = new DiskDataFile();
  read(file_desc, &file->page_, sizeof(Page));
  file->file_name_ = file_name_string;
  file->file_desc_ = file_desc;
  file->file_header_ = (DiskDataFileHeader *)file->page_.data;

  opened_files_name_.insert(std::pair<std::string, DiskDataFile *>(file_name_string, file));
  opened_files_fd_.insert(std::pair<int, DiskDataFile *>(file_desc, file));

  return RC::SUCCESS;
}

RC DiskManager::dispose_page(int file_desc, int page_num)
{
  auto iter = opened_files_fd_.find(file_desc);
  if (iter == opened_files_fd_.end()) {
    return RC::FILE_NOT_OPENED;
  }
  iter->second->file_header_->allocated_pages--;
  char tmp = 1 << (page_num % 8);
  iter->second->file_header_->bitmap[page_num / 8] &= ~tmp;
  return RC::SUCCESS;
}

RC DiskManager::close_file(int file_desc)
{
  auto iter = opened_files_fd_.find(file_desc);
  if (iter == opened_files_fd_.end()) {
    return RC::FILE_NOT_OPENED;
  }
  DiskDataFile *file = iter->second;
  write_page(file->file_desc_, HEADER_PAGE_NUM, &file->page_);

  opened_files_fd_.erase(file_desc);
  opened_files_name_.erase(file->file_name_);
  return RC::SUCCESS;
}

RC DiskManager::get_disk_data_file(int file_desc, DiskDataFile &disk_data_file) {
  auto iter = opened_files_fd_.find(file_desc);
  if (iter == opened_files_fd_.end()) {
    return RC::FILE_NOT_OPENED;
  }
  disk_data_file = *iter->second;
  return RC::SUCCESS;
}

RC DiskManager::write_page(int file_desc, PageNum page_num, const void *page_data)
{
  auto iter = opened_files_fd_.find(file_desc);
  if (iter == opened_files_fd_.end()) {
    return RC::FILE_NOT_OPENED;
  }
  DiskDataFile *file = iter->second;
  int offset = page_num * sizeof(Page);
  if (lseek(file_desc, offset, SEEK_SET) == -1) {
    LOG_ERROR("Failed to load page %d:%d, due to failed to lseek:%s.",
        file->file_name_.c_str(), page_num, strerror(errno));
    return RC::IOERR_SEEK;
  }

  size_t write_size = 0;
  if ((write_size = write(file_desc, page_data, sizeof(Page))) != sizeof(Page)) {
    LOG_ERROR("Failed to write %llu of %d:%s due to %s. Write size: %lld", offset, file_desc, file->file_name_.c_str(), strerror(errno), write_size);
    return RC::IOERR_WRITE;
  }
  return RC::SUCCESS;
}

RC DiskManager::read_page(int file_desc, PageNum page_num, void *page_data)
{
  auto iter = opened_files_fd_.find(file_desc);
  if (iter == opened_files_fd_.end()) {
    return RC::FILE_NOT_OPENED;
  }
  DiskDataFile *file = iter->second;
  int offset = page_num * sizeof(Page);
  if (lseek(file_desc, offset, SEEK_SET) == -1) {
    LOG_ERROR("Failed to load page %s:%d, due to failed to lseek:%s.",
        file->file_name_.c_str(), page_num, strerror(errno));
    return RC::IOERR_SEEK;
  }
  size_t read_size = 0;
  if ((read_size = read(file_desc, page_data, sizeof(Page))) != sizeof(Page)) {
    LOG_ERROR("Failed to read %llu of %d:%s due to %s. Read size: %lld", offset, file_desc, file->file_name_.c_str(), strerror(errno), read_size);
    return RC::IOERR_READ;
  }
  return RC::SUCCESS;
}

PageNum DiskManager::allocate_new_page(int file_desc)
{
  auto iter = opened_files_fd_.find(file_desc);
  if (iter == opened_files_fd_.end()) {
    return INVALID_PAGE_NUM;
  }
  DiskDataFile *file = iter->second;

  int byte = 0, bit = 0;
  //1. 已分配的Page里有被删除的页
  if ((file->file_header_->allocated_pages) < (file->file_header_->page_count)) {
    for (int i = 0; i < file->file_header_->page_count; i++) {
      byte = i / 8;
      bit = i % 8;
      if (((file->file_header_->bitmap[byte]) & (1 << bit)) == 0) {
        (file->file_header_->allocated_pages)++;
        file->file_header_->bitmap[byte] |= (1 << bit);
        return i;
      }
    }
  }
  //2. 已经到单个文件上限
  if (file->file_header_->page_count >= DiskDataFileHeader::MAX_PAGE_NUM) {
    LOG_WARN("file is full. page count %d, max page count %d",
        file->file_header_->page_count, DiskDataFileHeader::MAX_PAGE_NUM);
    return INVALID_PAGE_NUM;
  }
  //3. 分配一个新的页
  PageNum page_num = file->file_header_->page_count;
  file->file_header_->allocated_pages++;
  file->file_header_->page_count++;

  byte = page_num / 8;
  bit = page_num % 8;
  file->file_header_->bitmap[byte] |= (1 << bit);
  return page_num;
}

DiskManager::~DiskManager()
{

}


static DiskManager *default_disk_manager = nullptr;
void DiskManager::set_instance(DiskManager *disk_manager)
{
  if (default_disk_manager != nullptr && disk_manager != nullptr) {
    LOG_ERROR("default disk manager has been setted");
    abort();
  }
  default_disk_manager = disk_manager;
}
DiskManager &DiskManager::instance()
{
  return *default_disk_manager;
}