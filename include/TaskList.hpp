#ifndef TASKLIST_HPP_INCLUDED
#define TASKLIST_HPP_INCLUDED

#include <boost/thread/mutex.hpp>

#include <vector>

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
    ///void push_task( Task& task );
  private:
    ///Mutex m_mutex
    std::vector< Task* > m_tasks;
};

Task* TaskList::pop_task()
{
  SCOPEDLOCK;
  ///extract the Task*
  ///return the Task*
  Task* tmp;
  return tmp;
}

#endif // TASKLIST_HPP_INCLUDED
