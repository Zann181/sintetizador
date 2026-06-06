# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/deps/uWebSockets"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/uwebsockets-build"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/uwebsockets-subbuild/uwebsockets-populate-prefix"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/uwebsockets-subbuild/uwebsockets-populate-prefix/tmp"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/uwebsockets-subbuild/uwebsockets-populate-prefix/src/uwebsockets-populate-stamp"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/uwebsockets-subbuild/uwebsockets-populate-prefix/src"
  "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/uwebsockets-subbuild/uwebsockets-populate-prefix/src/uwebsockets-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/uwebsockets-subbuild/uwebsockets-populate-prefix/src/uwebsockets-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Motaz/Music/Nueva carpeta/sintetizador/build/_deps/uwebsockets-subbuild/uwebsockets-populate-prefix/src/uwebsockets-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
