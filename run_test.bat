@echo off
C:\msys64\ucrt64\bin\c++.exe -I"core" -I"state" -I"audio" -I"osc" -std=gnu++17 test_paths.cpp untitled.cpp -o test_paths.exe > compile_log.txt 2>&1
echo COMPILER EXIT CODE: %ERRORLEVEL%
if %ERRORLEVEL% equ 0 (
    test_paths.exe > output.txt
)
