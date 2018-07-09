################################################################################
## J-PET Framework Library
##  Description:
##  Builds J-PET Framework using CMake build generator.
################################################################################

cmake_minimum_required(VERSION 2.6)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

## For generate_root_dictionaries
include(JPetFramework-Utilities)

## Using only C++
project(JPetFramework CXX C)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

## Enable C++11 and warnings
if(NOT MSVC)
  add_definitions(-std=c++11 -Wall -Wunused-parameter)
endif()

################################################################################
## Find CERN ROOT
## Try the old-school ROOTSYS variable
set(root_prefix $ENV{ROOTSYS})
if(root_prefix)
  list(APPEND CMAKE_MODULE_PATH ${root_prefix}/etc/cmake/)
endif()

## Try search based on root-config
execute_process(COMMAND root-config --etcdir OUTPUT_VARIABLE ROOT_ETCDIR OUTPUT_STRIP_TRAILING_WHITESPACE)
list(APPEND CMAKE_MODULE_PATH ${ROOT_ETCDIR}/cmake)

## Try with package search
find_package(ROOT QUIET)

## If found - print version. If not, use fallback root-config version from cmake/fallback/
if(ROOT_FOUND)
  message(STATUS "Found ROOT version: ${ROOT_VERSION} (${ROOT_CONFIG_EXECUTABLE})")
else()
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/fallback)
  message(WARNING "No CMake modules from a ROOT installation found. Trying fallback mode.")
  find_package(ROOT 5 REQUIRED)
endif()

if(ROOT_USE_FILE)
  include(${ROOT_USE_FILE})
endif()

message(STATUS "ROOT version: ")

################################################################################
## Find BOOST LIBs
set(BOOST_LOG_DYN_LINK -DBOOST_LOG_DYN_LINK)
add_definitions(${BOOST_LOG_DYN_LINK})
find_package(Boost 1.50.0 REQUIRED COMPONENTS
  filesystem
  program_options
  regex
  system
  unit_test_framework
  log_setup
  log
  date_time
  thread
  chrono
)

message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")

################################################################################
## Add definitions of ROOT and BOOST
add_definitions(${ROOT_DEFINITIONS})
add_definitions(${Boost_DEFINITIONS})

################################################################################
## Enable rpath on OS X and point it to ROOT
if(APPLE)
  set(CMAKE_MACOSX_RPATH ON)
  set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${ROOT_LIBRARY_DIR}"
  )
endif()

## Use rpath pointing to build directory
set(CMAKE_SKIP_BUILD_RPATH OFF)
set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

################################################################################
## Add Unpacker subdirectory
add_subdirectory(Unpacker2/Unpacker2)

################################################################################
## Specify source folders
set(FOLDERS_WITH_SOURCE
  Options
  ParamObjects
  DataObjects
  Tasks
  Core
  ParametersTools
  MC
)

