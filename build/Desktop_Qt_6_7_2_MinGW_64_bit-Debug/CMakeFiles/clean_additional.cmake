# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Kolibri_test_2026_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Kolibri_test_2026_autogen.dir\\ParseCache.txt"
  "Kolibri_test_2026_autogen"
  )
endif()
