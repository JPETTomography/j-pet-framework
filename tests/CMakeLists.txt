enable_testing()

set(CMAKE_CXX_STANDARD 11) # maybe not best solutio to set it globally? upgrate minimal cmake version to 3.8 or find another way to set it only for target with interface
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

#Configure Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.50 REQUIRED COMPONENTS unit_test_framework)

if(NOT TARGET Boost::unit_test_framework)
    add_library(Boost::unit_test_framework IMPORTED INTERFACE)
    set_property(TARGET Boost::unit_test_framework PROPERTY
        INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
    set_property(TARGET Boost::unit_test_framework PROPERTY
        INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
endif()
#End of configuration of Boost
set(TESTS_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_custom_target(link_target ALL
                  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/../unitTestData ${TESTS_DIR}/unitTestData)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME}.x ${ARGN})
    target_compile_options(${TESTNAME}.x PRIVATE -Wunused-parameter -Wall)
    target_compile_definitions(${TESTNAME}.x PRIVATE BOOST_LOG_DYN_LINK=true)
    target_link_libraries(${TESTNAME}.x JPetFramework Boost::unit_test_framework)
    add_test(NAME ${TESTNAME}.x COMMAND ${TESTNAME}.x "--log_level=ALL --log_format=XML --log_sink=${TESTNAME}.xml --raport_level=no")
    set_target_properties(${TESTNAME}.x PROPERTIES FOLDER tests)
    add_dependencies(${TESTNAME}.x link_target)
endmacro()

foreach(test_source ${UNIT_TEST_SOURCES})
    get_filename_component(test ${test_source} NAME_WE)
    package_add_test(${test} ${test_source})
endforeach()

file(COPY ../unitTestUtils/parseXML.py DESTINATION ${TESTS_DIR})
