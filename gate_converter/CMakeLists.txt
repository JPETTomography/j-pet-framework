cmake_minimum_required(VERSION 2.6)

#MANDATORY: Before first cmake please insert here your path to ROOT installation directory
#set(ROOT_INSTALLATION_DIRECTORY "/home/alek/Programy/root-system-6")
#set(GLOBAL_ACTOR_DICTIONARIES "/home/mateusz/Libraries/Build/Gate/libGlobalActorEventPackageDict.so")

################################################################################
# Handling of thisroot.sh
################################################################################

#message(STATUS "Your ROOT installation directory is: ${ROOT_INSTALLATION_DIRECTORY}")

#if(EXISTS ${ROOT_INSTALLATION_DIRECTORY}/bin/thisroot.sh)
#  message(STATUS "Status of thisroot.sh file : EXIST")
#else()
# message(FATAL_ERROR "Status of thisroot.sh file :  DOES NOT EXIST - is your path to ROOT installation directory is correct? Please check a variable ROOT_INSTALLATION_DIRECTORY in this CMakeList.txt file.")
#endif()

#message(STATUS "Calling thisroot.sh")
#execute_process(COMMAND source ${ROOT_INSTALLATION_DIRECTORY}/bin/thisroot.sh)

################################################################################
# Project configuration
################################################################################

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

## For generate_root_dictionaries
#include(JPetFramework-Utilities)

set(projectName converter)
set(projectBinary ${projectName}.x)

project(${projectName} CXX) # using only C++

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

add_definitions(-std=c++11 -Wall -Wunused-parameter) # using C++11 standard

################################################################################
# Handling of ROOT
################################################################################

## Find CERN ROOT
# first try to find ROOT 6 or ROOT 5 compiled with CMake
# if present, such ROOT should be possible to find without explicit setting of any paths
find_package(ROOT 6 QUIET)

if(ROOT_FOUND)
  message(STATUS "XXX: ROOT (version ${ROOT_VERSION}) was found using ROOTConfig")
else()
  # try to locate ROOT using ROOTSYS and root-config in case ROOTSYS is not set
  # this might be necessary for ROOT 5 built with autotools rather than CMake
  set(root_prefix $ENV{ROOTSYS})
  if(root_prefix)
    list(APPEND CMAKE_MODULE_PATH ${root_prefix}/etc/cmake/)
  else()
    execute_process(COMMAND root-config --etcdir OUTPUT_VARIABLE ROOT_ETCDIR OUTPUT_STRIP_TRAILING_WHITESPACE)
    list(APPEND CMAKE_MODULE_PATH ${ROOT_ETCDIR}/cmake)
  endif()
  find_package(ROOT 5 QUIET)
  if(ROOT_FOUND)
    message(STATUS "ROOT (version ${ROOT_VERSION}) was found using FindROOT (legacy mode)")
  else()
    # as last resort, use the bundled FindROOT module
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/fallback)
    find_package(ROOT 5 REQUIRED)
    if(ROOT_FOUND)
      message(WARNING "No CMake modules from a ROOT installation were found. ROOT (version ${ROOT_VERSION}) was only found using fallback mode)")
    endif()
  endif()
endif()

if(ROOT_USE_FILE)
  include(${ROOT_USE_FILE})
endif()

################################################################################
# Sources and linking
################################################################################

# Adding ROOT dictionaries
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)  #to change the LD_LIBRARY_PATH and accept pcm
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

ROOT_GENERATE_DICTIONARY(GateHitDict GateHit.h LINKDEF GateHitLinkDef.h)
#---Create a shared library with geneated dictionary
add_library(EventPackage SHARED GateHitDict.cxx)
target_link_libraries(EventPackage ${ROOT_LIBRARIES})


file(GLOB SOURCES *.cpp)

file(GLOB HEADERS GateHit.h Writer.h Reader.h)

add_executable(${projectName} ${SOURCES} ${HEADERS} )
target_link_libraries(${projectName} ${ROOT_LIBRARIES} EventPackage)
