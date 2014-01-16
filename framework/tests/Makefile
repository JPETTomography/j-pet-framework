###################
BOOST_SYS =/home/${USER}/boost_1_49_0
BOOST_LIB=${BOOST_SYS}/lib
BOOST_INC=${BOOST_SYS}/include
###################
CO = g++
CFLAGS = -Wall `root-config --cflags`
CFLAGS += -I${BOOST_INC}
LD_BOOST_FLAGS = -L${BOOST_LIB} -lboost_unit_test_framework -lboost_filesystem -lboost_system -lboost_program_options
LDFLAGS = -Wall `root-config --glibs` -I${BOOST_INC}
LDFLAGS += ${LD_BOOST_FLAGS}
###################
MODULES = DummyClass JPetManager JPetSigCh JPetTSlot JPetHit JPetEvent JPetParamManager JPetReader
# JPetSignal JPetTSlotRawWriter
TESTS = $(MODULES:=Test.exe) 
###################
SRC_DIR = ..
SRC_MODULES = $(foreach MODULE, $(MODULES), $(SRC_DIR)/$(MODULE)/$(MODULE).cpp) 
SRC_OBJS = $(SRC_MODULES:.cpp=.o) ../JPetAnalysisModule/JPetAnalysisModule.o ../JPetLogger/JPetLogger.o ../JPetPM/JPetPM.o ../JPetTRB/JPetTRB.o ../JPetWriter/JPetWriter.o ../JPetSignal/JPetSignal.o
DICT_OBJS = ../JPetAnalysisModule/JPetAnalysisModuleDict.o ../JPetBarrelSlot/JPetBarrelSlotDict.o ../JPetEvent/JPetEventDict.o ../JPetHit/JPetHitDict.o ../JPetManager/JPetManagerDict.o ../JPetPM/JPetPMDict.o ../JPetScin/JPetScinDict.o ../JPetSigCh/JPetSigChDict.o ../JPetSignal/JPetSignalDict.o ../JPetTRB/JPetTRBDict.o ../JPetTSlot/JPetTSlotDict.o ../JPetCmdParser/JPetCmdParser.o
SRC_OBJS += $(DICT_OBJS)
###################
%.o: %.cpp
	$(CO) -o $@ $(CFLAGS)  -c $<
%.exe: %.o
	$(CO)  -o $@ $(LDFLAGS) $< $(SRC_OBJS)

all: $(TESTS)
clean:
	rm -f *.exe 
