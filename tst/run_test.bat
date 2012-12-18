del runner.*

python c:\mingw\cxxtest\bin\cxxtestgen --error-printer -o runner.cpp test.hpp

g++  runner.cpp -std=c++0x -Lc:\BOOST\boost_1_52_0\stage\lib\^
	^
	-lboost_date_time-mgw46-mt-1_52 ^
	-lboost_filesystem-mgw46-mt-1_52 ^
	-lboost_system-mgw46-mt-1_52 ^
	-lboost_thread-mgw46-mt-1_52 ^
	^
	-o runner

runner.exe