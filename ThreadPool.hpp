#ifndef THREADPOOL_HPP_INCLUDED
#define THREADPOOL_HPP_INCLUDED

#define BOOST_THREAD_USE_LIB
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "Worker.hpp"

class ThreadPool
{
  public:
    ~ThreadPool();
    void create_workers();
    //Task* pop_task();
    //void push_task( Task& task );

  private:
    std::vector< Worker* > m_workers;
    //TASK LIST from which worker will pop
};

ThreadPool::~ThreadPool()
{
  for( auto member : m_workers )
  {
    delete member;
  }
}

void ThreadPool::create_workers()
{
  for( unsigned i = 0; i < 4; ++i )
  {
    m_workers.push_back( new Worker( this ) );
  }
}


#endif // THREADPOOL_HPP_INCLUDED
