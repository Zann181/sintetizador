# =============================================================================
# BAZZ_Sintetizador — Sistema de Construcción CMake
# =============================================================================
# Sintetizador de audio en C++20 con secuenciador de 6 canales × 16 pasos.
# Genera una biblioteca estática (bazz_synth) y un ejecutable de pruebas.
# =============================================================================

cmake_minimum_required(VERSION 3.20)

project(BAZZ_Sintetizador
    VERSION      0.1.0
    DESCRIPTION  "Motor de síntesis de audio en tiempo real — BAZZ"
    LANGUAGES    CXX
)

# ---------------------------------------------------------------------------
# Estándar de C++ y política global
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)   # Usar -std=c++20, no -std=gnu++20

# Tipo de compilación por defecto: Release (optimizaciones habilitadas)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Tipo de compilación (Debug / Release / RelWithDebInfo / MinSizeRel)" FORCE)
endif()

message(STATUS "[BAZZ] Tipo de compilación: ${CMAKE_BUILD_TYPE}")
message(STATUS "[BAZZ] Compilador: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

# ---------------------------------------------------------------------------
# Opciones configurables
# ---------------------------------------------------------------------------
option(BAZZ_ENABLE_AVX2   "Habilitar instrucciones AVX2 (requiere CPU compatible)"   OFF)
option(BAZZ_ENABLE_SSE42  "Habilitar instrucciones SSE 4.2 (x86_64 moderno)"         OFF)
option(BAZZ_BUILD_TESTS   "Compilar el ejecutable de pruebas"                         ON)

# ---------------------------------------------------------------------------
# Recopilar archivos fuente (.cpp) de cada módulo
# ---------------------------------------------------------------------------

# --- Núcleo (core) ---
set(BAZZ_CORE_SOURCES
    core/mydsp.cpp
    core/PresetManager.cpp
)

# --- Secuenciador ---
set(BAZZ_SEQUENCER_SOURCES
    sequencer/Clock.cpp
    sequencer/Sequencer.cpp
)

# --- Voces de instrumentos ---
set(BAZZ_VOICES_SOURCES
    voices/KickVoice.cpp
    voices/FunkTribuKickVoice.cpp
    voices/SnareVoice.cpp
    voices/HiHatVoice.cpp
    voices/BassVoice.cpp
    voices/PsycheVoice.cpp
    voices/SiringeVoice.cpp
)

# Lista completa de fuentes para la biblioteca
set(BAZZ_ALL_SOURCES
    ${BAZZ_CORE_SOURCES}
    ${BAZZ_SEQUENCER_SOURCES}
    ${BAZZ_VOICES_SOURCES}
)

# ---------------------------------------------------------------------------
# Objetivo principal: biblioteca estática bazz_synth
# ---------------------------------------------------------------------------
add_library(bazz_synth STATIC ${BAZZ_ALL_SOURCES})

# Directorios de inclusión públicos (se propagan a targets que enlacen con esta lib)
target_include_directories(bazz_synth PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/sequencer
    ${CMAKE_CURRENT_SOURCE_DIR}/voices
    ${CMAKE_CURRENT_SOURCE_DIR}/dsp_components
)

# ---------------------------------------------------------------------------
# Banderas del compilador según plataforma
# ---------------------------------------------------------------------------
if(MSVC)
    # --- Microsoft Visual C++ ---
    # /W4            : Nivel alto de advertencias
    # /permissive-   : Conformidad estricta con el estándar
    # /fp:fast       : Aritmética de punto flotante rápida (como -ffast-math)
    target_compile_options(bazz_synth PRIVATE
        /W4
        /permissive-
        /fp:fast
    )

    # Optimizaciones por tipo de compilación
    target_compile_options(bazz_synth PRIVATE
        $<$<CONFIG:Release>:/O2 /Oi /GL>       # Optimización completa + intrínsecas
        $<$<CONFIG:Debug>:/Od /Zi /RTC1>        # Sin optimización + depuración completa
    )

    # Enlace con optimización global en Release (LTCG)
    target_link_options(bazz_synth PRIVATE
        $<$<CONFIG:Release>:/LTCG>
    )

    # SIMD en MSVC
    if(BAZZ_ENABLE_AVX2)
        target_compile_options(bazz_synth PRIVATE /arch:AVX2)
        message(STATUS "[BAZZ] SIMD: AVX2 habilitado (MSVC)")
    elseif(BAZZ_ENABLE_SSE42)
        # MSVC habilita SSE2 por defecto en x64; SSE4.2 no tiene bandera dedicada
        # pero /arch:AVX lo incluye implícitamente
        target_compile_definitions(bazz_synth PRIVATE BAZZ_SSE42_ENABLED)
        message(STATUS "[BAZZ] SIMD: SSE4.2 señalizado (MSVC, implícito en x64)")
    endif()

else()
    # --- GCC / Clang ---
    # -Wall -Wextra  : Advertencias exhaustivas
    # -ffast-math    : Aritmética de punto flotante agresiva
    # -fno-rtti      : Deshabilitar RTTI (no lo necesitamos)
    target_compile_options(bazz_synth PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -ffast-math
        -fno-rtti
    )

    # Optimizaciones por tipo de compilación
    target_compile_options(bazz_synth PRIVATE
        $<$<CONFIG:Release>:-O3 -march=native>
        $<$<CONFIG:Debug>:-g -O0>
    )

    # SIMD explícito (complementa -march=native si se desea forzar)
    if(BAZZ_ENABLE_AVX2)
        target_compile_options(bazz_synth PRIVATE -mavx2 -mfma)
        target_compile_definitions(bazz_synth PRIVATE BAZZ_AVX2_ENABLED)
        message(STATUS "[BAZZ] SIMD: AVX2 + FMA habilitado (GCC/Clang)")
    elseif(BAZZ_ENABLE_SSE42)
        target_compile_options(bazz_synth PRIVATE -msse4.2)
        target_compile_definitions(bazz_synth PRIVATE BAZZ_SSE42_ENABLED)
        message(STATUS "[BAZZ] SIMD: SSE4.2 habilitado (GCC/Clang)")
    endif()
endif()

# ---------------------------------------------------------------------------
# Definiciones de preprocesador útiles
# ---------------------------------------------------------------------------
target_compile_definitions(bazz_synth PUBLIC
    BAZZ_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    BAZZ_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    BAZZ_VERSION_PATCH=${PROJECT_VERSION_PATCH}
)

# En modo Debug, habilitar aserciones internas del sintetizador
target_compile_definitions(bazz_synth PRIVATE
    $<$<CONFIG:Debug>:BAZZ_DEBUG=1>
)

# ---------------------------------------------------------------------------
# Dependencias del sistema (hilos POSIX en Linux/macOS)
# ---------------------------------------------------------------------------
find_package(Threads REQUIRED)
target_link_libraries(bazz_synth PUBLIC Threads::Threads)

# ---------------------------------------------------------------------------
# Ejecutable de pruebas
# ---------------------------------------------------------------------------
if(BAZZ_BUILD_TESTS)
    add_executable(bazz_test tests/main_test.cpp)
    target_link_libraries(bazz_test PRIVATE bazz_synth)

    # Copiar el ejecutable al directorio raíz del proyecto para facilitar
    # la ejecución manual durante el desarrollo
    set_target_properties(bazz_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    )

    message(STATUS "[BAZZ] Ejecutable de pruebas habilitado (bazz_test)")
endif()

# ---------------------------------------------------------------------------
# Resumen de configuración
# ---------------------------------------------------------------------------
message(STATUS "")
message(STATUS "╔══════════════════════════════════════════════════╗")
message(STATUS "║        BAZZ_Sintetizador — Configuración        ║")
message(STATUS "╠══════════════════════════════════════════════════╣")
message(STATUS "║  Versión      : ${PROJECT_VERSION}                          ║")
message(STATUS "║  Compilación  : ${CMAKE_BUILD_TYPE}                       ║")
message(STATUS "║  C++ estándar : ${CMAKE_CXX_STANDARD}                            ║")
message(STATUS "║  AVX2         : ${BAZZ_ENABLE_AVX2}                          ║")
message(STATUS "║  SSE4.2       : ${BAZZ_ENABLE_SSE42}                          ║")
message(STATUS "║  Pruebas      : ${BAZZ_BUILD_TESTS}                          ║")
message(STATUS "╚══════════════════════════════════════════════════╝")
message(STATUS "")
