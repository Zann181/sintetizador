# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-src"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-build"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-subbuild/liblo-populate-prefix"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-subbuild/liblo-populate-prefix/tmp"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-subbuild/liblo-populate-prefix/src/liblo-populate-stamp"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-subbuild/liblo-populate-prefix/src"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-subbuild/liblo-populate-prefix/src/liblo-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-subbuild/liblo-populate-prefix/src/liblo-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/liblo-subbuild/liblo-populate-prefix/src/liblo-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
