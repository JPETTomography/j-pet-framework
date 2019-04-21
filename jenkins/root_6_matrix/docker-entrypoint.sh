#!/bin/bash
function executeCommand {
    $@
    rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
    echo "Exit code[" $@ "]: $rc"
}
executeCommand "export CMAKE_LIBRARY_PATH=$CMAKE_LIBRARY_PATH:/framework-dependencies/lib"
executeCommand "export CMAKE_INCLUDE_PATH=$CMAKE_INCLUDE_PATH:/framework-dependencies/include"
executeCommand "source /root-system/bin/thisroot.sh"
executeCommand "rm -rf Unpacker2 || true"
executeCommand "git clone --single-branch --branch cmake https://github.com/grey277/Unpacker2.git"
executeCommand "mkdir -p Unpacker2/build"
executeCommand "cd Unpacker2/build"
executeCommand "cmake .."
executeCommand "cmake --build ."
executeCommand "sudo make install"
executeCommand "cd ../.."
executeCommand "mkdir -p build"
executeCommand "cd build"
executeCommand "cmake .."
executeCommand "source thisframework.sh"
executeCommand "make all tests -j4"
executeCommand "cd tests"
executeCommand "ctest"
executeCommand "grep -rwnl . -e 'Error' | xarg cat"