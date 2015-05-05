OS = $(shell uname)
CC = g++
LD = $(CC) 
DEBUG_FLAG = -ggdb
#######################
COPTS = -Wall `root-config --cflags` $(DEBUG_FLAG) -O2 -std=c++0x
LDOPTS = -Wall `root-config --glibs` $(DEBUG_FLAG) -lboost_program_options -lboost_system -lboost_filesystem -lboost_unit_test_framework
#######################
SRC_MODULE = # ModuleName.cpp
HDR_MODULE = $(SRC_MODULE:.cpp=.h)
OBJ_MODULE = $(SRC_MODULE:.cpp=.o)
SRC_MAIN = JPetScopeReaderTest.cpp
OBJ_MAIN = $(SRC_MAIN:.cpp=.o)
#######################
EXECUTABLE = $(SRC_MAIN:.cpp=.exe)
LOG = JPet.log
#######################
SRC_DICT = # moduleDict.cpp
HDR_DICT = $(SRC_DICT:.cpp=.h)
OBJ_DICT = $(SRC_DICT:.cpp=.o)
#######################
SOURCES = $(SRC_MAIN) $(SRC_MODULE) $(SRC_DICT) 
OBJECTS = $(OBJ_MAIN) $(OBJ_MODULE) $(OBJ_DICT)
SHAREDLIB_DIR = ../../..
SHAREDLIBS = $(SHAREDLIB_DIR)/libJPetFramework.so #$(SHAREDLIB_DIR)/framework/JPetTreeHeader/libJPetTreeHeader.so 
SHAREDLIBS += $(SHAREDLIB_DIR)/framework/DBHandler/libdbhandler.so
ifeq ($(OS), Darwin)
	LDOPTS += -rpath @loader_path/$(SHAREDLIB_DIR)
endif
#######################
%.o: %.cpp
	$(CC) $^ -o $@ -c $(COPTS)
#######################
# ifndef ROOTSYS
# $(error ROOTSYS is not set)
# endif
#######################
all: $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS) $(SHAREDLIBS)
	$(LD) -o $@ $^ $(LDOPTS)
# $(OBJ_MODULE): $(SRC_MODULE)
# $(OBJ_MAIN): $(SRC_MAIN)
$(SHAREDLIBS): 
	cd ../..; $(MAKE) modules sharedlib;
$(SRC_DICT):
	rootcint -f $@ -c -P -I$(ROOTSYS) $(HDR_MODULE) 
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(SRC_DICT) $(HDR_DICT) $(LOG) *.o