## Point sources and headers
foreach(dir ${FOLDERS_WITH_SOURCE})
  file(GLOB HEADERS_TMP ${dir}/JPet*/*.h)
  file(GLOB SOURCES_TMP ${dir}/JPet*/*.cpp)
  file(GLOB UNIT_TEST_SOURCES_TMP ${dir}/JPet*/*Test.cpp)
  file(GLOB FOLDERS_TMP ${dir})
  list(REMOVE_ITEM FOLDERS_TMP ${HEADERS_TMP} ${SOURCES_TMP})
  list(REMOVE_ITEM SOURCES_TMP ${UNIT_TEST_SOURCES_TMP})
  list(APPEND HEADERS ${HEADERS_TMP})
  list(APPEND SOURCES ${SOURCES_TMP})
  list(APPEND UNIT_TEST_SOURCES ${UNIT_TEST_SOURCES_TMP})
  list(APPEND FOLDERS ${FOLDERS_TMP}) # path to include for dictionaries
endforeach()

list(APPEND FOLDERS ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND FOLDERS ${Boost_INCLUDE_DIRS})

################################################################################
## Download test files with external script
## Does not do anything if data has been already downloaded
set(DOWNLOAD_DATA ${CMAKE_CURRENT_SOURCE_DIR}/download_data.sh ${CMAKE_CURRENT_SOURCE_DIR})
execute_process(COMMAND ${DOWNLOAD_DATA})

################################################################################
## Generating ROOT dictionaries
generate_root_dictionaries(DICTIONARIES SOURCES ${SOURCES}
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
  JPetMCHit
  INCLUDE_DIRS ${FOLDERS}
)

################################################################################
## Building Framework library
add_library(JPetFramework SHARED ${SOURCES} ${HEADERS} ${DICTIONARIES})

foreach(dir ${FOLDERS_WITH_SOURCE})
  target_include_directories(JPetFramework PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${dir}>
    $<INSTALL_INTERFACE:${dir}>
    )
endforeach()

target_include_directories(JPetFramework PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> #add main source folder for Unpaker2
)

target_include_directories(JPetFramework SYSTEM PUBLIC
    $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>
)

target_include_directories(JPetFramework SYSTEM PUBLIC
    $<BUILD_INTERFACE:${ROOT_INCLUDE_DIRS}>
)

################################################################################
## Unit tests build
set(TESTS_DIR ${CMAKE_CURRENT_BINARY_DIR}/tests)
file(MAKE_DIRECTORY ${TESTS_DIR})
file(COPY unitTestUtils/run_tests.pl DESTINATION ${TESTS_DIR})
file(COPY unitTestUtils/parseXML.py DESTINATION ${TESTS_DIR})
foreach(test_source ${UNIT_TEST_SOURCES})
  get_filename_component(test ${test_source} NAME_WE)
  generate_root_dictionaries(test_dictionaries SOURCES ${test_source} INCLUDE_DIRS ${FOLDERS})
  list(APPEND test_binaries ${test}.x)
  add_executable(${test}.x EXCLUDE_FROM_ALL ${test_source}
    ${test_dictionaries}
  )
  set_target_properties(${test}.x PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_DIR})
  target_link_libraries(${test}.x
    JPetFramework
    ${Boost_LIBRARIES}
  )
endforeach()

add_custom_target(tests DEPENDS ${test_binaries} ${TESTS_DIR}/unitTestData)

## Create a symlink to the directory with data necessary for some unit tests
add_custom_command(OUTPUT ${TESTS_DIR}/unitTestData
  COMMAND ln -s ${CMAKE_CURRENT_SOURCE_DIR}/unitTestData ${TESTS_DIR}/unitTestData
)

################################################################################
## Add dependencies to Framework library
target_link_libraries(JPetFramework Unpacker2 ${ROOT_LIBRARIES} ${Boost_LIBRARIES})

## handle the ROOT's *.pcm files in case they were generated not in the build dir
find_program(SHELL bash)
if(SHELL)
  set(pcm_script ${CMAKE_CURRENT_BINARY_DIR}/move_pcm.sh)

  FILE(WRITE ${pcm_script}  "#!${SHELL}\n")
  FILE(APPEND ${pcm_script} "for f in ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Dictionaries/*.pcm; do\n")
  FILE(APPEND ${pcm_script} "[ -e \$f ] && mv \$f ${CMAKE_CURRENT_BINARY_DIR}\n")
  FILE(APPEND ${pcm_script} "done\n")
  FILE(APPEND ${pcm_script} "exit 0\n")

  add_custom_command(TARGET JPetFramework POST_BUILD
    COMMAND ${SHELL}  ${pcm_script}
  )
endif(SHELL)

################################################################################
## Read the version from git tag and git revision
exec_program(
  "git"
  ${CMAKE_CURRENT_SOURCE_DIR}
  ARGS "describe --tags --abbrev=0"
  OUTPUT_VARIABLE FRAMEWORK_VERSION
)
exec_program(
  "git"
  ${CMAKE_CURRENT_SOURCE_DIR}
  ARGS "rev-parse HEAD"
  OUTPUT_VARIABLE FRAMEWORK_REVISION
)

## Create the header file with framework version information
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/version.h ESCAPE_QUOTES @ONLY)

## Extra files, so they are visible in your editor
file(GLOB EXTRAS extras/**)
add_custom_target(extra SOURCES ${EXTRAS}
  README.md
  Doxyfile
  unitTestUtils/run_tests.pl
)

## Make clang print colored diagnostics when invoked from Ninja
if(UNIX AND
   CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND
   CMAKE_GENERATOR STREQUAL "Ninja")
  add_definitions(-fcolor-diagnostics)
endif()

## Workaround: relocation R_X86_64_32S against `...' can not be used when
## making a shared object
if(UNIX AND CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
  set_target_properties(Unpacker2 PROPERTIES COMPILE_FLAGS "-fPIC")
endif()

################################################################################
## Generating documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(documentation
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
  )
endif(DOXYGEN_FOUND)

get_target_property(framework_include JPetFramework INCLUDE_DIRECTORIES)
get_directory_property(has_parent PARENT_DIRECTORY)
if(has_parent)
  # export ROOT, Boost includes to depending projects
  set(Framework_INCLUDE_DIRS
    ${framework_include}
    PARENT_SCOPE
  )
  list(APPEND Framework_DEFINITIONS "${BOOST_LOG_DYN_LINK} ${ROOT_DEFINITIONS}")
  # ensure that projects use C++11 too
  if(NOT MSVC)
    set(Framework_DEFINITIONS
      "-std=c++11 ${Framework_DEFINITIONS}"
      PARENT_SCOPE
    )
  endif()
  # export ROOT cint needed to generate dictionaries from projects
  set(ROOT_rootcint_CMD ${ROOT_rootcint_CMD} PARENT_SCOPE)
  set(rootcint_cmd ${ROOT_rootcint_CMD} PARENT_SCOPE)
  set(ROOTCINT_EXECUTABLE ${ROOTCINT_EXECUTABLE} PARENT_SCOPE)
  # export ROOT rpath needed for OS X
  set(ROOT_LIBRARY_DIR ${ROOT_LIBRARY_DIR} PARENT_SCOPE)
  set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} PARENT_SCOPE)
endif()

################################################################################
