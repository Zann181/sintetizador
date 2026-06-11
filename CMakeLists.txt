cmake_minimum_required(VERSION 3.14)
project(FaustSynthServer C CXX)

set(CMAKE_CXX_STANDARD 20)
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

# FetchContent y dependencias locales/remotas
include(FetchContent)

# 1. RtAudio
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/deps/rtaudio")
    FetchContent_Declare(RtAudio SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/rtaudio")
else()
    FetchContent_Declare(
        RtAudio
        GIT_REPOSITORY https://github.com/thestk/rtaudio.git
        GIT_TAG        master
    )
endif()

# 2. liblo (OSC)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/deps/liblo")
    FetchContent_Declare(liblo SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/liblo" SOURCE_SUBDIR cmake)
else()
    FetchContent_Declare(
        liblo
        GIT_REPOSITORY https://github.com/radarsat1/liblo.git
        GIT_TAG        master
        SOURCE_SUBDIR  cmake
    )
endif()

# 3. nlohmann_json
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/deps/nlohmann_json")
    FetchContent_Declare(nlohmann_json SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/nlohmann_json")
else()
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG        v3.11.3
    )
endif()

# 4. uWebSockets
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/deps/uWebSockets")
    FetchContent_Declare(uWebSockets SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/uWebSockets")
else()
    FetchContent_Declare(
        uWebSockets
        GIT_REPOSITORY https://github.com/uNetworking/uWebSockets.git
        GIT_TAG        v20.44.0
    )
endif()

# 5. libuv
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/deps/libuv")
    FetchContent_Declare(libuv SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/libuv")
else()
    FetchContent_Declare(
        libuv
        GIT_REPOSITORY https://github.com/libuv/libuv.git
        GIT_TAG        v1.44.2
    )
endif()

# 6. Ableton Link
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/deps/link")
    FetchContent_Declare(AbletonLink SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/link")
else()
    FetchContent_Declare(
        AbletonLink
        GIT_REPOSITORY https://github.com/Ableton/link.git
        GIT_TAG        master
        GIT_SUBMODULES "modules/asio-standalone"
    )
endif()

# Configurar liblo para que no construya herramientas, tests ni ejemplos (evita fallos de enlace en Windows)
set(WITH_TOOLS OFF CACHE BOOL "Enable building tools." FORCE)
set(WITH_TESTS OFF CACHE BOOL "Enable building tests." FORCE)
set(WITH_EXAMPLES OFF CACHE BOOL "Enable building examples." FORCE)
set(WITH_CPP_TESTS OFF CACHE BOOL "Enable building C++ wrapper tests." FORCE)

# 7. GLFW
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw")
    FetchContent_Declare(glfw SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw")
else()
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.3.8
    )
endif()
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

# 8. Dear ImGui
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui")
    FetchContent_Declare(imgui SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/imgui")
else()
    FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG        v1.89.9
    )
endif()

FetchContent_MakeAvailable(RtAudio liblo uWebSockets nlohmann_json libuv glfw)

FetchContent_GetProperties(AbletonLink)
if(NOT abletonlink_POPULATED)
    FetchContent_Populate(AbletonLink)
endif()

FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
endif()

# Compilar uSockets junto con el proyecto (solo el eventing de libuv para Windows)
file(GLOB USOCKETS_SOURCES
    "${uwebsockets_SOURCE_DIR}/uSockets/src/*.c"
    "${uwebsockets_SOURCE_DIR}/uSockets/src/crypto/*.c"
)
list(APPEND USOCKETS_SOURCES "${uwebsockets_SOURCE_DIR}/uSockets/src/eventing/libuv.c")

# Añadir los fuentes del proyecto modular
set(BAZZ_MODULAR_SOURCES
    BAZZ_Sintetizador/core/mydsp.cpp
    BAZZ_Sintetizador/core/PresetManager.cpp
    BAZZ_Sintetizador/sequencer/Clock.cpp
    BAZZ_Sintetizador/sequencer/Sequencer.cpp
    BAZZ_Sintetizador/voices/KickVoice.cpp
    BAZZ_Sintetizador/voices/FunkTribuKickVoice.cpp
    BAZZ_Sintetizador/voices/SnareVoice.cpp
    BAZZ_Sintetizador/voices/HiHatVoice.cpp
    BAZZ_Sintetizador/voices/BassVoice.cpp
    BAZZ_Sintetizador/voices/PsycheVoice.cpp
    BAZZ_Sintetizador/voices/SiringeVoice.cpp
)

set(SOURCES
    app/main.cpp
    audio/RtAudioBackend.cpp
    osc/OscServer.cpp
    ${BAZZ_MODULAR_SOURCES}
    ${USOCKETS_SOURCES}
)

if(WIN32)
    list(APPEND SOURCES resource.rc)
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

# Configurar librerías según el sistema
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE __WINDOWS_WASAPI__ UWS_NO_ZLIB LIBUS_USE_LIBUV LIBUS_NO_SSL)
    target_link_libraries(${PROJECT_NAME} PRIVATE rtaudio liblo wsock32 ws2_32 nlohmann_json::nlohmann_json uv_a)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_compile_definitions(${PROJECT_NAME} PRIVATE __LINUX_ALSA__ UWS_NO_ZLIB LIBUS_USE_LIBUV LIBUS_NO_SSL)
    target_link_libraries(${PROJECT_NAME} PRIVATE rtaudio liblo asound pthread nlohmann_json::nlohmann_json uv_a)
    
    # Agregar el puente de sincronización GPIO en C++ para Linux/Raspberry Pi
    add_executable(pi_gpio_sync app/pi_gpio_sync.cpp)
    target_link_libraries(pi_gpio_sync PRIVATE liblo gpiod)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/state
    ${CMAKE_CURRENT_SOURCE_DIR}/audio
    ${CMAKE_CURRENT_SOURCE_DIR}/osc
    ${CMAKE_CURRENT_SOURCE_DIR}/BAZZ_Sintetizador/core
    ${CMAKE_CURRENT_SOURCE_DIR}/BAZZ_Sintetizador/sequencer
    ${CMAKE_CURRENT_SOURCE_DIR}/BAZZ_Sintetizador/voices
    ${CMAKE_CURRENT_SOURCE_DIR}/BAZZ_Sintetizador/dsp_components
    ${uwebsockets_SOURCE_DIR}/src
    ${uwebsockets_SOURCE_DIR}/uSockets/src
)

set(IMGUI_SOURCES
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

# C++ Ableton Link Sync Bridge
add_executable(cpp_bridge modulo_midi_sync/cpp_bridge/main.cpp ${IMGUI_SOURCES} ${USOCKETS_SOURCES})

if(WIN32)
    target_compile_definitions(cpp_bridge PRIVATE LINK_PLATFORM_WINDOWS=1 UWS_NO_ZLIB LIBUS_USE_LIBUV LIBUS_NO_SSL)
    target_link_libraries(cpp_bridge PRIVATE liblo wsock32 ws2_32 iphlpapi winmm glfw opengl32 uv_a)
else()
    target_compile_definitions(cpp_bridge PRIVATE LINK_PLATFORM_LINUX=1 UWS_NO_ZLIB LIBUS_USE_LIBUV LIBUS_NO_SSL)
    target_link_libraries(cpp_bridge PRIVATE liblo pthread glfw GL uv_a)
endif()

target_include_directories(cpp_bridge PRIVATE
    ${abletonlink_SOURCE_DIR}/include
    ${abletonlink_SOURCE_DIR}/modules/asio-standalone/asio/include
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${uwebsockets_SOURCE_DIR}/src
    ${uwebsockets_SOURCE_DIR}/uSockets/src
)

# standalone DSP testing executable
add_executable(test_dsp scratch/test_dsp.cpp
    BAZZ_Sintetizador/core/mydsp.cpp
    BAZZ_Sintetizador/sequencer/Clock.cpp
    BAZZ_Sintetizador/sequencer/Sequencer.cpp
    BAZZ_Sintetizador/voices/BassVoice.cpp
    BAZZ_Sintetizador/voices/HiHatVoice.cpp
    BAZZ_Sintetizador/voices/KickVoice.cpp
    BAZZ_Sintetizador/voices/FunkTribuKickVoice.cpp
    BAZZ_Sintetizador/voices/PsycheVoice.cpp
    BAZZ_Sintetizador/voices/SiringeVoice.cpp
    BAZZ_Sintetizador/voices/SnareVoice.cpp
)
target_include_directories(test_dsp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/state
    ${CMAKE_CURRENT_SOURCE_DIR}/audio
    ${CMAKE_CURRENT_SOURCE_DIR}/osc
    ${CMAKE_CURRENT_SOURCE_DIR}/BAZZ_Sintetizador/core
    ${CMAKE_CURRENT_SOURCE_DIR}/BAZZ_Sintetizador/sequencer
    ${CMAKE_CURRENT_SOURCE_DIR}/BAZZ_Sintetizador/voices
    ${uwebsockets_SOURCE_DIR}/src
    ${uwebsockets_SOURCE_DIR}/uSockets/src
)
