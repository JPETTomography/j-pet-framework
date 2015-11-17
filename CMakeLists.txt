# J-PET framework project main description file
#
# Author: Adam Strzelecki <adam.strzelecki@uj.edu.pl>
#
# Description:
#   Builds all J-PET framework modules using CMake build generator.

cmake_minimum_required(VERSION 2.6)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(JPetFramework-Utilities) # for generate_root_dictionaries

project(JPetFramework CXX) # using only C++

# use Release by default
# if(NOT CMAKE_BUILD_TYPE)
#  set(CMAKE_BUILD_TYPE Release CACHE STRING
#    "Choose the type Debug or Release" FORCE)
# endif()

# enable C++11 and warnings
if(NOT MSVC)
  add_definitions(-std=c++11 -Wall -Wunused-parameter)
endif()

# Dependencies
# ------------

# - ROOT
foreach(mode QUIET REQUIRED)
  find_package(ROOT 5 ${mode} COMPONENTS
    Hist
    Physics
    RIO
    Thread
    Tree
    )
  if(ROOT_USE_FILE)
    include(${ROOT_USE_FILE})
  endif()
  if(ROOT_FOUND)
    break()
  endif()
  # if we failed with CMake based find_package, use fallback
  # root-config version from cmake/fallback/
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/fallback)
endforeach()
include_directories(${ROOT_INCLUDE_DIRS})
add_definitions(${ROOT_DEFINITIONS})
message(STATUS "ROOT version: ${ROOT_VERSION}")
if(ROOT_FOUND AND NOT ROOT_VERSION VERSION_LESS "6.0")
  message(FATAL_ERROR "ROOT 6.0 is not compatible")
endif()

# - libpqxx
find_package(PQXX REQUIRED)
include_directories(${PQXX_INCLUDE_DIRS})
add_definitions(${PQXX_DEFINITIONS})

# - libconfig++
find_package(Config++ REQUIRED)
include_directories(${CONFIG++_INCLUDE_DIRS})
add_definitions(${CONFIG++_DEFINITIONS})

# - Boost
find_package(Boost 1.50.0 REQUIRED COMPONENTS
  filesystem
  program_options
  regex
  system
  unit_test_framework
  )
include_directories(${Boost_INCLUDE_DIRS})
add_definitions(${Boost_DEFINITIONS})

# enable rpath on OS X and point it to ROOT
if(APPLE)
  set(CMAKE_MACOSX_RPATH ON)
  set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${ROOT_LIBRARY_DIR}"
    )
endif()
# use rpath pointing to build directory
set(CMAKE_SKIP_BUILD_RPATH OFF)
set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

# Targets
# -------

# - JPetFramework
file(GLOB HEADERS framework/JPet*/*.h)
file(GLOB SOURCES framework/JPet*/*.cpp)
generate_root_dictionaries(DICTIONARIES SOURCES ${SOURCES}
  EXCLUDE # exclude following sources from ROOT dictionary
          # everything else will have dictionary generated
  # FIXME: For some reason these are excluded, it should be some better way
  # than writing them down explicitly to tell which file needs dictionary
  # and which not.
  JPetAnalysisRunner
  JPetCmdParser
  JPetDBParamGetter
  JPetManager
  JPetParamManager
  JPetReader
  JPetScopeReader
  )
add_library(JPetFramework SHARED ${SOURCES} ${HEADERS} ${DICTIONARIES})

# - Unpacker
file(GLOB UNPACKER2_HEADERS framework/JPetUnpacker/Unpacker2/*.h)
file(GLOB UNPACKER2_SOURCES framework/JPetUnpacker/Unpacker2/*.cc)
generate_root_dictionaries(UNPACKER_DICTIONARIES SOURCES ${UNPACKER2_SOURCES}
  INCLUDE # generate ROOT dictionaries for following sources
  Unpacker2
  TDCHit
  ADCHit
  Event
  UnpackingModule
  Unpacker_HPTDC_HR
  Unpacker_HPTDC_VHR
  Unpacker_HUB2
  Unpacker_TRB2
  Unpacker_Shower
  Unpacker_Ecal_ADC
  Unpacker_TRB3
  Unpacker_Lattice_TDC
  )
add_library(Unpacker2 ${UNPACKER2_HEADERS} ${UNPACKER2_SOURCES}
  ${UNPACKER_DICTIONARIES}
  )

# - DBHandler
file(GLOB DBHANDLER_HEADERS framework/DBHandler/HeaderFiles/*.h)
file(GLOB DBHANDLER_SOURCES framework/DBHandler/SourceFiles/*.cpp)
add_library(dbhandler SHARED ${DBHANDLER_HEADERS} ${DBHANDLER_SOURCES})
target_link_libraries(dbhandler
  ${PQXX_LIBRARIES}
  ${CONFIG++_LIBRARIES}
  )

# - tinyxml2
add_library(tinyxml2
  framework/JPetUnpacker/Unpacker2/tinyxml2-master/tinyxml2.h
  framework/JPetUnpacker/Unpacker2/tinyxml2-master/tinyxml2.cpp
  )

# add dependencies
target_link_libraries(JPetFramework
  Unpacker2
  tinyxml2
  dbhandler
  ${ROOT_LIBRARIES}
  ${Boost_LIBRARIES}
  )

# and all tests
file(GLOB TESTS framework/tests/*Test)
foreach(test ${TESTS})
  if(IS_DIRECTORY ${test})
    get_filename_component(test_name ${test} NAME)
    file(GLOB test_headers ${test}/*.h)
    file(GLOB test_sources ${test}/*.cpp)
    generate_root_dictionaries(test_dictionaries SOURCES ${test_sources})
    add_executable(${test_name} ${test_headers} ${test_sources}
      ${test_dictionaries}
      )
    target_link_libraries(${test_name}
      JPetFramework
      ${Boost_LIBRARIES}
      )
  endif()
endforeach()

# extra files, so they are visible in your editor
file(GLOB EXTRAS framework/extras/**)
add_custom_target(extra SOURCES ${EXTRAS}
  README
  Doxyfile
  framework/tests/README
  framework/tests/run_tests.pl
  )

# make clang print colored diagnostics when invoked from Ninja
if(UNIX AND
   CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND
   CMAKE_GENERATOR STREQUAL "Ninja")
  add_definitions(-fcolor-diagnostics)
endif()

# workaround: relocation R_X86_64_32S against `...' can not be used when
# making a shared object
if(UNIX AND CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
  set_target_properties(Unpacker2 tinyxml2 PROPERTIES COMPILE_FLAGS "-fPIC")
endif()
