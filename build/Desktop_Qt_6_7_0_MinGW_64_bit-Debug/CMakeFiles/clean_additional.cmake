# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appRDtask_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appRDtask_autogen.dir\\ParseCache.txt"
  "appRDtask_autogen"
  )
endif()
