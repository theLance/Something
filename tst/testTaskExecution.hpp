#include <cxxtest/TestSuite.h>

#define private public
#define protected public

#include "tst_tool/banner.hpp"

#include "../include/ThreadPool.hpp"

class Incrementor
{
  public:
    static unsigned testnum;
};

unsigned Incrementor::testnum = 0;

class TaskExecTestSuite : public CxxTest::TestSuite
{
public:

  void testIncrementTask()
  {
    LambdaTask testtask( [](){ Incrementor::testnum++; } );
    banner("Incrementing a variable");
    ThreadPool tp;
    tp.create_workers();
    for( unsigned i = 0; i < 50; i++ )
    {
      tp.push_task( &testtask );
    }
    tp.activate_workers();
    while( !tp.m_tptasks.m_tasks.empty() ) {}
    TS_ASSERT_EQUALS( Incrementor::testnum, 50 );
  }

};
