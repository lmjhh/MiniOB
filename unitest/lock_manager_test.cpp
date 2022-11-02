/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights rcerved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPrcS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */
//
// Created by lianyu on 2022/9/14.
//
#include <thread>
#include "storage/trx/lock_manager.h"
#include <future>
#include "gtest/gtest.h"

TEST(LockManagerTest, BasicTest) {
  LockManager lock_mgr{false};
  RID rid{0, 0};

  std::thread t0([&] {
    Trx *trx = new Trx(lock_mgr);
    RC rc = lock_mgr.lock_shared(trx, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx->get_state(), Trx::State::GROWING);
    trx->commit();
    ASSERT_EQ(trx->get_state(), Trx::State::COMMITTED);
  });

  std::thread t1([&] {
    Trx *trx = new Trx(lock_mgr);
    RC rc = lock_mgr.lock_shared(trx, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx->get_state(), Trx::State::GROWING);
    trx->commit();
    ASSERT_EQ(trx->get_state(), Trx::State::COMMITTED);
  });

  t0.join();
  t1.join();
}

TEST(LockManagerTest, LockSharedTest) {
  LockManager lock_mgr{false};
  RID rid{0, 0};

  Trx *trxs[10];
  for (int i = 0; i < 10; i++) {
    trxs[i] = new Trx(lock_mgr);
    ASSERT_EQ(lock_mgr.lock_shared(trxs[i], rid), RC::SUCCESS);
    ASSERT_EQ(Trx::State::GROWING, trxs[i]->get_state());
  }
  for (auto &trx : trxs) {
    trx->commit();
    ASSERT_EQ(Trx::State::COMMITTED, trx->get_state());
    delete trx;
  }
}

TEST(LockManagerTest, BasicExclusiveTest) {
  LockManager lock_mgr{false};
  RID rid{0, 0};

  std::promise<void> go, p0, p1, p2;
  std::shared_future<void> ready(go.get_future());

  Trx *trx1 = new Trx(lock_mgr);
  Trx *trx2 = new Trx(lock_mgr);
  Trx *trx3 = new Trx(lock_mgr);

  std::thread t0([&, ready] {
    RC rc = lock_mgr.lock_exclusive(trx3, rid);

    p0.set_value();
    ready.wait();

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx3->get_state(), Trx::State::GROWING);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    rc = lock_mgr.unlock(trx3, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx3->get_state(), Trx::State::SHRINKING);
  });

  std::thread t1([&, ready] {

    p1.set_value();
    ready.wait();

    RC rc = lock_mgr.lock_shared(trx2, rid);

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx2->get_state(), Trx::State::GROWING);

    rc = lock_mgr.unlock(trx2, rid);

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx2->get_state(), Trx::State::SHRINKING);

  });

  std::thread t2([&, ready] {

    p2.set_value();
    ready.wait();

    // wait for t1
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    RC rc = lock_mgr.lock_shared(trx1, rid);

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx1->get_state(), Trx::State::GROWING);

    rc = lock_mgr.unlock(trx1, rid);

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx1->get_state(), Trx::State::SHRINKING);

  });

  p0.get_future().wait();
  p1.get_future().wait();
  p2.get_future().wait();

  go.set_value();

  t0.join();
  t1.join();
  t2.join();
}

