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

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME}.x ${ARGN})
    target_compile_options(${TESTNAME}.x PRIVATE -Wunused-parameter -Wall)
    target_compile_definitions(${TESTNAME}.x PRIVATE BOOST_LOG_DYN_LINK=true)
    target_link_libraries(${TESTNAME}.x JPetFramework Boost::unit_test_framework)
    add_test(NAME ${TESTNAME}.x COMMAND ${TESTNAME}.x)
    set_target_properties(${TESTNAME}.x PROPERTIES FOLDER tests)
    list(APPEND test_binaries ${TESTNAME}.x)
endmacro()

set(TESTS_DIR ${CMAKE_CURRENT_BINARY_DIR})
foreach(test_source ${UNIT_TEST_SOURCES})
    get_filename_component(test ${test_source} NAME_WE)
    package_add_test(${test} ${test_source})
endforeach()

add_custom_command(OUTPUT ${TESTS_DIR}/unitTestData
  COMMAND ln -s ${CMAKE_CURRENT_SOURCE_DIR}/../unitTestData ${TESTS_DIR}/unitTestData
)

file(COPY ../unitTestUtils/run_tests.pl DESTINATION ${TESTS_DIR})
file(COPY ../unitTestUtils/parseXML.py DESTINATION ${TESTS_DIR})

add_custom_target(tests DEPENDS ${test_binaries} ${TESTS_DIR}/unitTestData)


#set(TESTS_DIR ${CMAKE_CURRENT_BINARY_DIR}/tests)
#
#  get_filename_component(test ${test_source} NAME_WE)
#  generate_root_dictionaries(test_dictionaries SOURCES ${test_source} INCLUDE_DIRS ${FOLDERS})
#  
#  add_executable(${test} EXCLUDE_FROM_ALL ${test_source}
#    ${test_dictionaries}
#  )
#  set_target_properties(${test}.x PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_DIR})
#  target_link_libraries(${test}.x
#    JPetFramework
#    ${Boost_LIBRARIES}
#  )
#
