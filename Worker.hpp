#ifndef WORKER_H_INCLUDED
#define WORKER_H_INCLUDED

#include "ThreadPool.hpp"

class ThreadPool;

class Worker
{
  public:
    explicit Worker( const ThreadPool* tp ) : m_threadpool( tp ), m_isalive( true ),
                                        m_isactive( false ), m_worker( 0 ) { awaken(); }
    ~Worker() { if( m_worker != 0 ) delete m_worker; }

    void activate() { m_isactive = true; }
    void deactivate() { m_isactive = false; }
    //void join() {};

  private:
    bool m_isactive;
    bool m_isalive;
    const ThreadPool* m_threadpool;
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
                                    //implement sleep mechanism later!!!
                                  } } );
}

void Worker::execute_tasks()
{
  while( m_isactive )
  {
    //m_threadpool->pop_task()
    std::cout << "Activated..." << std::endl;
  }
}


#endif // WORKER_H_INCLUDED
