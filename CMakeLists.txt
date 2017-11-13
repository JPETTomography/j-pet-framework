# J-PET framework project main description file
#
# Author: Adam Strzelecki <adam.strzelecki@uj.edu.pl>
#
# Description:
#   Builds all J-PET framework modules using CMake build generator.

cmake_minimum_required(VERSION 2.6)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(JPetFramework-Utilities) # for generate_root_dictionaries

project(JPetFramework CXX C) # using only C++
# enable C++11 and warnings
if(NOT MSVC)
  add_definitions(-std=c++11 -Wall -Wunused-parameter)
endif()

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
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/fallback)
endforeach()
include_directories(${ROOT_INCLUDE_DIRS})
add_definitions(${ROOT_DEFINITIONS})
message(STATUS "ROOT version: ${ROOT_VERSION}")
if(ROOT_FOUND AND NOT ROOT_VERSION VERSION_LESS "6.0")
  message(FATAL_ERROR "ROOT 6.0 is not compatible")
endif()

find_package(PQXX REQUIRED)
include_directories(${PQXX_INCLUDE_DIRS})
add_definitions(${PQXX_DEFINITIONS})

find_package(Boost 1.50.0 REQUIRED COMPONENTS
  filesystem
  program_options
  regex
  system
  unit_test_framework
  )

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
add_definitions(${Boost_DEFINITIONS})

find_package(FFTW REQUIRED)
include_directories(${FFTW_INCLUDE_DIRS})

get_directory_property(has_parent PARENT_DIRECTORY)
if(has_parent)
  # export ROOT, Boost and pqxx includes to depending projects
  set(Framework_INCLUDE_DIRS
    ${ROOT_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${PQXX_INCLUDE_DIRS}
    PARENT_SCOPE
    )
  set(Framework_DEFINITIONS
    ${ROOT_DEFINITIONS}
    ${Boost_DEFINITIONS}
    ${PQXX_DEFINITIONS}
    PARENT_SCOPE
    )
  # ensure that projects use C++11 too
  if(NOT MSVC)
    set(Framework_DEFINITIONS
      -std=c++11
      ${Framework_DEFINITIONS}
      PARENT_SCOPE
      )
  endif()
  # export ROOT cint needed to generate dictionaries from projects
  set(ROOT_rootcint_CMD   ${ROOT_rootcint_CMD}   PARENT_SCOPE)
  set(rootcint_cmd        ${ROOT_rootcint_CMD}   PARENT_SCOPE)
  set(ROOTCINT_EXECUTABLE ${ROOTCINT_EXECUTABLE} PARENT_SCOPE)
  # export ROOT rpath needed for OS X
  set(ROOT_LIBRARY_DIR    ${ROOT_LIBRARY_DIR}    PARENT_SCOPE)
endif()

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

# add Unpacker subdirectory
add_subdirectory(Unpacker2/Unpacker2)

file(GLOB HEADERS JPet*/*.h tools/JPet*/*.h)
file(GLOB SOURCES JPet*/*.cpp tools/JPet*/*.cpp)
file(GLOB UNIT_TEST_SOURCES JPet*/*Test.cpp)
list(REMOVE_ITEM SOURCES ${UNIT_TEST_SOURCES})

##download test files and config files
# the script shouldn't do anything if the data is present and correct
set(DOWNLOAD_DATA ${CMAKE_CURRENT_SOURCE_DIR}/download_data.sh ${CMAKE_CURRENT_SOURCE_DIR})
execute_process( COMMAND ${DOWNLOAD_DATA} )

generate_root_dictionaries(DICTIONARIES SOURCES ${SOURCES}
  # exclude following sources from ROOT dictionary
  # everything else will have dictionary generated
  # FIXME: For some reason these are excluded, it should be some better way
  # than writing them down explicitly to tell which file needs dictionary
  # and which not.
  INCLUDE
  JPetTimeWindow
  JPetSigCh
  JPetBaseSignal
  JPetRawSignal
  JPetRecoSignal
  JPetPhysSignal
  JPetStatistics
  JPetAuxilliaryData
  JPetTreeHeader
  JPetParamBank
  JPetHit
  JPetLOR
  JPetPM
  JPetScin
  JPetTRB
  JPetTOMBChannel
  JPetBarrel
  JPetLayer
  JPetBarrelSlot
  JPetFrame
  JPetFEB
  JPetUser
  JPetUnpacker
  JPetEvent
  )
add_library(JPetFramework SHARED ${SOURCES} ${HEADERS} ${DICTIONARIES})

# unit tests
set(TESTS_DIR ${CMAKE_CURRENT_BINARY_DIR}/tests)
file(MAKE_DIRECTORY ${TESTS_DIR})
file(COPY unitTestUtils/run_tests.pl DESTINATION ${TESTS_DIR})
file(COPY unitTestUtils/parseXML.py DESTINATION ${TESTS_DIR})
foreach(test_source ${UNIT_TEST_SOURCES})
  get_filename_component(test ${test_source} NAME_WE)
  generate_root_dictionaries(test_dictionaries SOURCES ${test_source})
  list(APPEND test_binaries ${test}.x)
  add_executable(${test}.x EXCLUDE_FROM_ALL ${test_source}
    ${test_dictionaries}
    )
  set_target_properties(${test}.x PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_DIR} )
  target_link_libraries(${test}.x
    JPetFramework
    ${Boost_LIBRARIES}
    ${FFTW_LIBRARIES}
    )

endforeach()

add_custom_target(tests DEPENDS ${test_binaries} ${TESTS_DIR}/unitTestData)

# create a symlink to the directory with data necessary for some unit tests
add_custom_command(OUTPUT ${TESTS_DIR}/unitTestData
  COMMAND ln -s ${CMAKE_CURRENT_SOURCE_DIR}/unitTestData ${TESTS_DIR}/unitTestData
  )

# - DBHandler
file(GLOB DBHANDLER_HEADERS DBHandler/HeaderFiles/*.h)
file(GLOB DBHANDLER_SOURCES DBHandler/SourceFiles/*.cpp)
add_library(dbhandler SHARED ${DBHANDLER_HEADERS} ${DBHANDLER_SOURCES})
target_link_libraries(dbhandler
  ${PQXX_LIBRARIES}
  )

# copy the DB config file to an expected location
set(db_config_dir ${CMAKE_CURRENT_BINARY_DIR}/DBConfig)
add_custom_command(TARGET dbhandler
  POST_BUILD 
  COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/DBHandler/Config ${db_config_dir}
  )

# add dependencies
target_link_libraries(JPetFramework
  Unpacker2
  dbhandler
  ${ROOT_LIBRARIES}
  ${Boost_LIBRARIES}
  )

# read the version from git tag and git revision
exec_program(
  "git"
  ${CMAKE_CURRENT_SOURCE_DIR}
  ARGS "describe --tags --abbrev=0"
  OUTPUT_VARIABLE FRAMEWORK_VERSION )

exec_program(
  "git"
  ${CMAKE_CURRENT_SOURCE_DIR}
  ARGS "rev-parse HEAD"
  OUTPUT_VARIABLE FRAMEWORK_REVISION )

# create the header file with framework version information
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/version.h ESCAPE_QUOTES @ONLY)

# extra files, so they are visible in your editor
file(GLOB EXTRAS extras/**)
add_custom_target(extra SOURCES ${EXTRAS}
  README
  Doxyfile
  unitTestUtils/run_tests.pl
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
  set_target_properties(Unpacker2 PROPERTIES COMPILE_FLAGS "-fPIC")
endif()


# generating documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(documentation
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)
