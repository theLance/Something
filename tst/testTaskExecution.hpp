#include <cxxtest/TestSuite.h>

#define private public
#define protected public

#include "tst_tool/banner.hpp"

#include "../include/ThreadPool.hpp"

class Incrementor
{
  public:
    volatile static unsigned testnum;
};

volatile unsigned Incrementor::testnum = 0;

class TaskExecTestSuite : public CxxTest::TestSuite
{
private:
  ThreadPool* m_tp;

public:

  void setUp()
  {
    m_tp = new ThreadPool;
    m_tp->create_workers();
  }

  void tearDown()
  {
    if( m_tp )
    {
      delete m_tp;
    }
  }

  void testIncrementTask()
  {
    banner("Incrementing a variable");
    LambdaTask testtask( [](){ Incrementor::testnum++; } );

    for( unsigned i = 0; i < 50; i++ )
    {
      m_tp->push_task( &testtask );
    }
    m_tp->activate_workers();
    while( !m_tp->m_tptasks.m_tasks.empty() ) {}
    //wait for last Worker to finish task
    boost::this_thread::sleep(boost::posix_time::millisec(50));
    TS_ASSERT_EQUALS( Incrementor::testnum, 50 );
  }

  void testBusyIndicator()
  {
    banner("Busy indicator test - artificial");
    LambdaTask testtask( [](){} );

    TS_ASSERT_EQUALS( false, m_tp->m_workers[0]->get_is_busy() );
    m_tp->m_workers[0]->m_workerstask = &testtask;
    TS_ASSERT_EQUALS( true, m_tp->m_workers[0]->get_is_busy() );
    m_tp->m_workers[0]->m_workerstask = NULL;
    TS_ASSERT_EQUALS( false, m_tp->m_workers[0]->get_is_busy() );

    banner("Busy indicator test - live");
    Incrementor::testnum = 0;
    LambdaTask testtaskwait( [&](){ while( 0 == Incrementor::testnum ){} } );
    m_tp->push_task( &testtaskwait );

    TS_ASSERT_EQUALS( false, m_tp->m_workers[0]->get_is_busy() );
    m_tp->m_workers[0]->activate();
    //wait for worker to pop task
    boost::this_thread::sleep(boost::posix_time::millisec(50));
    TS_ASSERT_EQUALS( true, m_tp->m_workers[0]->get_is_busy() );
    Incrementor::testnum = 1;
    m_tp->m_workers[0]->m_workerstask = NULL;
    TS_ASSERT_EQUALS( false, m_tp->m_workers[0]->get_is_busy() );
  }

};
