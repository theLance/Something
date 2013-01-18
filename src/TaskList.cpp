
#include "../include/TaskList.hpp"

TaskList::~TaskList()
{
  TRACE("Deleting tasks stuck in the TaskList...");
  for( auto it : m_tasks )
  {
    TRACE("  Deleting task");
    delete it;
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
    TRACE("Task popped from TaskList");
  }
  return tmp_task;
}
