CC    = g++
LD    = $(CC)
COPTS    = `root-config --cflags` -fPIC
LDOPTS    = `root-config --glibs` -g -lboost_program_options
################
UNPACKER_LIB = $(PWD)/framework/JPetUnpacker/libUnpacker2.so
################
SRC_DIR = $(PWD)/framework
#Modules that should have ROOT dictionnaries
DMODULES = JPetAnalysisModule JPetBarrelSlot JPetEvent JPetHit JPetMacroLoader JPetManager JPetPM JPetScin JPetSigCh JPetSignal JPetTRB JPetTSlot JPetUnpacker
DICTS   = $(DMODULES)
READERS = JPetReader JPetHLDReader
WRITERS = JPetWriter
#Modules that without ROOT dictionnaries
NONDMODULES = DummyClass JPetLogger JPetCmdParser JPetParamManager $(READERS) $(WRITERS)
MODULES = $(DMODULES) $(NONDMODULES)
################
SRC_MODULES = $(foreach MODULE, $(MODULES), $(SRC_DIR)/$(MODULE)/$(MODULE).cpp) 
SRC_HEADERS = $(SRC_MODULES:.cpp=.h)
################
TEST_DIR = $(SRC_DIR)/tests
################
#C++ Files
#SOURCES =  Dict.cpp
# Event.cpp TDCHit.cpp ADCHit.cpp Sig.cpp 
#SOURCES += $(SRC_MODULES)
SOURCES = $(SRC_MODULES)
HEADERS = JPetLoggerInclude.h #Event.h TDCHit.h ADCHit.h Sig.h
HEADERS += $(SRC_HEADERS)
HEADERS += linkdef.h
OBJECTS = $(SOURCES:.cpp=.o)
DICT_OBJS = $(foreach DICT, $(DICTS), $(SRC_DIR)/$(DICT)/$(DICT)Dict.o)
################
LIBFRAMEWORK = libJPetFramework.so
################
.cpp.o:
	$(CC) -o $@ $^ -c $(COPTS)
################
all: modules dbhandler
#Dictionary for ROOT classes
Dict.cpp: 
	@echo "Generating dictionary ..."
	@rootcint -f  Dict.cpp -c -P -I$(ROOTSYS) $(HEADERS)
modules:
	@($(foreach MODULE, $(MODULES), cd $(SRC_DIR)/$(MODULE);$(MAKE);))
sharedlib: modules
	$(LD) -shared -o $(LIBFRAMEWORK) $(OBJECTS) $(DICT_OBJS) $(UNPACKER_LIB) $(LDOPTS)
dbhandler:
	cd $(SRC_DIR)/DBHandler; $(MAKE);
documentation:
	doxygen Doxyfile
clean:         
	@rm -rf $(OBJECTS)  $(EXECUTABLE) *.o *.d Dict.cpp Dict.h $(LIBFRAMEWORK) latex html
	@($(foreach MODULE, $(MODULES),$(MAKE) -C $(SRC_DIR)/$(MODULE) clean;))
	$(MAKE) -C $(TEST_DIR) clean
