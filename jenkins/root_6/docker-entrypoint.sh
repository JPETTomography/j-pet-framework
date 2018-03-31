mkdir -p build
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
cd build
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
export CMAKE_LIBRARY_PATH=$CMAKE_LIBRARY_PATH:/framework-dependencies/lib
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
export CMAKE_INCLUDE_PATH=$CMAKE_INCLUDE_PATH:/framework-dependencies/include
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
source /root-system/bin/thisroot.sh
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
cmake ..
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
make all tests -j4
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
cd tests
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
./run_tests.pl -f xml
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
chmod a+x parseXML.py
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
./parseXML.py
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
