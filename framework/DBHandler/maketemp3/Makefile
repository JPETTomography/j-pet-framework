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
CPP_FILES= Functions RunData DBHandler PhotoMultiplierMap RunDataMap TRBThresholdMap PhotoMultiplierIdMap TOMBInputMap PassedInformationMap ParamServer ParamData Main
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
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(EXEC)
run:
	./$(EXEC)
start:
	clear && $(CC) $(CPP_MODULES) $(CFLAGS) -o $(EXEC) && ./$(EXEC)
#documentation:
#	doxygen Doxyfile
clean:
	rm -f *~ $(OBJECTS) $(EXEC) $(PHOTOMULTIPLIER_MAP_FILE)

