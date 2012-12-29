
#include "../include/ThreadPool.hpp"
#include "../include/Worker.hpp"

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
    m_workerstask = NULL;
    m_workerstask = m_threadpool->pop_task();
    if( m_workerstask )
    {
      TRACE("Worker received task... Running...");
      m_workerstask->run();
    }
    boost::this_thread::sleep(boost::posix_time::millisec(500));
    ///implement sleep mechanism later!!!
  }
}
