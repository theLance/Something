#ifndef THREADPOOL_HPP_INCLUDED
#define THREADPOOL_HPP_INCLUDED

#define BOOST_THREAD_USE_LIB
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <memory>

#include "Worker.hpp"

#ifndef NUM_OF_THREADS
  #define NUM_OF_THREADS 4
#endif


class ThreadPool
{
  public:
    virtual ~ThreadPool();

    void create_workers();
    void activate_workers();
    void deactivate_workers();
    void interrupt_worker( unsigned id ) { m_workers[id-1]->interrupt(); }

    void push_task( Task* task ) { TRACE("Pushing task to TP"); m_tptasks.push_task( task ); }
    Task* pop_task() { return m_tptasks.pop_task(); }

  private:
    std::vector< std::shared_ptr< Worker > > m_workers;
    TaskList m_tptasks;
};


#endif // THREADPOOL_HPP_INCLUDED
