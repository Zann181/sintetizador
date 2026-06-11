@echo off
set PATH=C:\msys64\ucrt64\bin;C:\msys64\usr\bin;%PATH%
echo Compiling... > scratch/compile_log.txt
c++.exe -std=c++20 -o scratch/test_clock.exe scratch/test_clock.cpp BAZZ_Sintetizador/sequencer/Clock.cpp > scratch/compile_log.txt 2>&1
if %ERRORLEVEL% neq 0 (
    echo Compilation failed. >> scratch/compile_log.txt
    exit /b %ERRORLEVEL%
)
echo Compilation succeeded. >> scratch/compile_log.txt
scratch\test_clock.exe > scratch/test_output.txt 2>&1
echo Execution finished. >> scratch/compile_log.txt
