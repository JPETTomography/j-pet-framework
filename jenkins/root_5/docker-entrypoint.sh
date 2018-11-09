#!/bin/bash
function executeCommand {
    $@
    rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
    echo "Exit code[" $@ "]: $rc"
}

executeCommand "mkdir -p build"
executeCommand "cd build"
executeCommand "export CMAKE_LIBRARY_PATH=$CMAKE_LIBRARY_PATH:/framework-dependencies/lib"
executeCommand "export CMAKE_INCLUDE_PATH=$CMAKE_INCLUDE_PATH:/framework-dependencies/include"
executeCommand "source /root-system/bin/thisroot.sh"
executeCommand "cmake .."
executeCommand "source thisframework.sh"
executeCommand "make all tests -j4"
executeCommand "cd tests"
executeCommand "hadd -f unitTestData/JPetHaddTest/result_root5.hadd.test.root unitTestData/JPetHaddTest/dabc_17237091818.hadd.test.root unitTestData/JPetHaddTest/dabc_17237093844.hadd.test.root"
executeCommand "./run_tests.pl -f xml"
executeCommand "chmod a+x parseXML.py"
executeCommand "./parseXML.py"
