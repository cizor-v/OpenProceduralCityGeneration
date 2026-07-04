# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\OpenProceduralCityGeneration_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\OpenProceduralCityGeneration_autogen.dir\\ParseCache.txt"
  "OpenProceduralCityGeneration_autogen"
  )
endif()
