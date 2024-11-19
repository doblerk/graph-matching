#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "hdf5::hdf5-static" for configuration "Release"
set_property(TARGET hdf5::hdf5-static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::hdf5-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libhdf5.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::hdf5-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::hdf5-static "${_IMPORT_PREFIX}/lib/libhdf5.a" )

# Import target "hdf5::hdf5-shared" for configuration "Release"
set_property(TARGET hdf5::hdf5-shared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::hdf5-shared PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libhdf5.so.310.5.0"
  IMPORTED_SONAME_RELEASE "libhdf5.so.310"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::hdf5-shared )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::hdf5-shared "${_IMPORT_PREFIX}/lib/libhdf5.so.310.5.0" )

# Import target "hdf5::mirror_server" for configuration "Release"
set_property(TARGET hdf5::mirror_server APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::mirror_server PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/mirror_server"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::mirror_server )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::mirror_server "${_IMPORT_PREFIX}/bin/mirror_server" )

# Import target "hdf5::mirror_server_stop" for configuration "Release"
set_property(TARGET hdf5::mirror_server_stop APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::mirror_server_stop PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/mirror_server_stop"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::mirror_server_stop )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::mirror_server_stop "${_IMPORT_PREFIX}/bin/mirror_server_stop" )

# Import target "hdf5::hdf5_tools-static" for configuration "Release"
set_property(TARGET hdf5::hdf5_tools-static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::hdf5_tools-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libhdf5_tools.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::hdf5_tools-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::hdf5_tools-static "${_IMPORT_PREFIX}/lib/libhdf5_tools.a" )

# Import target "hdf5::hdf5_tools-shared" for configuration "Release"
set_property(TARGET hdf5::hdf5_tools-shared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::hdf5_tools-shared PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libhdf5_tools.so.310.0.5"
  IMPORTED_SONAME_RELEASE "libhdf5_tools.so.310"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::hdf5_tools-shared )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::hdf5_tools-shared "${_IMPORT_PREFIX}/lib/libhdf5_tools.so.310.0.5" )

# Import target "hdf5::h5diff" for configuration "Release"
set_property(TARGET hdf5::h5diff APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5diff PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5diff"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5diff )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5diff "${_IMPORT_PREFIX}/bin/h5diff" )

# Import target "hdf5::h5ls" for configuration "Release"
set_property(TARGET hdf5::h5ls APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5ls PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5ls"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5ls )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5ls "${_IMPORT_PREFIX}/bin/h5ls" )

# Import target "hdf5::h5debug" for configuration "Release"
set_property(TARGET hdf5::h5debug APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5debug PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5debug"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5debug )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5debug "${_IMPORT_PREFIX}/bin/h5debug" )

# Import target "hdf5::h5repart" for configuration "Release"
set_property(TARGET hdf5::h5repart APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5repart PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5repart"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5repart )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5repart "${_IMPORT_PREFIX}/bin/h5repart" )

# Import target "hdf5::h5mkgrp" for configuration "Release"
set_property(TARGET hdf5::h5mkgrp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5mkgrp PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5mkgrp"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5mkgrp )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5mkgrp "${_IMPORT_PREFIX}/bin/h5mkgrp" )

# Import target "hdf5::h5clear" for configuration "Release"
set_property(TARGET hdf5::h5clear APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5clear PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5clear"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5clear )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5clear "${_IMPORT_PREFIX}/bin/h5clear" )

# Import target "hdf5::h5delete" for configuration "Release"
set_property(TARGET hdf5::h5delete APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5delete PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5delete"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5delete )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5delete "${_IMPORT_PREFIX}/bin/h5delete" )

# Import target "hdf5::h5import" for configuration "Release"
set_property(TARGET hdf5::h5import APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5import PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5import"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5import )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5import "${_IMPORT_PREFIX}/bin/h5import" )

# Import target "hdf5::h5repack" for configuration "Release"
set_property(TARGET hdf5::h5repack APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5repack PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5repack"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5repack )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5repack "${_IMPORT_PREFIX}/bin/h5repack" )

# Import target "hdf5::h5jam" for configuration "Release"
set_property(TARGET hdf5::h5jam APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5jam PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5jam"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5jam )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5jam "${_IMPORT_PREFIX}/bin/h5jam" )

# Import target "hdf5::h5unjam" for configuration "Release"
set_property(TARGET hdf5::h5unjam APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5unjam PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5unjam"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5unjam )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5unjam "${_IMPORT_PREFIX}/bin/h5unjam" )

# Import target "hdf5::h5copy" for configuration "Release"
set_property(TARGET hdf5::h5copy APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5copy PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5copy"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5copy )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5copy "${_IMPORT_PREFIX}/bin/h5copy" )

# Import target "hdf5::h5stat" for configuration "Release"
set_property(TARGET hdf5::h5stat APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5stat PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5stat"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5stat )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5stat "${_IMPORT_PREFIX}/bin/h5stat" )

# Import target "hdf5::h5dump" for configuration "Release"
set_property(TARGET hdf5::h5dump APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5dump PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5dump"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5dump )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5dump "${_IMPORT_PREFIX}/bin/h5dump" )

# Import target "hdf5::h5format_convert" for configuration "Release"
set_property(TARGET hdf5::h5format_convert APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5format_convert PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5format_convert"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5format_convert )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5format_convert "${_IMPORT_PREFIX}/bin/h5format_convert" )

# Import target "hdf5::h5perf_serial" for configuration "Release"
set_property(TARGET hdf5::h5perf_serial APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5perf_serial PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5perf_serial"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5perf_serial )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5perf_serial "${_IMPORT_PREFIX}/bin/h5perf_serial" )

# Import target "hdf5::hdf5_hl-static" for configuration "Release"
set_property(TARGET hdf5::hdf5_hl-static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::hdf5_hl-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libhdf5_hl.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::hdf5_hl-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::hdf5_hl-static "${_IMPORT_PREFIX}/lib/libhdf5_hl.a" )

# Import target "hdf5::hdf5_hl-shared" for configuration "Release"
set_property(TARGET hdf5::hdf5_hl-shared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::hdf5_hl-shared PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libhdf5_hl.so.310.0.5"
  IMPORTED_SONAME_RELEASE "libhdf5_hl.so.310"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::hdf5_hl-shared )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::hdf5_hl-shared "${_IMPORT_PREFIX}/lib/libhdf5_hl.so.310.0.5" )

# Import target "hdf5::h5watch" for configuration "Release"
set_property(TARGET hdf5::h5watch APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::h5watch PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/h5watch"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::h5watch )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::h5watch "${_IMPORT_PREFIX}/bin/h5watch" )

# Import target "hdf5::hdf5_cpp-static" for configuration "Release"
set_property(TARGET hdf5::hdf5_cpp-static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::hdf5_cpp-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libhdf5_cpp.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::hdf5_cpp-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::hdf5_cpp-static "${_IMPORT_PREFIX}/lib/libhdf5_cpp.a" )

# Import target "hdf5::hdf5_cpp-shared" for configuration "Release"
set_property(TARGET hdf5::hdf5_cpp-shared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::hdf5_cpp-shared PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libhdf5_cpp.so.310.0.5"
  IMPORTED_SONAME_RELEASE "libhdf5_cpp.so.310"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::hdf5_cpp-shared )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::hdf5_cpp-shared "${_IMPORT_PREFIX}/lib/libhdf5_cpp.so.310.0.5" )

# Import target "hdf5::hdf5_hl_cpp-static" for configuration "Release"
set_property(TARGET hdf5::hdf5_hl_cpp-static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::hdf5_hl_cpp-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libhdf5_hl_cpp.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::hdf5_hl_cpp-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::hdf5_hl_cpp-static "${_IMPORT_PREFIX}/lib/libhdf5_hl_cpp.a" )

# Import target "hdf5::hdf5_hl_cpp-shared" for configuration "Release"
set_property(TARGET hdf5::hdf5_hl_cpp-shared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(hdf5::hdf5_hl_cpp-shared PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libhdf5_hl_cpp.so.310.0.5"
  IMPORTED_SONAME_RELEASE "libhdf5_hl_cpp.so.310"
  )

list(APPEND _IMPORT_CHECK_TARGETS hdf5::hdf5_hl_cpp-shared )
list(APPEND _IMPORT_CHECK_FILES_FOR_hdf5::hdf5_hl_cpp-shared "${_IMPORT_PREFIX}/lib/libhdf5_hl_cpp.so.310.0.5" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
