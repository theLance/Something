
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
      try
      {
        m_workerstask->run();
        TRACE("Worker " + get_id_str() + ": task complete");
      }
      catch( const boost::thread_interrupted& )
      {
        TRACE("Interruption caused task to terminate in Worker " + get_id_str());
      }
      catch( ... )
      {
        TRACE("Exception caused task to terminate in Worker " + get_id_str());
      }
      m_workerstask = NULL;
    }
    else
    {
      boost::this_thread::yield();
      boost::this_thread::sleep(boost::posix_time::millisec(50));
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

