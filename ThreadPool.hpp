#ifndef THREADPOOL_HPP_INCLUDED
#define THREADPOOL_HPP_INCLUDED

#define BOOST_THREAD_USE_LIB
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <algorithm>

#include "Worker.hpp"

class ThreadPool
{
  public:
    ~ThreadPool();
    void create_workers();
    void activate_workers();
    void deactivate_workers();
    //Task* pop_task();
    //void push_task( Task& task );

  private:
    std::vector< Worker* > m_workers;
    //TASK LIST from which worker will pop
};

ThreadPool::~ThreadPool()
{
  if( !m_workers.empty() )
  {
    deactivate_workers();
    for( auto worker : m_workers )
    {
      delete worker;
    }
    m_workers.clear();
    std::cout << "\nThreadPool voided\n";
  }
  std::cout << "\nThreadPool destroyed\n";
}

void ThreadPool::create_workers()
{
  for( unsigned i = 0; i < 4; ++i )
  {
    m_workers.push_back( new Worker( this ) );
  }
}

void ThreadPool::activate_workers()
{
  for( auto worker : m_workers )
  {
    worker->activate();
  }
  std::cout << "Workers activated..." << std::endl;
}

void ThreadPool::deactivate_workers()
{
  for( auto worker : m_workers )
  {
    worker->deactivate();
  }
  std::cout << "Workers deactivated..." << std::endl;
}

#endif // THREADPOOL_HPP_INCLUDED
