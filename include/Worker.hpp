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
                                        m_identifier( 0 ),
                                        m_identifier_str( "0" ),
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

    void set_id( unsigned id );
    unsigned get_id() const { return m_identifier; }
    std::string get_id_str() const { return m_identifier_str; }

    bool get_is_busy() { if( m_workerstask ) return true; else return false; }

  private:
    bool m_isactive;
    bool m_isalive;
    ThreadPool& m_threadpool;
    Task* m_workerstask;
    void execute_tasks();
    boost::thread m_worker;
    unsigned m_identifier;
    std::string m_identifier_str;
};


#endif // WORKER_H_INCLUDED
