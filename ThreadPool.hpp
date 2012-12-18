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
    explicit Worker( ThreadPool& tp ) : m_threadpool( tp ), m_isalive( true ),
                                        m_isactive( false ), m_worker( 0 ) { awaken(); }
    ~Worker() { if( m_worker != 0 ) delete m_worker; }

    void activate() { m_isactive = true; }
    void deactivate() { m_isactive = false; }
    //void join() {};
  private:
    bool m_isactive;
    bool m_isalive;
    ThreadPool& m_threadpool;
    void awaken();
    void execute_tasks();
    boost::thread* m_worker;
};

void Worker::awaken()
{
  m_worker = new boost::thread( [&](){
                                  while( m_isalive )
                                  {
                                    execute_tasks();
                                    //fine-tune sleep mechanism later!!!
                                    boost::this_thread::sleep(boost::posix_time::seconds(1));
                                  } } );
}

void Worker::execute_tasks()
{
  while( m_isactive )
  {
    //m_threadpool->pop_task()
  }
}

#endif // THREADPOOL_HPP_INCLUDED
