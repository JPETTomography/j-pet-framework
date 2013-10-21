CC    = g++
LD    = g++
COPTS    = `root-config --cflags` 
LDOPTS    = `root-config --glibs` -g
################
SRC_DIR = $(PWD)/framework
MODULES = DummyClass JPetLogger JPetManager JPetReader JPetAnalysisModule JPetSignal JPetSigCh JPetTSlot  JPetTSlotUnpReader JPetHit JPetEvent JPetPhysSigReader JPetPhysSigWriter JPetTSlotRawReader
SRC_MODULES = $(foreach MODULE, $(MODULES), $(SRC_DIR)/$(MODULE)/$(MODULE).cpp) 
SRC_HEADERS = $(SRC_MODULES:.cpp=.h)
################
#C++ Files
SOURCES =  main.cpp  Dict.cpp Event.cpp TDCHit.cpp ADCHit.cpp Sig.cpp
SOURCES += $(SRC_MODULES)
HEADERS = Event.h TDCHit.h ADCHit.h Sig.h JPetLoggerInclude.h
HEADERS += $(SRC_HEADERS)
HEADERS += linkdef.h
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main
all: modules $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(LD) -o $@ $^ $(LDOPTS)
#C++ files
.cpp.o:
	$(CC) -o $@ $^ -c $(COPTS)
#Dictionary for ROOT classes
Dict.cpp: 
	@echo "Generating dictionary ..."
	@rootcint -f  Dict.cpp -c -P -I$(ROOTSYS) $(HEADERS)
modules:
	@($(foreach MODULE, $(MODULES), cd $(SRC_DIR)/$(MODULE);$(MAKE);))
clean:         
	@rm -f $(OBJECTS)  $(EXECUTABLE) *.o *.d Dict.cpp Dict.h
	@($(foreach MODULE, $(MODULES), cd $(SRC_DIR)/$(MODULE);$(MAKE) clean;))
documentation:
	doxygen Doxyfile
