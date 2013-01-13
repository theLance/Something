#include <cxxtest/TestSuite.h>

#define private public
#define protected public

#include "tst_tool/banner.hpp"

#include "../include/Tracer.hpp"


class TracerTestSuite : public CxxTest::TestSuite
{
public:

  void testTracer()
  {
    banner("Tracer write test");

    STracer::getinstance();
    STracer::m_data->m_logfile.flush();

    std::ifstream log;
    log.open("log.txt");
    TS_ASSERT_DIFFERS( log.good() , 0 );

    std::string logtest;
    std::getline( log, logtest );
    TS_ASSERT_EQUALS( logtest, "Logfile created" );

    #ifndef TRACE_OFF
    log.seekg( 0, std::ios::end );
    #endif

    STracer::getinstance()->trace("test");
    std::getline( log, logtest );
    TS_ASSERT_EQUALS( logtest, "test" );

    #ifndef TRACE_OFF
    TRACE("test2");
    std::getline( log, logtest );
    TS_ASSERT_EQUALS( logtest, "test2" );
    #endif
  }

  ///TEST THROW FOR LOGFILE REOPEN ATTEMPT

};
