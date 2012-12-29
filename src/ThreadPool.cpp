
#include "../include/ThreadPool.hpp"

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
