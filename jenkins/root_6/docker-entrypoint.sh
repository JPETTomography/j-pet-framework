mkdir -p build
cd build
export CMAKE_LIBRARY_PATH=$CMAKE_LIBRARY_PATH:/framework-dependencies/lib
export CMAKE_INCLUDE_PATH=$CMAKE_INCLUDE_PATH:/framework-dependencies/include
source /root-system/bin/thisroot.sh
cmake ..
make all tests -j4
cd tests
./run_tests.pl -f xml
chmod a+x parseXML.py
./parseXML.py
