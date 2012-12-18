#include <cxxtest/TestSuite.h>

#define private public
#define protected public

#include "../ThreadPool.hpp"
#include "tst_tool/banner.hpp"


class TestSuite : public CxxTest::TestSuite
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
    TS_ASSERT_EQUALS( wo.m_isactive, false );
    TS_ASSERT_EQUALS( &tp, &wo.m_threadpool );
  }

};
