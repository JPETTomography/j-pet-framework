CO = g++
CFLAGS = -Wall `root-config --cflags`
LD_BOOST_FLAGS =  -lboost_unit_test_framework -lboost_filesystem -lboost_system -lboost_program_options
LDFLAGS = -Wall `root-config --glibs --ldflags`
LDFLAGS += ${LD_BOOST_FLAGS}
###################
TEST_MODULES = DummyClass JPetManager JPetSigCh JPetTSlot JPetHit JPetEvent JPetReader JPetPM JPetScin JPetTRB JPetBarrelSlot JPetHLDReader JPetParamManager JPetCmdParser
TESTS = $(TEST_MODULES:=Test.exe) 
###################
SRC_DIR = ..
SRC_MODULES = $(foreach TEST_MODULES, $(TEST_MODULES), $(SRC_DIR)/$(TEST_MODULES)/$(TEST_MODULES).cpp) 
SRC_OBJS = $(SRC_MODULES:.cpp=.o) 
###################
##### Additional modules not tested so far
ADD_MODULE = JPetAnalysisModule JPetWriter JPetSignal JPetUnpacker JPetLogger
SRC_ADD = $(foreach ADD_MODULE, $(ADD_MODULE), $(SRC_DIR)/$(ADD_MODULE)/$(ADD_MODULE).cpp) 
ADD_OBJS = $(SRC_ADD:.cpp=.o) 
SRC_OBJS += $(ADD_OBJS)
###################
DICT_OBJS = ../JPetAnalysisModule/JPetAnalysisModuleDict.o ../JPetBarrelSlot/JPetBarrelSlotDict.o ../JPetEvent/JPetEventDict.o ../JPetHit/JPetHitDict.o ../JPetManager/JPetManagerDict.o ../JPetPM/JPetPMDict.o ../JPetScin/JPetScinDict.o ../JPetSigCh/JPetSigChDict.o ../JPetSignal/JPetSignalDict.o ../JPetTRB/JPetTRBDict.o ../JPetTSlot/JPetTSlotDict.o  ../JPetUnpacker/JPetUnpackerDict.o 
SRC_OBJS += $(DICT_OBJS) ../JPetUnpacker/libUnpacker2.so
###################
LOG = JPet.log
###################
%.o: %.cpp
	$(CO) -o $@ $(CFLAGS) -c $<
%.exe: %.o
	$(CO) -o $@ $< $(SRC_OBJS) $(LDFLAGS) 

###################
%Test.o: %Test.cpp
%Test.exe: %Test.o
###################
all: $(TESTS)
clean:
	rm -f *.exe *.o $(LOG) 
