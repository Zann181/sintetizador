@echo off
echo ========================================================
echo CONFIGURANDO Y COMPILANDO CON CMAKE Y MSYS2
echo ========================================================
set PATH=C:\msys64\ucrt64\bin;C:\msys64\usr\bin;%PATH%
if not exist build mkdir build
cd build
cmake -G "MSYS Makefiles" -DCMAKE_MAKE_PROGRAM=C:/msys64/usr/bin/make.exe -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/c++.exe ..
if %ERRORLEVEL% neq 0 (
    echo Error en la configuracion de CMake
    exit /b %ERRORLEVEL%
)
C:\msys64\usr\bin\make.exe FaustSynthServer -j4
if %ERRORLEVEL% neq 0 (
    echo Error en la compilacion
    exit /b %ERRORLEVEL%
)
copy FaustSynthServer.exe ..\bazz.exe
echo Compilacion exitosa.
