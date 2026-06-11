# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/abletonlink-src"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/abletonlink-build"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/abletonlink-subbuild/abletonlink-populate-prefix"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/abletonlink-subbuild/abletonlink-populate-prefix/tmp"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/abletonlink-subbuild/abletonlink-populate-prefix/src/abletonlink-populate-stamp"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/abletonlink-subbuild/abletonlink-populate-prefix/src"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/abletonlink-subbuild/abletonlink-populate-prefix/src/abletonlink-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/abletonlink-subbuild/abletonlink-populate-prefix/src/abletonlink-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/abletonlink-subbuild/abletonlink-populate-prefix/src/abletonlink-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
