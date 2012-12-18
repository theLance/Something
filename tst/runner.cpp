/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    status = CxxTest::Main<CxxTest::ErrorPrinter>( tmp, argc, argv );
    return status;
}
bool suite_TestSuite_init = false;
#include "test.hpp"

static TestSuite suite_TestSuite;

static CxxTest::List Tests_TestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestSuite( "test.hpp", 10, "TestSuite", suite_TestSuite, Tests_TestSuite );

static class TestDescription_suite_TestSuite_testCreateTp : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestSuite_testCreateTp() : CxxTest::RealTestDescription( Tests_TestSuite, suiteDescription_TestSuite, 13, "testCreateTp" ) {}
 void runTest() { suite_TestSuite.testCreateTp(); }
} testDescription_suite_TestSuite_testCreateTp;

static class TestDescription_suite_TestSuite_testInitTp : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestSuite_testInitTp() : CxxTest::RealTestDescription( Tests_TestSuite, suiteDescription_TestSuite, 20, "testInitTp" ) {}
 void runTest() { suite_TestSuite.testInitTp(); }
} testDescription_suite_TestSuite_testInitTp;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
