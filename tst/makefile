TRACE?=OFF

INCLUDE= -I'/../include/'

LIBDIR=  -L'C:/BOOST/boost_1_52_0/stage/lib/'

SRC= ../src/

LIBS=	-lboost_date_time-mgw46-mt-1_52	\
	-lboost_filesystem-mgw46-mt-1_52 \
	-lboost_system-mgw46-mt-1_52 \
	-lboost_thread-mgw46-mt-1_52

BASIC_ALL_OBJS := Worker.o ThreadPool.o TaskList.o
BASIC_ALL_SRCS := $(ALL_FILES:.o=.cpp)

CC=g++
CCO=g++ -c -DTRACE_OFF

ifeq ($(TRACE),ON)
CCOT=g++ -c
TRGT=runner_tron.exe
else
CCOT=g++ -c -DTRACE_OFF
TRGT=runner_troff.exe
endif

runner.exe: runner.o $(BASIC_ALL_OBJS) Tracer.o
	$(CC) runner.o $(BASIC_ALL_OBJS) Tracer.o -std=c++0x $(INCLUDE) $(LIBDIR) $(LIBS) -o $@

runner.o: runner.cpp
	$(CCO) runner.cpp -std=c++0x $(INCLUDE) -o $@

$(BASIC_ALL_OBJS): $(BASIC_ALL_SRCS)
	$(CCO) $(SRC)$(@:.o=.cpp) -std=c++0x $(INCLUDE) -o $@
  
#######################################################################################
basic: runner.exe

tracer: $(TRGT)
	@echo off

$(TRGT): runTracer.o Tracer.o
	$(CC) runTracer.o Tracer.o -std=c++0x $(INCLUDE) -o $@
  
runTracer.o: runTracer.cpp
	$(CCOT) runTracer.cpp -std=c++0x $(INCLUDE) -o $@

Tracer.o: $(SRC)Tracer.cpp
	$(CCOT) $(SRC)Tracer.cpp -std=c++0x $(INCLUDE) -o $@

clean:
	del *.o