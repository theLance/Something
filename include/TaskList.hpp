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
    Task* pop_task();
    void push_task( Task* task ) { m_tasks.push_front( task ); }
  private:
    mutable boost::mutex m_mutex;
    std::deque< Task* > m_tasks;
};

Task* TaskList::pop_task()
{
  SCOPEDLOCK;
  Task* tmp_task = 0;
  if( m_tasks.size() )
  {
    tmp_task = m_tasks.back();
    m_tasks.pop_back();
  }
  return tmp_task;
}


#endif // TASKLIST_HPP_INCLUDED
