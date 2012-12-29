
#include "../include/TaskList.hpp"

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