TEST(LockManagerTest, LockExclusiveTest) {
  LockManager lock_mgr{false};
  RID rid{0, 0};

  {
    Trx trx0{lock_mgr};
    Trx trx1{lock_mgr};
    Trx trx2{lock_mgr};

    std::mutex mu;
    ASSERT_EQ(RC::SUCCESS, lock_mgr.lock_shared(&trx1, rid));
    ASSERT_EQ(Trx::State::GROWING, trx1.get_state());

    std::thread t([&] {
      ASSERT_EQ(RC::SUCCESS, lock_mgr.lock_exclusive(&trx0, rid));
      ASSERT_EQ(Trx::State::GROWING, trx0.get_state());
      {
        std::lock_guard<std::mutex> lock{mu};
        ASSERT_EQ(Trx::State::COMMITTED, trx1.get_state());
      }
      trx0.commit();
      ASSERT_EQ(Trx::State::COMMITTED, trx0.get_state());
    });
    
    RID rid1{0, 1};
    ASSERT_EQ(RC::SUCCESS, lock_mgr.lock_exclusive(&trx2, rid1));
    ASSERT_EQ(Trx::State::GROWING, trx2.get_state());
    trx2.commit();
    ASSERT_EQ(Trx::State::COMMITTED, trx2.get_state());

    {
      std::lock_guard<std::mutex> lock{mu};
      trx1.commit();
      ASSERT_EQ(Trx::State::COMMITTED, trx1.get_state());
    }
    t.join();
  }

  {

    Trx trx0{lock_mgr};
    Trx trx1{lock_mgr};

    std::mutex mu;
    ASSERT_EQ(RC::SUCCESS, lock_mgr.lock_exclusive(&trx1, rid));
    ASSERT_EQ(Trx::State::GROWING, trx1.get_state());

    std::thread t([&] {
      ASSERT_EQ(RC::SUCCESS, lock_mgr.lock_exclusive(&trx0, rid));
      ASSERT_EQ(Trx::State::GROWING, trx0.get_state());
      {
        std::lock_guard<std::mutex> lock{mu};
        ASSERT_EQ(Trx::State::COMMITTED, trx1.get_state());
      }
      trx0.commit();
      ASSERT_EQ(Trx::State::COMMITTED, trx0.get_state());
    });

    {
      std::lock_guard<std::mutex> lock{mu};
      trx1.commit();
      ASSERT_EQ(Trx::State::COMMITTED, trx1.get_state());
    }
    t.join();
  }
}


TEST(LockManagerTest, 2plTest) {
  LockManager lock_mgr{false};
  Trx trx{lock_mgr};
  RID rid0{0,0}, rid1{0,1};

  ASSERT_EQ(RC::SUCCESS, lock_mgr.lock_shared(&trx, rid0));
  ASSERT_EQ(RC::SUCCESS, lock_mgr.unlock(&trx, rid0));
  ASSERT_EQ(Trx::State::SHRINKING, trx.get_state());
  ASSERT_EQ(RC::GENERIC_ERROR ,lock_mgr.lock_shared(&trx, rid1));
  ASSERT_EQ(Trx::State::ABORTED, trx.get_state());
}

TEST(LockManagerTest, S2plTest) {
  LockManager lock_mgr{true};
  RID rid{0,0};

  {
    Trx trx{lock_mgr};
    ASSERT_EQ(RC::SUCCESS, lock_mgr.lock_shared(&trx, rid));
    ASSERT_EQ(RC::GENERIC_ERROR, lock_mgr.unlock(&trx, rid));
    ASSERT_EQ(Trx::State::ABORTED, trx.get_state());
  }

  {
    Trx trx{lock_mgr};
    ASSERT_EQ(RC::SUCCESS, lock_mgr.lock_shared(&trx, rid));
    trx.set_state(Trx::State::COMMITTED);
    ASSERT_EQ(RC::SUCCESS, lock_mgr.unlock(&trx, rid));
  }
}

TEST(LockManagerTest, BasicTest1) {
  LockManager lock_mgr{false};
  RID rid{0, 0};

  std::promise<void> go, t0, t1, t2;
  std::shared_future<void> ready(go.get_future());

  Trx trx0{lock_mgr};
  Trx trx1{lock_mgr};
  Trx trx2{lock_mgr};
  
  std::thread thread0([&, ready] {
    
    // will block and can wait
    RC rc = lock_mgr.lock_shared(&trx1, rid);

    t0.set_value();
    ready.wait();

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx1.get_state(), Trx::State::GROWING);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // unlock
    rc = lock_mgr.unlock(&trx1, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx1.get_state(), Trx::State::SHRINKING);
  });

  
  std::thread thread1([&, ready] {

    // will block and can wait
    RC rc = lock_mgr.lock_shared(&trx2, rid);

    t1.set_value();
    ready.wait();

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx2.get_state(), Trx::State::GROWING);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // unlock
    rc = lock_mgr.unlock(&trx2, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx2.get_state(), Trx::State::SHRINKING);
  });

  
  std::thread thread2([&, ready] {

    t2.set_value();
    ready.wait();

    // can wait and will block
    RC rc = lock_mgr.lock_exclusive(&trx0, rid);

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx0.get_state(), Trx::State::GROWING);

    rc = lock_mgr.unlock(&trx0, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx0.get_state(), Trx::State::SHRINKING);
  });

  t0.get_future().wait();
  t1.get_future().wait();
  t2.get_future().wait();

  // go!
  go.set_value();

  thread0.join();
  thread1.join();
  thread2.join();
}


