#include <cxxtest/TestSuite.h>

#define private public
#define protected public

#include "tst_tool/banner.hpp"

#include "../include/ThreadPool.hpp"


class TaskExecTestSuite : public CxxTest::TestSuite
{
public:

  void testIncrementTask()
  {
    banner("Incrementing static variable");
    ThreadPool tp;
    Worker wo(tp);
    TS_ASSERT_EQUALS( wo.m_isalive, true );
    TS_ASSERT_EQUALS( wo.m_isactive, false );
    TS_ASSERT_EQUALS( wo.m_workerstask, nullptr );

    ThreadPool* tpptr = &tp;
    ThreadPool* tpptr2 = &wo.m_threadpool;
    TS_ASSERT_EQUALS( tpptr, tpptr2 );
  }

};
