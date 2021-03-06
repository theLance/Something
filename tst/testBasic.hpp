#include <cxxtest/TestSuite.h>

#define private public
#define protected public

#include "tst_tool/banner.hpp"

#include "../include/ThreadPool.hpp"

class FakeTask : public Task
{
  public:
    void run() { TRACE("Running fake task..."); while(0){} }
};

class BasicTestSuite : public CxxTest::TestSuite
{
public:

  void testCreateTp()
  {
    banner("Instantiation");
    ThreadPool tp;
    Worker wo(tp);
  }

  void testInitTp()
  {
    banner("Initialization");
    ThreadPool tp;
    Worker wo(tp);
    TS_ASSERT_EQUALS( wo.m_isalive, true );
    TS_ASSERT_EQUALS( wo.m_isactive, false );
    TS_ASSERT_EQUALS( wo.m_workerstask, nullptr );

    ThreadPool* tpptr = &tp;
    ThreadPool* tpptr2 = &wo.m_threadpool;
    TS_ASSERT_EQUALS( tpptr, tpptr2 );
  }

  void testCreateWorkers()
  {
    banner("Create worker threads");
    ThreadPool tp;
    Worker wo(tp);
    TS_ASSERT_EQUALS( tp.m_workers.size(), 0 );
    tp.create_workers();
    TS_ASSERT_EQUALS( tp.m_workers.size(), 4 );
  }

  void testWorkerActivateDeactivate()
  {
    banner("Activate worker");
    ThreadPool tp;
    Worker wo(tp);
    TS_ASSERT_EQUALS( wo.m_isactive, false );
    wo.activate();
    TS_ASSERT_EQUALS( wo.m_isactive, true );
    banner("Deactivate worker");
    wo.deactivate();
    TS_ASSERT_EQUALS( wo.m_isactive, false );
  }

  void testTpActivateDeactivateWorkers()
  {
    banner("TP: Activate workers");
    ThreadPool tp;
    Worker wo(tp);
    tp.create_workers();
    for( auto worker : tp.m_workers )
    {
      TS_ASSERT_EQUALS( worker->m_isactive, false );
    }
    tp.activate_workers();
    for( auto worker : tp.m_workers )
    {
      TS_ASSERT_EQUALS( worker->m_isactive, true );
    }
    banner("TP: Deactivate workers");
    tp.deactivate_workers();
    for( auto worker : tp.m_workers )
    {
      TS_ASSERT_EQUALS( worker->m_isactive, false );
    }
  }

  void testTpWorkerIds()
  {
    banner("TP: Worker IDs");
    ThreadPool tp;
    tp.create_workers();
    std::stringstream strstm;
    std::string numstr;

    for( unsigned i = 0; i < NUM_OF_THREADS; i++ )
    {
      strstm << (i+1) << " ";
      strstm >> numstr;
      TS_ASSERT_EQUALS( i+1, tp.m_workers[i]->get_id() );
      TS_ASSERT_EQUALS( numstr, tp.m_workers[i]->get_id_str() );
    }
  }

/*********************************************/
  void testTaskList()
  {
    banner("TaskList");
    TaskList tl;
    FakeTask ft;
    Task* taskptr = &ft;
    Task* testptr = nullptr;

    banner("Insertion");
    tl.push_task( taskptr );
    TS_ASSERT_DIFFERS( 0, tl.m_tasks.size() );

    banner("Extraction");
    testptr = tl.pop_task();
    TS_ASSERT_DIFFERS( nullptr, testptr );

    banner("No pop when empty - safety check");
    TS_ASSERT_EQUALS( 0, tl.m_tasks.size() );
    testptr = tl.pop_task();
    TS_ASSERT_EQUALS( nullptr, testptr );
  }

  void testAddTaskToTp()
  {
    banner("TP: Add task");
    ThreadPool tp;
    FakeTask ft;
    Task* taskptr = &ft;
    Task* testptr = nullptr;

    banner("Insertion");
    tp.push_task( taskptr );
    TS_ASSERT_DIFFERS( 0, tp.m_tptasks.m_tasks.size() );
    TS_ASSERT_EQUALS( taskptr, tp.m_tptasks.m_tasks.front() );
  }

};