TEST(LockManagerTest, BasicTest2) {
  LockManager lock_mgr{false};
  
  RID rid{0, 0};
  
  std::promise<void> go, t0, t1, t2;
  std::shared_future<void> ready(go.get_future());
  Trx trx{lock_mgr};
  Trx trx1{lock_mgr};
  Trx trx2{lock_mgr};
  
  std::thread thread0([&, ready] {
    

    t0.set_value();
    ready.wait();

    // let thread1 try to acquire shared lock first
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // will block and can wait
    RC rc = lock_mgr.lock_shared(&trx, rid);

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx.get_state(), Trx::State::GROWING);

    // unlock
    rc = lock_mgr.unlock(&trx, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx.get_state(), Trx::State::SHRINKING);
  });

  std::thread thread1([&, ready] {

    t1.set_value();
    ready.wait();

    // will block and can wait
    RC rc = lock_mgr.lock_shared(&trx1, rid);

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx1.get_state(), Trx::State::GROWING);


    // unlock
    rc = lock_mgr.unlock(&trx1, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx1.get_state(), Trx::State::SHRINKING);
  });

  std::thread thread2([&, ready] {

    // can wait and will block
    RC rc = lock_mgr.lock_exclusive(&trx2, rid);

    t2.set_value();
    ready.wait();

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx2.get_state(), Trx::State::GROWING);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    rc = lock_mgr.unlock(&trx2, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx2.get_state(), Trx::State::SHRINKING);
  });

  t0.get_future().wait();
  t1.get_future().wait();
  t2.get_future().wait();

  // go!
  go.set_value();

  thread0.join();
  thread1.join();
  thread2.join();
}

// basic wait-die test
TEST(LockManagerTest, WaitDieTest) {
  LockManager lock_mgr{false};
  
  RID rid{0,0};

  std::promise<void> done;
  auto f = done.get_future();
  Trx trx0{lock_mgr};
  Trx trx1{lock_mgr};
  Trx trx2{lock_mgr};
  Trx trx3{lock_mgr};
  lock_mgr.lock_shared(&trx2, rid);
  ASSERT_NE(lock_mgr.lock_exclusive(&trx3, rid), RC::SUCCESS);

  std::thread t0([&] {
    done.set_value();
    ASSERT_EQ(lock_mgr.lock_exclusive(&trx0, rid), RC::SUCCESS);
    lock_mgr.unlock(&trx0, rid);
  });
  f.get();
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  ASSERT_NE(lock_mgr.lock_exclusive(&trx1, rid), RC::SUCCESS);
  ASSERT_EQ(lock_mgr.unlock(&trx2, rid), RC::SUCCESS);
  t0.join();
}


TEST(LockManagerTest, DeadlockTest1) {
  LockManager lock_mgr{false};
  
  RID rid{0, 0};

  std::promise<void> go, go2, t1, t2;
  std::shared_future<void> ready(go.get_future());
  Trx trx{lock_mgr};
  Trx trx1{lock_mgr};
  
  std::thread thread0([&, ready] {
    
    RC rc = lock_mgr.lock_shared(&trx, rid);

    t1.set_value();
    ready.wait();

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx.get_state(), Trx::State::GROWING);

    // waiting thread2 call lock_exclusive before unlock
    go2.get_future().wait();

    // unlock
    rc = lock_mgr.unlock(&trx, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx.get_state(), Trx::State::SHRINKING);
  });

  std::thread thread1([&, ready] {
//    Trx trx(1);

    // wait thread t0 to get shared lock first
    t2.set_value();
    ready.wait();

    RC rc = lock_mgr.lock_exclusive(&trx1, rid);
    go2.set_value();

    ASSERT_NE(rc, RC::SUCCESS);
    ASSERT_EQ(trx1.get_state(), Trx::State::ABORTED);
  });

  t1.get_future().wait();
  t2.get_future().wait();

  // go!
  go.set_value();

  thread0.join();
  thread1.join();
}

