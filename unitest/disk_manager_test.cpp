//
// Created by lianyu on 2022/10/29.
//

#include "storage/disk/disk_manager.h"
#include "gtest/gtest.h"

TEST(DiskManagerTest, BasicTest) {
  DiskManager *manager = new DiskManager();
  int fd;
  manager->create_file("test.db");
  manager->open_file("test.db", fd);
  manager->write_page(fd, 1, "123451512415213513535");
  manager->close_file("test.db");
}

int main(int argc, char **argv)
{

  // 分析gtest程序的命令行参数
  testing::InitGoogleTest(&argc, argv);

  // 调用RUN_ALL_TESTS()运行所有测试用例
  // main函数返回RUN_ALL_TESTS()的运行结果

  int rc = RUN_ALL_TESTS();

  return rc;
}