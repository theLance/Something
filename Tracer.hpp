#ifndef TRACER_HPP_INCLUDED
#define TRACER_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include "include/Singleton.hpp"

class Tracer
{
  public:
//  Tracer() { m_logfile = new std::ofstream(); m_logfile->open( "log.txt" ); m_logfile << "Logfile created\n" }
  Tracer() { m_logfile.open( "log.txt", std::ios::out | std::ios::trunc ); m_logfile << "Logfile created\n"; }
  ~Tracer() { m_logfile.close(); }
    void trace( const std::string msg );
  private:
    std::ofstream m_logfile;
};

void Tracer::trace( const std::string msg )
{
  std::cout << msg << std::endl;
  m_logfile << msg << std::endl;
}

class STracer : public Singleton<Tracer>
{};

#ifdef TRACE_OFF
  #define TRACE(msg) ;
#else
  ///later, this should log to a file
  #define TRACE(msg) \
          STracer::getinstance()->trace(msg);
#endif


#endif // TRACER_HPP_INCLUDED
