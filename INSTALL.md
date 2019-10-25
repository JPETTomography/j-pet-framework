# Installation

## Basic steps

1. Install the required libraries and tools.  
   Refer to the `Requirements` section of this document for details.  
   You can find ready commands for some systems in the `Requirements installation` section.

2. Create a directory where the built programs will be placed, e.g. in the main directory:  
   `mkdir build`  
   `cd build`

3. Invoke the CMake build tool and provide the path to the source directory as well as path to install.
   If you created the build directory in the main one and entered `build` as in step 2. then do:  
   `cmake -DCMAKE_INSTALL_PREFIX=<install_path> ..`
   If you didn't install Unpacker2 globally on the system also provide path to Unpacker2_DIR:
   `cmake -DCMAKE_INSTALL_PREFIX=<install_path> -DUnpacker2_DIR=<path_to_unpacker2> ..`

4. To compile the J-PET Framework Library do:  
   `make`

5. Once the compilation is finished, you can run tests with:
   `ctest`
   or install libraries in <install_path> using:
   `make install`

**NOTE:** Full install procedure with tips and troubleshootung can be found on [PetWiki](http://koza.if.uj.edu.pl/petwiki/index.php/Installing_the_J-PET_Framework_on_Ubuntu)


## Code documentation

To generate the code documentation of the J-PET Framework library, the Doxygen software must be installed.
To generate the documentation just go to the j-pet-framework build directory and do:
```
make documentation
```
and the documentation will be generated and put in folders named latex and html inside the build directory.


## Requirements
1. gcc

2. [cmake](https://cmake.org/)

3. [ROOT](http://root.cern.ch)  
   Works with ROOT 6 (tested 6.10/08)

4. [BOOST](https://www.boost.org/)

5. [Unpacker2](https://github.com/JPETTomography/Unpacker2)

6. (Optional)To generate documentation: [Doxygen](www.doxygen.org)
