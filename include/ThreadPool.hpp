#ifndef THREADPOOL_HPP_INCLUDED
#define THREADPOOL_HPP_INCLUDED

#define BOOST_THREAD_USE_LIB
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <memory>

#include "Tracer.hpp"
#include "Worker.hpp"
#include "TaskList.hpp"

#ifndef NUM_OF_THREADS
  #define NUM_OF_THREADS 4
#endif

class ThreadPool
{
  public:
    ~ThreadPool();
    void create_workers();
    void activate_workers();
    void deactivate_workers();
    void push_task( Task* task ) { m_tptasks.push_task( task ); }

  private:
    std::vector< std::shared_ptr< Worker > > m_workers;
    TaskList m_tptasks;
};

ThreadPool::~ThreadPool()
{
  TRACE("ThreadPool destruction commencing...");
  if( !m_workers.empty() )
  {
    deactivate_workers();
    m_workers.clear();
    TRACE("ThreadPool voided");
  }
  TRACE("ThreadPool destroyed");
}

void ThreadPool::create_workers()
{
  TRACE("ThreadPool creating workers...");
  for( unsigned i = 0; i < NUM_OF_THREADS; ++i )
  {
    m_workers.push_back( std::shared_ptr< Worker >( new Worker( this ) ) );
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
