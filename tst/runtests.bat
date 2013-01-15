@echo off

del run_*.*

@echo ----------------------------------------------------------------
@echo --------------- CREATING SOURCEFILES FOR TESTING ---------------
@echo ----------------------------------------------------------------

python c:\mingw\cxxtest\bin\cxxtestgen --error-printer -o run_basic.cpp testBasic.hpp
python c:\mingw\cxxtest\bin\cxxtestgen --error-printer -o run_Tracer.cpp testTracer.hpp
python c:\mingw\cxxtest\bin\cxxtestgen --error-printer -o run_TaskExec.cpp testTaskExecution.hpp

mingw32-make clean

@echo ----------------------------------------------------------------
@echo ----------- COMPILING BASIC TEST CASES - TRACES OFF ------------
@echo ----------------------------------------------------------------

mingw32-make basic

@echo ----------------------------------------------------------------
@echo ------- COMPILING TEST EXECUTION TEST CASES - TRACES OFF -------
@echo ----------------------------------------------------------------

mingw32-make taskexec

del Tracer.o

@echo ----------------------------------------------------------------
@echo ------------- COMPILING TRACER TEST WITH TRACES ON -------------
@echo ----------------------------------------------------------------

mingw32-make tracer TRACE=ON

del Tracer.o
del run_Tracer.o

@echo ----------------------------------------------------------------
@echo ------------- COMPILING TRACER TEST WITH TRACES OFF ------------
@echo ----------------------------------------------------------------

mingw32-make tracer

@echo ----------------------------------------------------------------
@echo ------------- TESTING BASIC FUNCTIONS - TRACES OFF -------------
@echo ----------------------------------------------------------------

run_basic.exe

@echo ----------------------------------------------------------------
@echo -------------- TESTING TASK EXECUTION - TRACES OFF -------------
@echo ----------------------------------------------------------------

run_task_exec.exe

@echo ----------------------------------------------------------------
@echo ---------------- TESTING TRACER WITH TRACES ON -----------------
@echo ----------------------------------------------------------------

run_traceon.exe

@echo ----------------------------------------------------------------
@echo ---------------- TESTING TRACER WITH TRACES OFF ----------------
@echo ----------------------------------------------------------------

run_traceoff.exe


@echo ----------------------------------------------------------------
@echo --------------------------- CLEANUP ----------------------------
@echo ----------------------------------------------------------------

mingw32-make clean
del run_*.*
