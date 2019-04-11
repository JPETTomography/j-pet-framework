################################################################################
## J-PET Framework Library
##  Description:
##  Builds J-PET Framework using CMake build generator.
################################################################################

cmake_minimum_required(VERSION 3.1...3.14)

if(${CMAKE_VERSION} VERSION_LESS 3.14)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.14)
endif()

# Force out-of-source build
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

project(JPetFramework VERSION 1.0.0
                  DESCRIPTION "JPetFramework module"
                  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11) # maybe not best solution to set it globally? upgrate minimal cmake version to 3.8 or find another way to set it only for target with interface
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_PLATFORM_INDEPENDENT_CODE ON)

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

## For generate_root_dictionaries
include(JPetFramework-Utilities)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    Unpacker2ConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

find_package(Threads)

################################################################################
## Find CERN ROOT
# first try to find ROOT 6 compiled with CMake
# if present, such ROOT should be possible to find without explicit setting of any paths
find_package(ROOT CONFIG REQUIRED)
if(ROOT_FOUND)
  message(STATUS "ROOT (version ${ROOT_VERSION}) was found using ROOTConfig")
endif()

include("${ROOT_DIR}/modules/RootNewMacros.cmake")
# fix missing include directories property in versions < ROOT 6.12
set_target_properties(ROOT::Core PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${ROOT_INCLUDE_DIRS}")


add_library(ROOT::Flags_CXX IMPORTED INTERFACE)

# Fix for ROOT_CXX_FLAGS not actually being a CMake list
separate_arguments(ROOT_CXX_FLAGS)
set_property(TARGET ROOT::Flags_CXX APPEND PROPERTY
    INTERFACE_COMPILE_OPTIONS ${ROOT_CXX_FLAGS})

# Add definitions
separate_arguments(ROOT_DEFINITIONS)
foreach(_flag ${ROOT_EXE_LINKER_FLAG_LIST})
    # Remove -D or /D if present
    string(REGEX REPLACE [=[^[-//]D]=] "" _flag ${_flag})
    set_property(TARGET ROOT::Flags APPEND PROPERTY INTERFACE_LINK_LIBRARIES ${_flag})
endforeach()

# This also fixes a bug in the linker flags
string(REPLACE "-L " "-L" ROOT_EXE_LINKER_FLAGS "${ROOT_EXE_LINKER_FLAGS}")
separate_arguments(ROOT_EXE_LINKER_FLAGS)
set_property(TARGET ROOT::Flags_CXX APPEND PROPERTY
    INTERFACE_LINK_LIBRARIES ${ROOT_EXE_LINKER_FLAGS})

################################################################################
## Find BOOST LIBs
set(BOOST_LOG_DYN_LINK -DBOOST_LOG_DYN_LINK)
add_definitions(${BOOST_LOG_DYN_LINK})

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.50 REQUIRED 
             COMPONENTS filesystem
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

if(NOT TARGET Boost::filesystem)
    add_library(Boost::filesystem IMPORTED INTERFACE)
    set_property(TARGET Boost::filesystem PROPERTY
        INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
    set_property(TARGET Boost::filesystem PROPERTY
        INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
endif()

message(STATUS "Boost_VERSION: ${Boost_VERSION}")

################################################################################
## Find Unpacker2
find_package(Unpacker2 REQUIRED)

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
  GeantParser
  )

## Point sources and headers
foreach(dir ${FOLDERS_WITH_SOURCE})
  file(GLOB HEADERS_TMP ${dir}/JPet*/*.h)
  file(GLOB SOURCES_TMP ${dir}/JPet*/*.cpp)
  file(GLOB UNIT_TEST_SOURCES_TMP ${dir}/JPet*/*Test.cpp)
  file(GLOB FOLDERS_TMP ${dir})
  list(REMOVE_ITEM FOLDERS_TMP ${HEADERS_TMP} ${SOURCES_TMP})
  if(UNIT_TEST_SOURCES_TMP)
    list(REMOVE_ITEM SOURCES_TMP ${UNIT_TEST_SOURCES_TMP})
  endif()
  list(APPEND HEADERS ${HEADERS_TMP})
  list(APPEND SOURCES ${SOURCES_TMP})
  list(APPEND UNIT_TEST_SOURCES ${UNIT_TEST_SOURCES_TMP})
  list(APPEND FOLDERS ${FOLDERS_TMP}) # path to include for dictionaries
endforeach()

list(APPEND FOLDERS ${CMAKE_PREFIX_PATH}/include)
list(APPEND FOLDERS ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND FOLDERS ${Boost_INCLUDE_DIRS})

################################################################################
## Download test files with external script
## Does not do anything if data has been already downloaded
set(DOWNLOAD_DATA ${CMAKE_CURRENT_SOURCE_DIR}/download_data.sh ${CMAKE_CURRENT_SOURCE_DIR})
execute_process(COMMAND ${DOWNLOAD_DATA})

message(FOLDERS: ${FOLDERS})
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
  JPetTimeWindowMC
  JPetMCDecayTree
  JPetGeantScinHits
  JPetGeantDecayTree
  JPetGeantEventPack
  JPetGeantEventInformation
  INCLUDE_DIRS ${FOLDERS}
  RESULT_NAME JPetFramework
)

################################################################################
## Building Framework library
add_library(JPetFramework SHARED ${SOURCES} ${HEADERS} ${DICTIONARIES})
add_library(JPetFramework::JPetFramework ALIAS JPetFramework)
target_compile_options(JPetFramework PRIVATE -Wunused-parameter -Wall)
target_compile_definitions(JPetFramework PRIVATE BOOST_LOG_DYN_LINK=true)
foreach(dir ${FOLDERS_WITH_SOURCE})
  target_include_directories(JPetFramework PUBLIC
                             $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${dir}>
                             $<INSTALL_INTERFACE:${dir}>
                            )
endforeach()
set_target_properties(JPetFramework PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(JPetFramework PUBLIC Unpacker2::Unpacker2
                                           Boost::filesystem
                                           Boost::program_options
                                           Boost::regex
                                           Boost::system
                                           Boost::unit_test_framework
                                           Boost::log_setup
                                           Boost::log
                                           Boost::date_time
                                           Boost::thread
                                           Boost::chrono
                                           ROOT::Core 
                                           ROOT::Physics
                                           ROOT::Hist
                                           ROOT::RIO
                                           ROOT::Thread
                                           ROOT::HistPainter
                                           ROOT::Tree
                                           ROOT::Flags_CXX
                                           Threads::Threads
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

## Create the thisframework.sh file with correct LD_LIBRARY_PATH information
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/thisframework.sh.in
  ${CMAKE_CURRENT_BINARY_DIR}/thisframework.sh ESCAPE_QUOTES @ONLY)

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
  set_target_properties(Unpacker2::Unpacker2 PROPERTIES COMPILE_FLAGS "-fPIC")
endif()

################################################################################
## Install format hook to git
## Automatically installs hook to .git/hooks/pre-commit to format code with clang-format
set(INSTALL_HOOK ${CMAKE_CURRENT_SOURCE_DIR}/hooks/git-pre-commit-format install)
execute_process(COMMAND ${INSTALL_HOOK})

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
