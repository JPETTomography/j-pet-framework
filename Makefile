###################
BOOST_SYS =/home/${USER}/boost_1_49_0
BOOST_LIB=${BOOST_SYS}/lib
BOOST_INC=${BOOST_SYS}/include
###################
CC    = g++
LD    = g++
COPTS    = `root-config --cflags` -I${BOOST_INC}
LDOPTS    = `root-config --glibs` -g -L${BOOST_LIB} -lboost_program_options
################
SRC_DIR = $(PWD)/framework
DMODULES = JPetAnalysisModule JPetBarrelSlot JPetEvent JPetHit JPetManager JPetPM JPetScin JPetSigCh JPetSignal JPetTRB JPetTSlot
DICTS   = $(DMODULES)
READERS = JPetReader
WRITERS = JPetWriter
MODULES = $(DMODULES) DummyClass JPetLogger $(READERS) $(WRITERS)
SRC_MODULES = $(foreach MODULE, $(MODULES), $(SRC_DIR)/$(MODULE)/$(MODULE).cpp) 
SRC_HEADERS = $(SRC_MODULES:.cpp=.h)
################
TEST_DIR = $(SRC_DIR)/tests
################
#C++ Files
SOURCES =  main.cpp  Dict.cpp Event.cpp TDCHit.cpp ADCHit.cpp Sig.cpp framework/JPetCmdParser/JPetCmdParser.cpp
SOURCES += $(SRC_MODULES)
HEADERS = Event.h TDCHit.h ADCHit.h Sig.h JPetLoggerInclude.h
HEADERS += $(SRC_HEADERS)
HEADERS += linkdef.h
OBJECTS = $(SOURCES:.cpp=.o)
DICT_OBJS = $(foreach DICT, $(DICTS), $(SRC_DIR)/$(DICT)/$(DICT)Dict.o)
EXECUTABLE = main
all: modules $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(LD) -o $@ $^ $(LDOPTS) $(DICT_OBJS)
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
	@($(foreach MODULE, $(MODULES),$(MAKE) -C $(SRC_DIR)/$(MODULE) clean;))
	$(MAKE) -C $(TEST_DIR) clean
documentation:
	doxygen Doxyfile
