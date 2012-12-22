#ifndef THREADPOOL_HPP_INCLUDED
#define THREADPOOL_HPP_INCLUDED

#define BOOST_THREAD_USE_LIB
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <algorithm>

#include "Tracer.hpp"
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
  TRACE("ThreadPool destruction commencing...");
  if( !m_workers.empty() )
  {
    deactivate_workers();
    for( auto worker : m_workers )
    {
      delete worker;
    }
    m_workers.clear();
    TRACE("ThreadPool voided");
  }
  TRACE("ThreadPool destroyed");
}

void ThreadPool::create_workers()
{
  TRACE("ThreadPool creating workers...");
  for( unsigned i = 0; i < 4; ++i )
  {
    m_workers.push_back( new Worker( this ) );
  }
  TRACE("ThreadPool workers created");
}

void ThreadPool::activate_workers()
{
  TRACE("ThreadPool activating workers...");
  for( auto worker : m_workers )
  {
    worker->activate();
  }
  TRACE("ThreadPool workers activated");
}

void ThreadPool::deactivate_workers()
{
  TRACE("ThreadPool deactivating workers...");
  for( auto worker : m_workers )
  {
    worker->deactivate();
  }
  TRACE("ThreadPool workers deactivated");
}

#endif // THREADPOOL_HPP_INCLUDED
