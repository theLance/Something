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
  LambdaTask testtask_increment;
  LambdaTask testtask_empty;
  LambdaTask testtask_wait;
  LambdaTask testtask_interrupt;
  LambdaTask testtask_interrupt_macro;

public:
  TaskExecTestSuite() : testtask_increment( [](){ Incrementor::testnum++; } )
                      , testtask_empty( [](){} )
                      , testtask_wait( [&](){ while( 0 == Incrementor::testnum ){} } )
                      , testtask_interrupt( [](){
                                            while( 0 == Incrementor::testnum )
                                            {
                                              boost::this_thread::interruption_point();
                                            } })
                      , testtask_interrupt_macro( [](){
                                            while( 0 == Incrementor::testnum )
                                            {
                                              INTERRUPT;
                                            } })
  {
  }

  void setUp()
  {
    m_tp = new ThreadPool;
    m_tp->create_workers();
    Incrementor::testnum = 0;
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

    for( unsigned i = 0; i < 50; i++ )
    {
      m_tp->push_task( &testtask_increment );
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

    TS_ASSERT_EQUALS( false, m_tp->m_workers[0]->get_is_busy() );
    m_tp->m_workers[0]->m_workerstask = &testtask_empty;
    TS_ASSERT_EQUALS( true, m_tp->m_workers[0]->get_is_busy() );
    m_tp->m_workers[0]->m_workerstask = NULL;
    TS_ASSERT_EQUALS( false, m_tp->m_workers[0]->get_is_busy() );

    banner("Busy indicator test - live");
    m_tp->push_task( &testtask_wait );

    TS_ASSERT_EQUALS( false, m_tp->m_workers[0]->get_is_busy() );
    m_tp->m_workers[0]->activate();
    //wait for worker to pop task
    boost::this_thread::sleep(boost::posix_time::millisec(50));
    TS_ASSERT_EQUALS( true, m_tp->m_workers[0]->get_is_busy() );
    Incrementor::testnum = 1;
    boost::this_thread::sleep(boost::posix_time::millisec(50));
    TS_ASSERT_EQUALS( false, m_tp->m_workers[0]->get_is_busy() );
  }

  void testInterrupt()
  {
    banner("Control of interrupt - classical");

    m_tp->push_task( &testtask_interrupt );
    m_tp->m_workers[0]->activate();
    while ( false == m_tp->m_workers[0]->get_is_busy() ) {}
    m_tp->interrupt_worker(1);
    boost::this_thread::sleep(boost::posix_time::millisec(50));
    TS_ASSERT_EQUALS( false, m_tp->m_workers[0]->get_is_busy() );

    banner("Control of interrupt - macro");

    m_tp->push_task( &testtask_interrupt_macro );
    while ( false == m_tp->m_workers[0]->get_is_busy() ) {}
    m_tp->interrupt_worker(1);
    boost::this_thread::sleep(boost::posix_time::millisec(50));
    TS_ASSERT_EQUALS( false, m_tp->m_workers[0]->get_is_busy() );
  }

  void testNoInterruptWhenIdle()
  {
    banner("Control of interrupt - No Interrupt when idle");

    for( auto worker : m_tp->m_workers )
    {
      worker->interrupt();
    }
    m_tp->activate_workers();

    for( auto worker : m_tp->m_workers )
    {
      worker->interrupt();
    }

    for( auto worker : m_tp->m_workers )
    {
      m_tp->push_task( &testtask_wait );
    }

    while ( !m_tp->m_tptasks.m_tasks.empty() ) {}
    boost::this_thread::sleep(boost::posix_time::millisec(50));
    for( auto worker : m_tp->m_workers )
    {
      TS_ASSERT_EQUALS( true, worker->get_is_busy() );
    }

    Incrementor::testnum = 1;
    boost::this_thread::sleep(boost::posix_time::millisec(50));
    for( auto worker : m_tp->m_workers )
    {
      TS_ASSERT_EQUALS( false, worker->get_is_busy() );
    }
  }

};
