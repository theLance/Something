#include <iostream>
#include "ThreadPool.hpp"

void awaken()
{
  std::cout << "I'm awake" << std::endl;
}

int main()
{
  boost::thread m_worker( &awaken );
  m_worker.join();

  ThreadPool tp;
  Worker wo(&tp);
  boost::this_thread::sleep(boost::posix_time::seconds(1));
  wo.activate();
  std::cout << "Activated..." << std::endl;

  for( int i = 0; i < 10; ++i )
    std::cout << i << std::endl;

  return 0;
}
