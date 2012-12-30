@echo off
REM --------------------------------------------------------------------------
REM    Usage: run_test.bat OR run_test.bat traceon OR run_test.bat traceoff
REM --------------------------------------------------------------------------

del runner.*

python c:\mingw\cxxtest\bin\cxxtestgen --error-printer -o runner.cpp test.hpp

if "%1" == "traceoff" goto :traceoff_comp
REM ---- if nothing is specified, will compile both ----

REM compile with tracing ON
@echo ----------------------------------------------------------------
@echo ------------------- COMPILING WITH TRACES ON -------------------
@echo ----------------------------------------------------------------

mingw32-make clean

mingw32-make TRACE=ON

if "%1" == "traceon" goto :clean
REM compile with tracing OFF
:traceoff_comp
@echo ----------------------------------------------------------------
@echo ------------------- COMPILING WITH TRACES OFF ------------------
@echo ----------------------------------------------------------------

mingw32-make clean

mingw32-make

:clean
@echo ----------------------------------------------------------------
@echo --------------------------- CLEANUP ----------------------------
@echo ----------------------------------------------------------------

mingw32-make clean

if "%1" == "traceoff" goto :traceoff_run
REM ---- if nothing is specified, will run both ----

@echo ----------------------------------------------------------------
@echo -------------------- TESTING WITH TRACES ON --------------------
@echo ----------------------------------------------------------------

runner_t.exe
if "%1" == "traceon" goto :eof

:traceoff_run
@echo ----------------------------------------------------------------
@echo -------------------- TESTING WITH TRACES OFF -------------------
@echo ----------------------------------------------------------------

runner.exe