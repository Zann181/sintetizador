cmake_minimum_required(VERSION 3.14)
project(FaustSynthServer C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Opciones de optimización para Raspberry Pi y Producción
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Asumiendo Raspberry Pi 4 (AArch64) - Ajustar según versión específica
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math -mcpu=cortex-a72 -mtune=cortex-a72 -mfpu=neon-fp-armv8 -ftree-vectorize -funroll-loops")
elseif(MSVC)
    # Windows MSVC - Usar /O1 en lugar de /O2 para evitar que el compilador se cuelgue procesando el DSP de Faust
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O1 /fp:fast /bigobj")
else()
    # Assume GCC/Clang on other systems/environments (like MSYS2)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math")
endif()

# FetchContent para traer RtAudio
include(FetchContent)
FetchContent_Declare(
    RtAudio
    GIT_REPOSITORY https://github.com/thestk/rtaudio.git
    GIT_TAG        master
)
# FetchContent para traer liblo (OSC)
FetchContent_Declare(
    liblo
    GIT_REPOSITORY https://github.com/radarsat1/liblo.git
    GIT_TAG        master
    SOURCE_SUBDIR  cmake
)

# FetchContent para traer nlohmann_json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
)

# FetchContent para traer uWebSockets (WebSocket server)
FetchContent_Declare(
    uWebSockets
    GIT_REPOSITORY https://github.com/uNetworking/uWebSockets.git
    GIT_TAG        v20.44.0
)

# FetchContent para traer libuv (requerido por uWebSockets en Windows)
FetchContent_Declare(
    libuv
    GIT_REPOSITORY https://github.com/libuv/libuv.git
    GIT_TAG        v1.44.2
)

# Configurar liblo para que no construya herramientas, tests ni ejemplos (evita fallos de enlace en Windows)
set(WITH_TOOLS OFF CACHE BOOL "Enable building tools." FORCE)
set(WITH_TESTS OFF CACHE BOOL "Enable building tests." FORCE)
set(WITH_EXAMPLES OFF CACHE BOOL "Enable building examples." FORCE)
set(WITH_CPP_TESTS OFF CACHE BOOL "Enable building C++ wrapper tests." FORCE)

FetchContent_MakeAvailable(RtAudio liblo uWebSockets nlohmann_json libuv)

# Compilar uSockets junto con el proyecto (solo el eventing de libuv para Windows)
file(GLOB USOCKETS_SOURCES
    "${uwebsockets_SOURCE_DIR}/uSockets/src/*.c"
    "${uwebsockets_SOURCE_DIR}/uSockets/src/crypto/*.c"
)
list(APPEND USOCKETS_SOURCES "${uwebsockets_SOURCE_DIR}/uSockets/src/eventing/libuv.c")

# Añadir los fuentes del proyecto
set(SOURCES
    app/main.cpp
    audio/RtAudioBackend.cpp
    osc/OscServer.cpp
    untitled.cpp
    ${USOCKETS_SOURCES}
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Configurar librerías según el sistema
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE __WINDOWS_WASAPI__ UWS_NO_ZLIB LIBUS_USE_LIBUV LIBUS_NO_SSL)
    target_link_libraries(${PROJECT_NAME} PRIVATE rtaudio liblo wsock32 ws2_32 nlohmann_json::nlohmann_json uv_a)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_compile_definitions(${PROJECT_NAME} PRIVATE __LINUX_ALSA__ UWS_NO_ZLIB LIBUS_USE_LIBUV LIBUS_NO_SSL)
    target_link_libraries(${PROJECT_NAME} PRIVATE rtaudio liblo asound pthread nlohmann_json::nlohmann_json uv_a)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/state
    ${CMAKE_CURRENT_SOURCE_DIR}/audio
    ${CMAKE_CURRENT_SOURCE_DIR}/osc
    ${uwebsockets_SOURCE_DIR}/src
    ${uwebsockets_SOURCE_DIR}/uSockets/src
)
