#ifndef TASKLIST_HPP_INCLUDED
#define TASKLIST_HPP_INCLUDED

#include <boost/thread/mutex.hpp>

#include <deque>

#define SCOPEDLOCK boost::mutex::scoped_lock lock( m_mutex )

class Task
{
  public:
    virtual void run() = 0;
};

class TaskList
{
  public:
    ///virtual ~TaskList() { clear memory }
    Task* pop_task();
    void push_task( Task* task ) { m_tasks.push_front( task ); }
  private:
    mutable boost::mutex m_mutex;
    std::deque< Task* > m_tasks;
};


#endif // TASKLIST_HPP_INCLUDED
