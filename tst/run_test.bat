@echo off
REM --------------------------------------------------------------------------
REM    Usage: run_test.bat OR run_test.bat traceon OR run_test.bat traceoff
REM --------------------------------------------------------------------------

del runner*.*

@echo ----------------------------------------------------------------
@echo --------------- CREATING SOURCEFILES FOR TESTING ---------------
@echo ----------------------------------------------------------------

python c:\mingw\cxxtest\bin\cxxtestgen --error-printer -o runner.cpp testBasic.hpp
python c:\mingw\cxxtest\bin\cxxtestgen --error-printer -o runTracer.cpp testTracer.hpp

mingw32-make clean

@echo ----------------------------------------------------------------
@echo ------------ COMPILING BASIC TEST CASES - TRACE OFF ------------
@echo ----------------------------------------------------------------

mingw32-make basic

del Tracer.o

@echo ----------------------------------------------------------------
@echo ------------- COMPILING TRACER TEST WITH TRACES ON -------------
@echo ----------------------------------------------------------------

mingw32-make tracer TRACE=ON

del Tracer.o

@echo ----------------------------------------------------------------
@echo ------------- COMPILING TRACER TEST WITH TRACES OFF ------------
@echo ----------------------------------------------------------------

mingw32-make tracer

@echo ----------------------------------------------------------------
@echo ------------- TESTING BASIC FUNCTIONS - TRACES OFF -------------
@echo ----------------------------------------------------------------

runner.exe

@echo ----------------------------------------------------------------
@echo ---------------- TESTING TRACER WITH TRACES ON -----------------
@echo ----------------------------------------------------------------

runner_tron.exe

@echo ----------------------------------------------------------------
@echo ---------------- TESTING TRACER WITH TRACES OFF ----------------
@echo ----------------------------------------------------------------

runner_troff.exe


@echo ----------------------------------------------------------------
@echo --------------------------- CLEANUP ----------------------------
@echo ----------------------------------------------------------------

mingw32-make clean
del runner*.*
del runTracer.cpp
