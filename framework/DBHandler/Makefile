##################
#
# Makefile for DBHadler code
#
###################
OS = $(shell uname)
CC=g++
CFLAGS= -I/usr/local/include/ -std=c++0x -Wall -fPIC
LDFLAGS= -std=c++0x -lconfig++ -Wall -lpqxx -lpq 
HDR_DIR = HeaderFiles
SRC_DIR = SourceFiles
CPP_FILES= Functions RunData DBHandler PhotoMultiplierMap RunDataMap TRBThresholdMap PhotoMultiplierIdMap TOMBInputMap PassedInformationMap ParamServer ParamData 
###################
CPP_MODULES=$(foreach dir, $(CPP_FILES), $(SRC_DIR)/$(dir).cpp)
OBJECTS=$(foreach dir, $(CPP_FILES), $(SRC_DIR)/$(dir).o)
###################
CPP_MAIN = $(SRC_DIR)/Main.cpp
OBJ_MAIN = $(CPP_MAIN:.cpp=.o)
EXEC= dbhandler
###################
%.o: %.cpp
	$(CC) $^ -o $@  -c $(CFLAGS)
###################
PHOTOMULTIPLIER_MAP_FILE=PhotoMultiplierMap.txt
###################
LIBDBHANDLER = libdbhandler.so
###################
all: $(OBJECTS) $(OBJ_MAIN)
	$(CC) $(OBJECTS) $(OBJ_MAIN) $(LDFLAGS) -o $(EXEC)
sharedlib: $(OBJECTS) 
	$(LD) -shared -o $(LIBDBHANDLER) $(OBJECTS) $(LD_FLAGS);
ifeq ($(OS), Darwin)
	install_name_tool -id @rpath/$(LIBDBHANDLER) $(LIBDBHANDLER)
endif
run:
	./$(EXEC)
clean:
	rm -f *~ $(LIBDBHANDLER) $(OBJECTS) $(EXEC) $(PHOTOMULTIPLIER_MAP_FILE) 
