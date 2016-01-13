# J-PET tool project using J-PET framework
#
# Author: Adam Strzelecki <adam.strzelecki@uj.edu.pl>
#
# Description:
#   Builds project depending on J-PET framework.

cmake_minimum_required(VERSION 2.6)

project(ScopeReaderExample CXX) # using only C++

file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cpp)

include_directories(${Framework_INCLUDE_DIRS})
add_definitions(${Framework_DEFINITIONS})

generate_root_dictionaries(DICTIONARIES SOURCES ${SOURCES})
add_executable(ScopeReaderExample ${SOURCES} ${HEADERS} ${DICTIONARIES})
target_link_libraries(ScopeReaderExample JPetFramework)
