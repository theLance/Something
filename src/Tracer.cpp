
#include "../include/Tracer.hpp"

bool Tracer::m_logisopen = false;

Tracer::Tracer()
{
  if( Tracer::m_logisopen )
  {
    std::cerr << "Attempted to reopen log.txt!\n";
    ///maybe replace with more meaningful exception
    throw 1;
  }
  else
  {
    m_logfile.open( "log.txt", std::ios::out | std::ios::trunc );
    m_logfile << "Logfile created\n";
    Tracer::m_logisopen = true;
  }
}

void Tracer::trace( const std::string msg )
{
  //for testing, display everything
  std::cout << msg << std::endl;
  m_logfile << msg << std::endl;
}
