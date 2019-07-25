#!/bin/bash
function executeCommand {
    $@
    rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
    echo "Exit code[" $@ "]: $rc"
}
executeCommand "export CMAKE_LIBRARY_PATH=$CMAKE_LIBRARY_PATH:/framework-dependencies/lib"
executeCommand "export CMAKE_INCLUDE_PATH=$CMAKE_INCLUDE_PATH:/framework-dependencies/include"
executeCommand "source /root-system/bin/thisroot.sh"
executeCommand "mkdir -p build"
executeCommand "cd build"
executeCommand "cmake .."
executeCommand "make all tests -j4"
executeCommand "source bin/thisframework.sh"
executeCommand "ctest -j6 -C Debug -T test --output-on-failure"