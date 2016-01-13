file(GLOB TESTS tests/*Test)
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
