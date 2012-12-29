////////////////////////
#define private public
#define protected public
////////////////////////

#include <iostream>
#include "include/ThreadPool.hpp"


void awaken()
{
  std::cout << "I'm awake" << std::endl;
}


int main()
{
  boost::thread m_worker( &awaken );
  m_worker.join();
  {
  ThreadPool tp;
  Worker wo(tp);
  boost::this_thread::sleep(boost::posix_time::seconds(1));

  //---EARLY EXIT FOR TESTING---
//  return 0;

  tp.create_workers();
  std::cout << "MAIN: Workers created..." << std::endl;
  boost::this_thread::sleep(boost::posix_time::seconds(1));

  tp.activate_workers();
  std::cout << "MAIN: Workers activated..." << std::endl;
  for( int i = 0; i < 10; ++i )
    std::cout << i << std::endl;

  boost::this_thread::sleep(boost::posix_time::seconds(1));
//  tp.~ThreadPool();
//  std::cout << "After TP destructor was called..." << std::endl;
  boost::this_thread::sleep(boost::posix_time::seconds(1));
  std::cout << "MAIN: End of inner scope -------" << std::endl;
  }

  std::cout << "MAIN: Destroyed TP..." << std::endl;
  boost::this_thread::sleep(boost::posix_time::seconds(2));
  std::cout << "MAIN: All is said and done..." << std::endl;

  return 0;
}

