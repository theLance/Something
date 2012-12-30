TRACE?=OFF

INCLUDE= -I'/../include/'

LIBDIR=  -L'C:/BOOST/boost_1_52_0/stage/lib/'

SRC= ../src/

LIBS=	-lboost_date_time-mgw46-mt-1_52	\
	-lboost_filesystem-mgw46-mt-1_52 \
	-lboost_system-mgw46-mt-1_52 \
	-lboost_thread-mgw46-mt-1_52

ALL_OBJS := Worker.o ThreadPool.o TaskList.o Tracer.o
ALL_SRCS := $(ALL_FILES:.o=.cpp)

CC=g++

ifeq ($(TRACE),ON)
CCO=g++ -c
TRGT=runner_t.exe
else
CCO=g++ -c -DTRACE_OFF
TRGT=runner.exe
endif

$(TRGT): runner.o $(ALL_OBJS)
	$(CC) runner.o $(ALL_OBJS) -std=c++0x $(INCLUDE) $(LIBDIR) $(LIBS) -o $@

runner.o: runner.cpp
	$(CCO) runner.cpp -std=c++0x $(INCLUDE) -o $@

$(ALL_OBJS): $(ALL_SRCS)
	$(CCO) $(SRC)$(@:.o=.cpp) -std=c++0x $(INCLUDE) -o $@

clean:
	del *.o