TEST(LockManagerTest, DeadlockTest2) {
  LockManager lock_mgr{false};
  
  RID rid{0, 0};

  std::promise<void> go, t1, t2;
  std::shared_future<void> ready(go.get_future());

  Trx trx{lock_mgr};
  Trx trx1{lock_mgr};
  std::thread thread0([&, ready] {


    t1.set_value();
    ready.wait();

    // will block and can wait
    RC rc = lock_mgr.lock_shared(&trx, rid);

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx.get_state(), Trx::State::GROWING);

    // unlock
    rc = lock_mgr.unlock(&trx, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx.get_state(), Trx::State::SHRINKING);
  });

  std::thread thread1([&, ready] {
//    Trx trx(1);

    RC rc = lock_mgr.lock_exclusive(&trx1, rid);

    t2.set_value();
    ready.wait();

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx1.get_state(), Trx::State::GROWING);

    rc = lock_mgr.unlock(&trx1, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx1.get_state(), Trx::State::SHRINKING);
  });

  t1.get_future().wait();
  t2.get_future().wait();

  // go!
  go.set_value();

  thread0.join();
  thread1.join();
}

TEST(LockManagerTest, DeadlockTest3) {
  LockManager lock_mgr{false};
  
  RID rid{0, 0};
  RID rid2{0, 1};

  std::promise<void> go, t1, t2;
  std::shared_future<void> ready(go.get_future());

  Trx trx{lock_mgr};
  Trx trx1{lock_mgr};
  std::thread thread0([&, ready] {


    // try get exclusive lock on rid2, will succeed
    RC rc = lock_mgr.lock_exclusive(&trx, rid2);

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx.get_state(), Trx::State::GROWING);

    t1.set_value();
    ready.wait();

    // will block and can wait
    rc = lock_mgr.lock_shared(&trx, rid);

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx.get_state(), Trx::State::GROWING);

    // unlock rid1
    rc = lock_mgr.unlock(&trx, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx.get_state(), Trx::State::SHRINKING);

    // unblock rid2
    rc = lock_mgr.unlock(&trx, rid2);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx.get_state(), Trx::State::SHRINKING);
  });

  std::thread thread1([&, ready] {
//    Trx trx(1);

    // try to get shared lock on rid, will succeed
    RC rc = lock_mgr.lock_exclusive(&trx1, rid);

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx1.get_state(), Trx::State::GROWING);

    t2.set_value();
    ready.wait();

    rc = lock_mgr.lock_shared(&trx1, rid2);
    ASSERT_NE(rc, RC::SUCCESS);
    ASSERT_EQ(trx1.get_state(), Trx::State::ABORTED);

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // unlock rid
    rc = lock_mgr.unlock(&trx1, rid);

    ASSERT_EQ(rc, RC::SUCCESS);

    if (trx1.get_state() == Trx::State::GROWING) {
      LOG_INFO("rcult of young lock state is growing");
    }
    if (trx1.get_state() == Trx::State::ABORTED) {
      LOG_INFO("rcult of young lock state is ABORTED");
    }
    if (trx1.get_state() == Trx::State::SHRINKING) {
      LOG_INFO("rcult of young lock state is SHRINKING");
    }
    ASSERT_EQ(trx1.get_state(), Trx::State::ABORTED);
  });

  t1.get_future().wait();
  t2.get_future().wait();

  // go!
  go.set_value();

  thread0.join();
  thread1.join();
}

TEST(LockManagerTest, AbortOnExclusiveLockTest)
{
  LockManager lock_mgr{false};

  RID rid{0, 0};
  bool flag1 = false;
  Trx trx{lock_mgr};
  Trx trx1{lock_mgr};

  std::thread t0([&]
      {

        RC rc = lock_mgr.lock_shared(&trx, rid);
        ASSERT_EQ(rc, RC::SUCCESS);
        ASSERT_EQ(trx.get_state(), Trx::State::GROWING);
        flag1 = true;
        // let the other thread run
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ASSERT_EQ(trx.get_state(), Trx::State::GROWING);
        trx.commit();
        ASSERT_EQ(trx.get_state(), Trx::State::COMMITTED);
        assert (trx.get_shared_lockset()->empty() == true);
        assert (trx.get_exclusive_lockset()->empty() == true);
      });
  std::thread t1([&]
      {
        while (flag1 == false)
          ; // wait for t0 to acquire the exclusive lock
        RC rc = lock_mgr.lock_exclusive(&trx1, rid);
        ASSERT_NE(rc, RC::SUCCESS);
        assert (trx1.get_shared_lockset()->empty() == true);
        assert (trx1.get_exclusive_lockset()->empty() == true);
      });
  t0.join();
  t1.join();
}

