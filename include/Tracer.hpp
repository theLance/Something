#ifndef TRACER_HPP_INCLUDED
#define TRACER_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include "Singleton.hpp"

class Tracer
{
  public:
    Tracer();
    ~Tracer() { m_logfile.close(); Tracer::m_logisopen = false; }
    void trace( const std::string msg );
  private:
    std::ofstream m_logfile;
    static bool m_logisopen;
};

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
  //for testing, output everything
  std::cout << msg << std::endl;
  m_logfile << msg << std::endl;
}

class STracer : public Singleton<Tracer>
{};

#ifdef TRACE_OFF
  #define TRACE(msg) ;
#else
  #define TRACE(msg) \
          STracer::getinstance()->trace(msg);
#endif


#endif // TRACER_HPP_INCLUDED
