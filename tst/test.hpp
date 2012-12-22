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
    Worker wo(&tp);
  }

  void testInitTp()
  {
    banner("Initialization");
    ThreadPool tp;
    Worker wo(&tp);
    TS_ASSERT_EQUALS( wo.m_isalive, true );
    TS_ASSERT_EQUALS( wo.m_isactive, false );
    TS_ASSERT_EQUALS( ( wo.m_worker != 0 ), true );
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

    for( auto i = tp.m_workers.begin(); i != tp.m_workers.end(); ++i )
      std::cout << std::boolalpha << (*i)->m_isactive;

    std::cout << std::boolalpha << wo.m_isactive;
  }
};
