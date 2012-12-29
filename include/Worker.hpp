#ifndef WORKER_H_INCLUDED
#define WORKER_H_INCLUDED

#define BOOST_THREAD_USE_LIB
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <memory>

#include "Tracer.hpp"
#include "TaskList.hpp"

class ThreadPool;

class Worker
{
  public:
    explicit Worker( ThreadPool& tp ) : m_threadpool( tp ),
                                        m_isactive( false ),
                                        m_isalive( true ),
                                        m_workerstask( NULL ),
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
    virtual ~Worker();

    void activate() { m_isactive = true; }
    void deactivate() { m_isactive = false; }

  private:
    bool m_isactive;
    bool m_isalive;
    ThreadPool& m_threadpool;
    Task* m_workerstask;
    void execute_tasks();
    boost::thread m_worker;
};


#endif // WORKER_H_INCLUDED
