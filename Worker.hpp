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
                                              m_istaskcomplete( true ),
                                              m_worker( [this](){
                                                                  while( m_isalive )
                                                                  {
                                                                    execute_tasks();
                                                            //implement sleep mechanism later!!!
                                                                  } })
                                              {
                                              };
    ~Worker();

    void activate() { m_isactive = true; }
    void deactivate() { m_isactive = false; }
//    bool is_finished() { return m_istaskcomplete; }

  private:
    bool m_isactive;
    bool m_isalive;
    bool m_istaskcomplete;
    const ThreadPool* m_threadpool;
    void awaken();
    void execute_tasks();
    boost::thread m_worker;
};

Worker::~Worker()
{
  m_isactive = false;
  m_isalive = false;
  std::cout << "\nWaiting for Worker to finish";
  while( !m_istaskcomplete )
  {
    ///DELETE CORE ONCE IT WORKS PERFECTLY
    std::cout << ".";
    boost::this_thread::sleep(boost::posix_time::millisec(50));
  }
  m_worker.join();
  std::cout << "\nWorker destroyed\n";
}

void Worker::execute_tasks()
{
  while( m_isactive )
  {
    m_istaskcomplete = false;
    ///m_threadpool->pop_task()
//    std::cout << "Within thread and Activated..." << std::endl;
    std::cout << "a";
    boost::this_thread::sleep(boost::posix_time::millisec(2000));
    m_istaskcomplete = true;
  }
  m_istaskcomplete = true;
}


#endif // WORKER_H_INCLUDED
