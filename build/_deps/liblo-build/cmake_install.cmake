# Install script for directory: C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/FaustSynthServer")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/msys64/ucrt64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/lo" TYPE FILE FILES
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake/../lo/lo_cpp.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake/../lo/lo_errors.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake/../lo/lo_lowlevel.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake/../lo/lo_macros.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake/../lo/lo_osc_types.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake/../lo/lo_serverthread.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake/../lo/lo_throw.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake/../lo/lo_types.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-build/lo/lo_endian.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-build/lo/lo.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-build/liblo.dll.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-build/liblo.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/liblo.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/liblo.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/msys64/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/liblo.dll")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/liblo/libloTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/liblo/libloTargets.cmake"
         "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-build/CMakeFiles/Export/24232cc174539220bc0fcb2f1476e63b/libloTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/liblo/libloTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/liblo/libloTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/liblo" TYPE FILE FILES "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-build/CMakeFiles/Export/24232cc174539220bc0fcb2f1476e63b/libloTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/liblo" TYPE FILE FILES "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-build/CMakeFiles/Export/24232cc174539220bc0fcb2f1476e63b/libloTargets-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/liblo" TYPE FILE FILES
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-build/libloConfig.cmake"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-build/libloConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-build/liblo.dll.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-build/liblo.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/liblo.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/liblo.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/msys64/ucrt64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/liblo.dll")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/lo" TYPE FILE FILES
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake/../lo/lo_cpp.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake/../lo/lo_errors.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake/../lo/lo_lowlevel.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake/../lo/lo_macros.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake/../lo/lo_osc_types.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake/../lo/lo_serverthread.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake/../lo/lo_throw.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src/cmake/../lo/lo_types.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-build/lo/lo_endian.h"
    "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-build/lo/lo.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/liblo" TYPE FILE FILES "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-build/libloConfig.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-build/liblo.pc")
endif()

