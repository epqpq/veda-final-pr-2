# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Test_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Test_autogen.dir\\ParseCache.txt"
  "Test_autogen"
  )
endif()
