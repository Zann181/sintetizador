#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "liblo::liblo" for configuration ""
set_property(TARGET liblo::liblo APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(liblo::liblo PROPERTIES
  IMPORTED_IMPLIB_NOCONFIG "${_IMPORT_PREFIX}/lib/liblo.dll.a"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/bin/liblo.dll"
  )

list(APPEND _cmake_import_check_targets liblo::liblo )
list(APPEND _cmake_import_check_files_for_liblo::liblo "${_IMPORT_PREFIX}/lib/liblo.dll.a" "${_IMPORT_PREFIX}/bin/liblo.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
