
#include "../include/ThreadPool.hpp"
#include "../include/Worker.hpp"

Worker::~Worker()
{
  TRACE("Worker " + get_id_str() + " destruction commencing...");
  m_isactive = false;
  m_isalive = false;
  TRACE("Waiting for Worker " + get_id_str() + " to join...");
  m_worker.join();
  TRACE("Worker " + get_id_str() + " destroyed");
}

void Worker::execute_tasks()
{
  while( m_isactive )
  {
    m_workerstask = NULL;
    m_workerstask = m_threadpool.pop_task();
    if( m_workerstask )
    {
      TRACE("Worker " + get_id_str() + " received task... Running...");
      m_workerstask->run();
      m_workerstask = NULL;
    }
    else
    {
    boost::this_thread::sleep(boost::posix_time::millisec(100));
    ///implement sleep mechanism later!!!
    }
  }
}

void Worker::set_id( unsigned id )
{
  m_identifier = id;
  std::stringstream strstm;
  strstm << id;
  m_identifier_str = strstm.str();
}

