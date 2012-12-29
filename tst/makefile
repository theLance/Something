INCLUDE= -I'/../include/'

LIBDIR=  -L'C:/BOOST/boost_1_52_0/stage/lib/'

SRC= ../src/

LIBS=	-lboost_date_time-mgw46-mt-1_52	\
	-lboost_filesystem-mgw46-mt-1_52 \
	-lboost_system-mgw46-mt-1_52 \
	-lboost_thread-mgw46-mt-1_52

ALL_FILES= runner.o Worker.o ThreadPool.o TaskList.o Tracer.o


runner.exe: $(ALL_FILES)
	g++ $(ALL_FILES) -std=c++0x $(INCLUDE) $(LIBDIR) $(LIBS) -o $@

runner.o: runner.cpp
	g++ -c runner.cpp -std=c++0x $(INCLUDE) -o $@

Worker.o: $(SRC)Worker.cpp
	g++ -c $(SRC)Worker.cpp -std=c++0x $(INCLUDE) -o $@
	
ThreadPool.o: $(SRC)ThreadPool.cpp
	g++ -c $(SRC)ThreadPool.cpp -std=c++0x $(INCLUDE) -o $@
	
TaskList.o: $(SRC)TaskList.cpp
	g++ -c $(SRC)TaskList.cpp -std=c++0x $(INCLUDE) -o $@
	
Tracer.o: $(SRC)Tracer.cpp
	g++ -c $(SRC)Tracer.cpp -std=c++0x $(INCLUDE) -o $@

clean:
	del *.o