#ifndef TRACER_HPP_INCLUDED
#define TRACER_HPP_INCLUDED

#ifdef TRACE_OFF
  #define TRACE(msg) ;
#else
  ///later, this should log to a file
  #define TRACE(msg) \
          std::cout << msg << std::endl;
#endif


#endif // TRACER_HPP_INCLUDED
