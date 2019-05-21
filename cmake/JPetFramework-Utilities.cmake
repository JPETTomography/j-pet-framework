macro(package_add_test TESTNAME)
    add_executable(${TESTNAME}.x ${ARGN})
    target_compile_options(${TESTNAME}.x PRIVATE -Wunused-parameter -Wall)
    target_link_libraries(${TESTNAME}.x JPetFramework Boost::unit_test_framework)
    add_test(NAME ${TESTNAME}.x COMMAND ${TESTNAME}.x "--log_level=ERROR --log_format=XML --raport_level=no")
    set_target_properties(${TESTNAME}.x PROPERTIES FOLDER tests)
    add_dependencies(${TESTNAME}.x link_target)
endmacro()


function(package_add_format_hook)
  set(INSTALL_HOOK ${CMAKE_CURRENT_SOURCE_DIR}/hooks/git-pre-commit-format install)
  execute_process(COMMAND ${INSTALL_HOOK})
endfunction()