echo Compilando BAZZ C++ Sync Bridge...
echo.
set PATH=%PATH%;C:\msys64\ucrt64\bin
C:\msys64\ucrt64\bin\c++.exe -DLIBUS_NO_SSL -DLIBUS_USE_LIBUV -DUWS_NO_ZLIB -D__WINDOWS_WASAPI__ -I"core" -I"state" -I"audio" -I"osc" -I"deps/uWebSockets/src" -I"deps/uWebSockets/uSockets/src" -I"deps/rtaudio" -I"build/_deps/liblo-build" -I"deps/liblo" -I"deps/nlohmann_json/include" -I"deps/libuv/include" -O3 -ffast-math -std=gnu++17 app/main.cpp osc/OscServer.cpp untitled.cpp audio/RtAudioBackend.cpp -L"build/_deps/liblo-build" -L"build/_deps/libuv-build" -L"build/deps/uWebSockets/uSockets" -luSockets -luv -llo -lole32 -lws2_32 -lwinmm -ldsound -lksuser -lrtaudio -o bazz.exe 
echo.
