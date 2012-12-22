#ifndef WORKER_H_INCLUDED
#define WORKER_H_INCLUDED

#include "ThreadPool.hpp"

class ThreadPool;

class Worker
{
  public:
    explicit Worker( const ThreadPool* tp ) : m_threadpool( tp ),
                                              m_isactive( false ),
                                              m_isalive( true ),
                                              m_worker( [this]()
                                                       {
                                                         TRACE("Worker created");
                                                         while( m_isalive )
                                                         {
                                                           execute_tasks();
                                                      ///implement sleep mechanism later!!!
                                                         }
                                                         TRACE("Worker died");
                                                       })
                                              {
                                              };
    ~Worker();

    void activate() { m_isactive = true; }
    void deactivate() { m_isactive = false; }

  private:
    bool m_isactive;
    bool m_isalive;
    const ThreadPool* m_threadpool;
    void execute_tasks();
    boost::thread m_worker;
};

Worker::~Worker()
{
  TRACE("Worker destruction commencing...");
  m_isactive = false;
  m_isalive = false;
  TRACE("Waiting for worker to join...");
  m_worker.join();
  TRACE("Worker destroyed");
}

void Worker::execute_tasks()
{
  while( m_isactive )
  {
    //trace if pop successful
    ///m_threadpool->pop_task()
    std::cout << "a";
    boost::this_thread::sleep(boost::posix_time::millisec(500));
    ///implement sleep mechanism later!!!
  }
}


#endif // WORKER_H_INCLUDED
