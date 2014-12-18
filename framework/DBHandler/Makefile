##################
#
# Makefile for DBHadler library 
#
###################
OS = $(shell uname)
CC=g++
LD = $(CC)
CFLAGS= -I/usr/local/include/ -std=c++0x -Wall -fPIC -O2
LDFLAGS= -std=c++0x -lconfig++ -Wall -lpqxx -lpq 
HDR_DIR = HeaderFiles
SRC_DIR = SourceFiles
CPP_FILES= Functions RunData DBHandler PhotoMultiplierMap RunDataMap TRBThresholdMap PhotoMultiplierIdMap TOMBInputMap PassedInformationMap ParamServer ParamData 
###################
CPP_MODULES=$(foreach dir, $(CPP_FILES), $(SRC_DIR)/$(dir).cpp)
OBJECTS=$(foreach dir, $(CPP_FILES), $(SRC_DIR)/$(dir).o)
###################
%.o: %.cpp
	$(CC) $^ -o $@  -c $(CFLAGS)
###################
PHOTOMULTIPLIER_MAP_FILE=PhotoMultiplierMap.txt
###################
LIBDBHANDLER = libdbhandler.so
###################
all: sharedlib 
sharedlib: $(OBJECTS)
	$(LD) -shared -o $(LIBDBHANDLER) $(OBJECTS) $(LDFLAGS);
ifeq ($(OS), Darwin)
	install_name_tool -id @rpath/$(LIBDBHANDLER) $(LIBDBHANDLER)
endif
clean:
	rm -f *~ $(LIBDBHANDLER) $(OBJECTS)  $(PHOTOMULTIPLIER_MAP_FILE) 
