#include <cxxtest/TestSuite.h>

#define private public
#define protected public

///------REMOVE LATER (when tracing works as it should)
#define TRACE_OFF
///------

#include "tst_tool/banner.hpp"

#include "../ThreadPool.hpp"


class TestSuite : public CxxTest::TestSuite
{
public:
  void testCreateTp()
  {
    banner("Instantiation");
    ThreadPool tp;
    Worker wo(&tp);
  }

  void testInitTp()
  {
    banner("Initialization");
    ThreadPool tp;
    Worker wo(&tp);
    TS_ASSERT_EQUALS( wo.m_isalive, true );
    TS_ASSERT_EQUALS( wo.m_isactive, false );
    TS_ASSERT_EQUALS( &tp, wo.m_threadpool );
  }

  void testCreateWorkers()
  {
    banner("Create worker threads");
    ThreadPool tp;
    Worker wo(&tp);
    TS_ASSERT_EQUALS( tp.m_workers.size(), 0 );
    tp.create_workers();
    TS_ASSERT_EQUALS( tp.m_workers.size(), 4 );
  }

  void testWorkerActivateDeactivate()
  {
    banner("Activate worker");
    ThreadPool tp;
    Worker wo(&tp);
    TS_ASSERT_EQUALS( wo.m_isactive, false );
    wo.activate();
    TS_ASSERT_EQUALS( wo.m_isactive, true );
    banner("Deactivate worker");
    wo.deactivate();
    TS_ASSERT_EQUALS( wo.m_isactive, false );
  }

  void testTpActivateDeactivateWorkers()
  {
    banner("TP Activate workers");
    ThreadPool tp;
    Worker wo(&tp);
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
    banner("TP Deactivate workers");
    tp.deactivate_workers();
    for( auto worker : tp.m_workers )
    {
      TS_ASSERT_EQUALS( worker->m_isactive, false );
    }
  }
};
