#ifndef THREADPOOL_HPP_INCLUDED
#define THREADPOOL_HPP_INCLUDED

#define BOOST_THREAD_USE_LIB
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class Worker;

class ThreadPool
{
  public:
    //Task* pop_task();
    //void push_task( Task& task );
  private:
    std::vector< Worker* > m_workers;
    //TASK LIST from which worker will pop
};

class Worker
{
  public:
    explicit Worker( ThreadPool& tp ) : m_threadpool( tp ), m_isactive( false ) {};
    void activate() { m_isactive = true; }
    void deactivate() { m_isactive = false; }
    void execute();
  private:
    bool m_isactive;
    ThreadPool& m_threadpool;
};

void Worker::execute()
{
  while( m_isactive )
  {
    //m_threadpool->pop_task()
  }
}

#endif // THREADPOOL_HPP_INCLUDED