TEST(LockManagerTest, SharedExclusiveTestWithDeadlock)
{
  LockManager lock_mgr{false};
  

  RID rid{0, 0};
  bool flag = false;

  Trx trx{lock_mgr};
  Trx trx1{lock_mgr};
  std::thread t0([&]
      {

        RC rc = lock_mgr.lock_exclusive(&trx, rid);
        ASSERT_EQ(rc, RC::SUCCESS);
        // let the other thread run
        flag = true;
        // sleep for 1 second
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ASSERT_EQ(trx.get_state(), Trx::State::GROWING);
        trx.commit();
        ASSERT_EQ(trx.get_state(), Trx::State::COMMITTED);
        assert (trx.get_shared_lockset()->empty() == true);
        assert (trx.get_exclusive_lockset()->empty() == true);
      });
  std::thread t1([&]
      {
//        Trx trx(1);
        while (flag == false)
          ; // spin for the flag to become true
        // this will fail because the timestamp of trx1 > tstamp of t0
        RC rc = lock_mgr.lock_shared(&trx1, rid);
        ASSERT_NE(rc, RC::SUCCESS);
        assert (trx1.get_shared_lockset()->empty() == true);
        assert (trx1.get_exclusive_lockset()->empty() == true);
      });
  t0.join();
  t1.join();

}


TEST(LockManagerTest, LockUpgradeTest) {
  LockManager lock_mgr{false};
  RID rid{0, 0};
  
  {
    Trx trx{lock_mgr};
    ASSERT_NE(lock_mgr.lock_upgrade(&trx, rid), RC::SUCCESS);
    ASSERT_EQ(Trx::State::ABORTED, trx.get_state());
    trx.rollback();
  }

  
  {
    Trx trx0{lock_mgr};
    ASSERT_EQ(lock_mgr.lock_exclusive(&trx0, rid), RC::SUCCESS);
    ASSERT_NE(lock_mgr.lock_upgrade(&trx0, rid), RC::SUCCESS);
    ASSERT_EQ(Trx::State::ABORTED, trx0.get_state());
    trx0.rollback();
  }

  {
    Trx trx0{lock_mgr};
    ASSERT_EQ(lock_mgr.lock_shared(&trx0, rid), RC::SUCCESS);
    ASSERT_EQ(lock_mgr.lock_upgrade(&trx0, rid), RC::SUCCESS);
    trx0.commit();
  }

  {
    std::mutex mu;
    Trx trx0{lock_mgr};
    Trx trx1{lock_mgr};
    ASSERT_EQ(lock_mgr.lock_shared(&trx1, rid), RC::SUCCESS);

    std::thread t([&] {
      ASSERT_EQ(lock_mgr.lock_shared(&trx0, rid), RC::SUCCESS);
      ASSERT_EQ(lock_mgr.lock_upgrade(&trx0, rid), RC::SUCCESS);
      {
        std::lock_guard<std::mutex> lock{mu};
        ASSERT_EQ(Trx::State::COMMITTED, trx1.get_state());
      }
      trx0.commit();
      ASSERT_EQ(Trx::State::COMMITTED, trx0.get_state());
    });

    {
      std::lock_guard<std::mutex> lock{mu};
      trx1.commit();
      ASSERT_EQ(Trx::State::COMMITTED, trx1.get_state());
    }
    t.join();
  }
}

TEST(LockManagerTest, BasicUpgradeTest) {
  LockManager lock_mgr{false};
  RID rid{0, 0};

  std::promise<void> go, p0, p1, p2, p3;
  std::shared_future<void> ready(go.get_future());

  Trx trx{lock_mgr};
  Trx trx1{lock_mgr};
  Trx trx2{lock_mgr};
  Trx trx3{lock_mgr};
  std::thread t0([&, ready] {

    RC rc = lock_mgr.lock_shared(&trx, rid);

    p0.set_value();
    ready.wait();

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx.get_state(), Trx::State::GROWING);

    // update
    rc = lock_mgr.lock_upgrade(&trx, rid);

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx.get_state(), Trx::State::GROWING);

    rc = lock_mgr.unlock(&trx, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx.get_state(), Trx::State::SHRINKING);
  });

  std::thread t1([&, ready] {

    RC rc = lock_mgr.lock_shared(&trx1, rid);

    p1.set_value();
    ready.wait();

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx1.get_state(), Trx::State::GROWING);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    rc = lock_mgr.unlock(&trx1, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx1.get_state(), Trx::State::SHRINKING);
  });

  std::thread t2([&, ready] {
    RC rc = lock_mgr.lock_shared(&trx2, rid);

    p2.set_value();
    ready.wait();

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx2.get_state(), Trx::State::GROWING);

    rc = lock_mgr.unlock(&trx2, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx2.get_state(), Trx::State::SHRINKING);
  });

  std::thread t3([&, ready] {
    RC rc = lock_mgr.lock_shared(&trx3, rid);

    p3.set_value();
    ready.wait();

    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx3.get_state(), Trx::State::GROWING);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    rc = lock_mgr.unlock(&trx3, rid);
    ASSERT_EQ(rc, RC::SUCCESS);
    ASSERT_EQ(trx3.get_state(), Trx::State::SHRINKING);
  });

  p0.get_future().wait();
  p1.get_future().wait();
  p2.get_future().wait();
  p3.get_future().wait();

  go.set_value();

  t0.join();
  t1.join();
  t2.join();
  t3.join();
}



