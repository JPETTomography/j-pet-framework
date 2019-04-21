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

project(JPetFramework VERSION 1.0.0
                  LANGUAGES CXX)
set(PROJECT_DESCRIPTION "JPetFramework module")

message(STATUS "")
message(STATUS "    == ${PROJECT_NAME} Project configuration ==")
message(STATUS "")

set(CMAKE_CXX_STANDARD 11) # maybe not best solution to set it globally? upgrate minimal cmake version to 3.8 or find another way to set it only for target with interface
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_PLATFORM_INDEPENDENT_CODE ON)

# Force out-of-source build
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

# Include cmake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(JPetFramework-Utilities)

################################################################################
## Install format hook to git
## Automatically installs hook to .git/hooks/pre-commit to format code with clang-format
option(INSTALL_HOOK "Install format hook to .git/hooks/pre-commit" ON)
if(INSTALL_HOOK)
  message(STATUS "Trying to install format hook..")
  package_add_format_hook()
endif()

add_subdirectory(src)

#documentation
option(PACKAGE_DOC "Build the documentation" ON)
if(PACKAGE_TESTS)
  add_subdirectory(doc)
endif()

#unit tests
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

################################################################################
# Wrap up of settings printed on build
message(STATUS "")
message(STATUS "    == Final overview for ${PROJECT_NAME} ==")
message(STATUS "Version:              ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
message(STATUS "Install prefix:       ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Compiler:             ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_BUILD_TYPE:     ${CMAKE_BUILD_TYPE}")
message(STATUS "  possible options: Debug Release RelWithDebInfo MinSizeRel")
message(STATUS "  set with ` cmake -DCMAKE_BUILD_TYPE=Debug .. `")
message(STATUS "")

