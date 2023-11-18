# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Expresso_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Expresso_autogen.dir/ParseCache.txt"
  "Expresso_autogen"
  )
endif()
