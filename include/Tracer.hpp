#ifndef TRACER_HPP_INCLUDED
#define TRACER_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include "Singleton.hpp"

class Tracer
{
  public:
    Tracer();
    virtual ~Tracer() { m_logfile.close(); Tracer::m_logisopen = false; }
    void trace( const std::string msg );
  private:
    std::ofstream m_logfile;
    static bool m_logisopen;
};


class STracer : public Singleton<Tracer>
{};

#ifdef TRACE_OFF
  #define TRACE(msg) ;
#else
  #define TRACE(msg) \
          STracer::getinstance()->trace(msg);
#endif //TRACE_OFF


#endif // TRACER_HPP_INCLUDED
