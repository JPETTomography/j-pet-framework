# J-PET tools and examples
#
# Author: Adam Strzelecki <adam.strzelecki@uj.edu.pl>
#
# Description:
#   Builds J-PET tools and examples depending on Framework.

cmake_minimum_required(VERSION 2.6)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/framework-lib/cmake)

# add Framework submodule
add_subdirectory(framework)
include_directories(framework ${Framework_INCLUDE_DIRS})
add_definitions(${Framework_DEFINITIONS})

# enable rpath on OS X and point it to ROOT
if(APPLE)
  set(CMAKE_MACOSX_RPATH ON)
  set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${ROOT_LIBRARY_DIR}"
    )
endif()

add_subdirectory(AnalysisExample)
add_subdirectory(ScopeReaderExample)
