CC    = g++
LD    = g++
COPTS    = `root-config --cflags` -fPIC
LDOPTS    = `root-config --glibs` -g -lboost_program_options
################
SRC_DIR = $(PWD)/framework
DMODULES = JPetAnalysisModule JPetBarrelSlot JPetEvent JPetHit JPetMacroLoader JPetManager JPetPM JPetScin JPetSigCh JPetSignal JPetTRB JPetTSlot
DICTS   = $(DMODULES)
READERS = JPetReader JPetHLDReader
WRITERS = JPetWriter
MODULES = $(DMODULES) DummyClass JPetLogger JPetCmdParser JPetParamManager $(READERS) $(WRITERS) 
SRC_MODULES = $(foreach MODULE, $(MODULES), $(SRC_DIR)/$(MODULE)/$(MODULE).cpp) 
SRC_HEADERS = $(SRC_MODULES:.cpp=.h)
################
TEST_DIR = $(SRC_DIR)/tests
################
#C++ Files
SOURCES =  Dict.cpp
# Event.cpp TDCHit.cpp ADCHit.cpp Sig.cpp 
SOURCES += $(SRC_MODULES)
HEADERS = JPetLoggerInclude.h #Event.h TDCHit.h ADCHit.h Sig.h
HEADERS += $(SRC_HEADERS)
HEADERS += linkdef.h
OBJECTS = $(SOURCES:.cpp=.o)
DICT_OBJS = $(foreach DICT, $(DICTS), $(SRC_DIR)/$(DICT)/$(DICT)Dict.o)
EXECUTABLE = main
all: modules# $(EXECUTABLE)
#$(EXECUTABLE): $(OBJECTS)
#	$(LD) -o $@ $^ $(LDOPTS) $(DICT_OBJS)
#C++ files
.cpp.o:
	$(CC) -o $@ $^ -c $(COPTS)
#Dictionary for ROOT classes
Dict.cpp: 
	@echo "Generating dictionary ..."
	@rootcint -f  Dict.cpp -c -P -I$(ROOTSYS) $(HEADERS)
modules:
	@($(foreach MODULE, $(MODULES), cd $(SRC_DIR)/$(MODULE);$(MAKE);))
	@(cd $(SRC_DIR)/Unpacker2/; $(MAKE))
documentation:
	doxygen Doxyfile
sharedlib: $(OBJECTS)
	$(LD) -shared -o libJPetFramework.so $^ $(DICT_OBJS) $(LDOPTS)
clean:         
	@rm -rf $(OBJECTS)  $(EXECUTABLE) *.o *.d Dict.cpp Dict.h JPetFramework.so latex html
	@($(foreach MODULE, $(MODULES),$(MAKE) -C $(SRC_DIR)/$(MODULE) clean;))
	$(MAKE) -C $(TEST_DIR) clean