/*

 TEST(LockManagerTest, LockUpgradeTest2)
{
 LockManager lock_mgr{false};


RID rid{0, 0};
bool flag = false;
bool flag1 = false;
bool flag2 = false;
Trx trx{lock_mgr};
Trx trx1{lock_mgr};
Trx trx2{lock_mgr};
std::thread t0([&]
   {

     RC rc = lock_mgr.lock_shared(&trx, rid);
     flag2 = true; // t0 should acquire the shared lock first
     // to avoid the die scenario in deadlock prevention
     ASSERT_EQ(rc, RC::SUCCESS);
     ASSERT_EQ(trx.get_state(), Trx::State::GROWING);
     while (flag == false || flag1 == false)
       ; // wait for t1 and t2 to acquire the shared lock on rid
     bool rc1 = lock_mgr.lock_upgrade(&trx, rid);
     ASSERT_EQ(rc1, true);
     ASSERT_EQ(trx.get_state(), Trx::State::GROWING);
     trx.commit();
     ASSERT_EQ(trx.get_state(), Trx::State::COMMITTED);
     assert (trx.get_shared_lockset()->empty() == true);
     assert (trx.get_exclusive_lockset()->empty() == true);
   });
std::thread t1([&]
   {

     while (flag2 == false)
       ; // wait for t0 to acquire the exclusive lock
     RC rc = lock_mgr.lock_shared(&trx1, rid);
     flag = true;
     ASSERT_EQ(rc, RC::SUCCESS);
     // let t0 run, t0 should be stuck waiting for t1 to release
     // the shared lock
     // sleep for 1 second
     std::this_thread::sleep_for(std::chrono::milliseconds(100));
     trx1.commit();
     ASSERT_EQ(trx1.get_state(), Trx::State::COMMITTED);
     assert (trx1.get_shared_lockset()->empty() == true);
     assert (trx1.get_exclusive_lockset()->empty() == true);
   });
std::thread t2([&]
   {

     while (flag2 == false)
       ; // wait for t0 to acquire the exclusive lock
     RC rc = lock_mgr.lock_shared(&trx2, rid);
     flag1 = true;
     ASSERT_EQ(rc, RC::SUCCESS);
     // let t0 run, t0 should be stuck waiting for t2 to release
     // the shared lock
     // sleep for 1 second
     std::this_thread::sleep_for(std::chrono::milliseconds(100));
     trx2.commit();
     ASSERT_EQ(trx2.get_state(), Trx::State::COMMITTED);
     assert (trx2.get_shared_lockset()->empty() == true);
     assert (trx2.get_exclusive_lockset()->empty() == true);
   });
t0.join();
t1.join();
t2.join();

}

TEST(LockManagerTest, SharedExclusiveTestWithoutDeadlock)
{
  LockManager lock_mgr{false};

  RID rid{0, 0};
  RID rid1{0, 1};
  bool flag = false;
  bool flag1 = false;

  Trx trx{lock_mgr};
  Trx trx1{lock_mgr};
  std::thread t0([&]
      {

        RC rc = lock_mgr.lock_exclusive(&trx, rid);
        ASSERT_EQ(rc, RC::SUCCESS);
        ASSERT_EQ(trx.get_state(), Trx::State::GROWING);
        flag1 = true;
        while (flag == false)
          ; // wait for t1 to acquire the lock on rid1
        RC rc1 = lock_mgr.lock_exclusive(&trx, rid1);
        ASSERT_EQ(rc1, RC::SUCCESS);
        ASSERT_EQ(trx.get_state(), Trx::State::GROWING);
        trx.commit();
        ASSERT_EQ(trx.get_state(), Trx::State::COMMITTED);
        assert (trx.get_shared_lockset()->empty() == true);
        assert (trx.get_exclusive_lockset()->empty() == true);
      });
  std::thread t1([&]
      {
//        Trx trx(1);

        while (flag1 == false)
          ; // wait for t0 to acquire the exclusive lock
        RC rc = lock_mgr.lock_shared(&trx1, rid1);
        flag = true;
        ASSERT_EQ(rc, RC::SUCCESS);
        // let the other thread run
        // sleep for 1 second
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        trx1.commit();
        ASSERT_EQ(trx1.get_state(), Trx::State::COMMITTED);
        assert (trx1.get_shared_lockset()->empty() == true);
        assert (trx1.get_exclusive_lockset()->empty() == true);
      });
  t0.join();
  t1.join();
}



TEST(LockManagerTest, WaitingOnSharedLockTest)
{
  LockManager lock_mgr{false};

  RID rid{0, 0};
  RID rid1{0, 1};
  bool flag = false;
  bool flag1 = false;

  Trx trx{lock_mgr};
  Trx trx1{lock_mgr};
  std::thread t0([&]
      {

        RC rc = lock_mgr.lock_shared(&trx, rid);
        ASSERT_EQ(rc, RC::SUCCESS);
        ASSERT_EQ(trx.get_state(), Trx::State::GROWING);
        flag1 = true;
        while (flag == false)
          ; // wait for t1 to acquire the lock on rid1
        printf("1\n");
        RC rc1 = lock_mgr.lock_shared(&trx, rid1);

        ASSERT_EQ(rc1, RC::SUCCESS);
        ASSERT_EQ(trx.get_state(), Trx::State::GROWING);
        trx.commit();
        ASSERT_EQ(trx.get_state(), Trx::State::COMMITTED);
        assert (trx.get_shared_lockset()->empty() == true);
        assert (trx.get_exclusive_lockset()->empty() == true);
      });
  std::thread t1([&]
      {
        while (flag1 == false)
          ; // wait for t0 to acquire the exclusive lock
        RC rc = lock_mgr.lock_exclusive(&trx1, rid1);
        flag = true;
        ASSERT_EQ(rc, RC::SUCCESS);
        // let the other thread run
        // sleep for 1 second
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        trx1.commit();
        ASSERT_EQ(trx1.get_state(), Trx::State::COMMITTED);

        assert (trx1.get_shared_lockset()->empty() == true);
        assert (trx1.get_exclusive_lockset()->empty() == true);
      });
  t0.join();
  t1.join();
}

TEST(LockManagerTest, AbortOnlock_upgrade)
{
  LockManager lock_mgr{false};


RID rid{0, 0};
bool flag1 = false;

Trx trx{lock_mgr};
Trx trx1{lock_mgr};
std::thread t0([&]
    {

      while (flag1 == false)
        ; // wait for the other thread to acquire the shared lock
      RC rc = lock_mgr.lock_shared(&trx, rid);
      ASSERT_EQ(rc, RC::SUCCESS);
      ASSERT_EQ(trx.get_state(), Trx::State::GROWING);
      bool rc1 = lock_mgr.lock_upgrade(&trx, rid);
      ASSERT_EQ(rc1, true);
      trx.commit();
      ASSERT_EQ(trx.get_state(), Trx::State::COMMITTED);
      assert (trx.get_shared_lockset()->empty() == true);
      assert (trx.get_exclusive_lockset()->empty() == true);
    });
std::thread t1([&]
    {

      RC rc = lock_mgr.lock_shared(&trx1, rid);
      flag1 = true;
      ASSERT_EQ(rc, RC::SUCCESS);
      // let the other thread run
      // sleep for 1 second
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      bool rc1 = lock_mgr.lock_upgrade(&trx1, rid);
      ASSERT_EQ(rc1, false);
      trx1.abort();

      assert (trx.get_shared_lockset()->empty() == true);
      assert (trx.get_exclusive_lockset()->empty() == true);
    });
t0.join();
t1.join();
}
*/





int main(int argc, char **argv)
{

  // 分析gtest程序的命令行参数
  testing::InitGoogleTest(&argc, argv);

  // 调用RUN_ALL_TESTS()运行所有测试用例
  // main函数返回RUN_ALL_TESTS()的运行结果

  int rc = RUN_ALL_TESTS();

  return rc;
}


