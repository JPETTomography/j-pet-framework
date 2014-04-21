###################
#
# Makefile for DBHadler code
#
###################
CC=g++
CFLAGS=-I/usr/local/include/ -std=c++0x -lconfig++ -Wall -lpqxx -lpq
LDFLAGS=
HDR_DIR = ../HeaderFiles
SRC_DIR = ../SourceFiles
HPP_FILES=SerializableMap
CPP_FILES=Functions RunData DBHandler PhotoMultiplierMap RunDataMap TRBThresholdMap PhotoMultiplierIdMap TOMBInputMap PassedInformationMap ParamServer ParamData Main
HPP_MODULES=$(foreach dir, $(HPP_FILES), $(HDR_DIR)/$(dir).hpp)
CPP_MODULES=$(foreach dir, $(CPP_FILES), $(SRC_DIR)/$(dir).cpp)
EXEC=dbhandler
###################
PHOTOMULTIPLIER_MAP_FILE=PhotoMultiplierMap.txt
###################
all:
	$(CC) $(HPP_MODULES) $(CPP_MODULES) $(CFLAGS) -o $(EXEC)
run:
	./$(EXEC)
start:
	clear && $(CC) $(HPP_MODULES) $(CPP_MODULES) $(CFLAGS) -o $(EXEC) && ./$(EXEC)
#documentation:
#	doxygen Doxyfile
clean:
	rm -f *~ *.o $(EXEC) $(PHOTOMULTIPLIER_MAP_FILE) 
###################
# Old makefile
#all:
#	g++ ../SourceFiles/RunData.cpp ../SourceFiles/DBHandler.cpp ../SourceFiles/ParamServer.cpp ../SourceFiles/ParamData.cpp ../SourceFiles/Functions.cpp ../SourceFiles/Main.cpp -I/usr/local/include/ -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main
###################
