cmake_minimum_required(VERSION 3.14)
project(FaustSynthServer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Opciones de optimización para Raspberry Pi y Producción
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Asumiendo Raspberry Pi 4 (AArch64) - Ajustar según versión específica
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math -mcpu=cortex-a72 -mtune=cortex-a72 -mfpu=neon-fp-armv8 -ftree-vectorize -funroll-loops")
elseif(MSVC)
    # Windows MSVC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /fp:fast")
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

# FetchContent para traer uWebSockets (WebSocket server)
FetchContent_Declare(
    uWebSockets
    GIT_REPOSITORY https://github.com/uNetworking/uWebSockets.git
    GIT_TAG        v20.44.0
)


# Configurar liblo para que no construya herramientas, tests ni ejemplos (evita fallos de enlace en Windows)
set(WITH_TOOLS OFF CACHE BOOL "Enable building tools." FORCE)
set(WITH_TESTS OFF CACHE BOOL "Enable building tests." FORCE)
set(WITH_EXAMPLES OFF CACHE BOOL "Enable building examples." FORCE)
set(WITH_CPP_TESTS OFF CACHE BOOL "Enable building C++ wrapper tests." FORCE)

FetchContent_MakeAvailable(RtAudio liblo uWebSockets)

# Añadir los fuentes del proyecto
set(SOURCES
    app/main.cpp
    audio/RtAudioBackend.cpp
    osc/OscServer.cpp
    untitled.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Configurar librerías según el sistema
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE __WINDOWS_WASAPI__)
    target_link_libraries(${PROJECT_NAME} PRIVATE rtaudio liblo wsock32 ws2_32 uWebSockets)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_compile_definitions(${PROJECT_NAME} PRIVATE __LINUX_ALSA__)
    target_link_libraries(${PROJECT_NAME} PRIVATE rtaudio liblo asound pthread uWebSockets)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/state
    ${CMAKE_CURRENT_SOURCE_DIR}/audio
    ${CMAKE_CURRENT_SOURCE_DIR}/osc
)
