#ifndef TASKLIST_HPP_INCLUDED
#define TASKLIST_HPP_INCLUDED

#include <functional>

#include <boost/thread/mutex.hpp>

#include <deque>

#include "Tracer.hpp"

#define SCOPEDLOCK boost::mutex::scoped_lock lock(  m_mutex );

class Task
{
  public:
    virtual void run() = 0;
};

class LambdaTask : public Task
{
  public:
    explicit LambdaTask( std::function<void()> funct ) : runner(funct) {};
    std::function<void()> runner;
    void run() { runner(); }
};

class TaskList
{
  public:
    virtual ~TaskList();
    Task* pop_task();
    void push_task( Task* task ) { m_tasks.push_front( task ); }
  private:
    mutable boost::mutex m_mutex;
    std::deque< Task* > m_tasks;
};


#endif // TASKLIST_HPP_INCLUDED
