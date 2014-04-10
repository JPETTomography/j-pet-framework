##################
#
# Makefile for DBHadler code
#
###################
CC=g++
CFLAGS= -I/usr/local/include/ -std=c++0x -Wall
LDFLAGS= -std=c++0x -lconfig++ -Wall -lpqxx -lpq
HDR_DIR = HeaderFiles
SRC_DIR = SourceFiles
HPP_FILES= SerializableMap
CPP_FILES= Functions RunData DBHandler PhotoMultiplierMap RunDataMap TRBThresholdMap PhotoMultiplierIdMap TOMBInputMap PassedInformationMap ParamServer Main
HPP_MODULES=$(foreach dir, $(HPP_FILES), $(HDR_DIR)/$(dir).hpp)
CPP_MODULES=$(foreach dir, $(CPP_FILES), $(SRC_DIR)/$(dir).cpp)
OBJECTS=$(foreach dir, $(CPP_FILES), $(SRC_DIR)/$(dir).o)
EXEC=dbhandler
###################
%.o: %.cpp
	$(CC) $^ -o $@  -c $(CFLAGS)
###################
PHOTOMULTIPLIER_MAP_FILE=PhotoMultiplierMap.txt
###################
all: $(OBJECTS)
	$(CC) $(HPP_MODULES) $(OBJECTS) $(LDFLAGS) -o $(EXEC)
run:
	./$(EXEC)
start:
	clear && $(CC) $(HPP_MODULES) $(CPP_MODULES) $(CFLAGS) -o $(EXEC) && ./$(EXEC)
#documentation:
#	doxygen Doxyfile
clean:
	rm -f *~ $(OBJECTS) $(EXEC) $(PHOTOMULTIPLIER_MAP_FILE) 
