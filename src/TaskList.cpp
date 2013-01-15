
#include "../include/TaskList.hpp"

TaskList::~TaskList()
{
  TRACE("Deleting tasks stuck in the TaskList...");
  for( auto it : m_tasks )
  {
    delete it;
<<<<<<< HEAD
=======
    std::cerr << "Task deleted\n";
>>>>>>> 3581e162b7764a14fbf5d7bcb4a7731b2a145a27
  }
}

Task* TaskList::pop_task()
{
  SCOPEDLOCK;
  Task* tmp_task = 0;
  if( !m_tasks.empty() )
  {
    tmp_task = m_tasks.back();
    m_tasks.pop_back();
  }
  return tmp_task;
}
