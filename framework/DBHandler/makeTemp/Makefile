##################
#
# Makefile for DBHadler code
#
###################
CC=g++
CFLAGS= -I/usr/local/include/ -std=c++0x -Wall
LDFLAGS= -lconfig++ -lpqxx -lpq
HDR_DIR = HeaderFiles
SRC_DIR = SourceFiles
CPP_FILES= Functions RunData DBHandler PhotoMultiplierMap RunDataMap TRBThresholdMap PhotoMultiplierIdMap TOMBInputMap PassedInformationMap ParamServer ParamData
CPP_MODULES=$(foreach dir, $(CPP_FILES), $(SRC_DIR)/$(dir).cpp)
OBJECTS=$(foreach dir, $(CPP_FILES), $(SRC_DIR)/$(dir).o)
EXEC=dbhandler
################
LIBFRAMEWORK = libJPetFramework.so
LIB_LDOPTS = $(LDFLAGS)
OSX_LIB_COPTS += -install_name @rpath/$(LIBFRAMEWORK)
OSX_LIB_LDOPTS = -rpath $(UNPACKER_PATH)

LIB_LDOPTS += -L$(UNPACKER_PATH) -l$(UNPACKER_LIB)
###################
%.o: %.cpp
	$(CC) $^ -o $@  -c $(CFLAGS)
###################
PHOTOMULTIPLIER_MAP_FILE=PhotoMultiplierMap.txt
###################
all: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(EXEC)
	
modules:
	@($(foreach MODULE, $(MODULES), cd $(SRC_DIR)/$(MODULE);$(MAKE);))

sharedlib:
	$(LD) -shared -o $(LIBFRAMEWORK) $(OBJECTS) $(LIB_LDOPTS);
ifeq ($(OS), Darwin)
	install_name_tool -id @rpath/$(LIBFRAMEWORK) $(LIBFRAMEWORK)
endif
	
run:
	./$(EXEC)
start:
	clear && $(CC) $(CPP_MODULES) $(CFLAGS) -o $(EXEC) && ./$(EXEC)
#documentation:
#	doxygen Doxyfile
clean:
	rm -f *~ $(OBJECTS) $(EXEC) $(PHOTOMULTIPLIER_MAP_FILE) 
