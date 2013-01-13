TRACE?=OFF

INCLUDE= -I'/../include/'

LIBDIR=  -L'C:/BOOST/boost_1_52_0/stage/lib/'

SRC= ../src/

LIBS=	-lboost_date_time-mgw46-mt-1_52	\
	-lboost_filesystem-mgw46-mt-1_52 \
	-lboost_system-mgw46-mt-1_52 \
	-lboost_thread-mgw46-mt-1_52

BASIC_ALL_OBJS := Worker.o ThreadPool.o TaskList.o Tracer.o
BASIC_ALL_SRCS := $(ALL_FILES:.o=.cpp)

CC=g++
CCO=g++ -c -DTRACE_OFF

ifeq ($(TRACE),ON)
CCOT=g++ -c
TRGT=run_traceon.exe
else
CCOT=g++ -c -DTRACE_OFF
TRGT=run_traceoff.exe
endif

run_basic.exe: run_basic.o $(BASIC_ALL_OBJS)
	$(CC) run_basic.o $(BASIC_ALL_OBJS) -std=c++0x $(INCLUDE) $(LIBDIR) $(LIBS) -o $@

run_basic.o: run_basic.cpp
	$(CCOT) run_basic.cpp -std=c++0x $(INCLUDE) -o $@

$(BASIC_ALL_OBJS): $(BASIC_ALL_SRCS)
	$(CCOT) $(SRC)$(@:.o=.cpp) -std=c++0x $(INCLUDE) -o $@
  
#######################################################################################

run_task_exec.exe: run_task_exec.o $(BASIC_ALL_OBJS)
	$(CC) run_task_exec.o $(BASIC_ALL_OBJS) -std=c++0x $(INCLUDE) $(LIBDIR) $(LIBS) -o $@

run_task_exec.o: run_TaskExec.cpp
	$(CCO) run_TaskExec.cpp -std=c++0x $(INCLUDE) -o $@

#######################################################################################


$(TRGT): run_Tracer.o Tracer.o
	$(CC) run_Tracer.o Tracer.o -std=c++0x $(INCLUDE) -o $@
  
run_Tracer.o: run_Tracer.cpp
	$(CCOT) run_Tracer.cpp -std=c++0x $(INCLUDE) -o $@

#######################################################################################

basic: run_basic.exe
	@echo off
	
taskexec: run_task_exec.exe
	@echo off
	
tracer: $(TRGT)
	@echo off

clean:
	del *.o