###################
BOOST_SYS =/home/${USER}/boost_1_49_0
BOOST_LIB=${BOOST_SYS}/lib
BOOST_INC=${BOOST_SYS}/include
###################
CO = g++
CFLAGS = -Wall `root-config --cflags`
CFLAGS += -I${BOOST_INC}
LD_BOOST_FLAGS = -L${BOOST_LIB} -lboost_unit_test_framework -lboost_filesystem -lboost_system
LDFLAGS = -Wall `root-config --glibs` -I${BOOST_INC}
LDFLAGS += ${LD_BOOST_FLAGS}
###################
MODULES = DummyClass JPetManager JPetSignal JPetSigCh JPetTSlotRawWriter JPetTSlot JPetHit JPetEvent JPetPhysSigReader JPetPhysSigWriter JPetTSlotUnpReader 
TESTS = $(MODULES:=Test.exe) 
###################
SRC_DIR = ..
SRC_MODULES = $(foreach MODULE, $(MODULES), $(SRC_DIR)/$(MODULE)/$(MODULE).cpp) 
<<<<<<< HEAD
SRC_OBJS = $(SRC_MODULES:.cpp=.o) ../JPetLogger/JPetLogger.o ../JPetReader/JPetReader.o ../JPetWriter/JPetWriter.o
DICT_OBJS = ../JPetSigCh/JPetSigChDict.o ../JPetSignal/JPetSignalDict.o ../JPetHit/JPetHitDict.o ../JPetEvent/JPetEventDict.o
SRC_OBJS += $(DICT_OBJS)
=======
SRC_OBJS = $(SRC_MODULES:.cpp=.o) ../JPetLogger/JPetLogger.o  ../JPetReader/JPetReader.o ../JPetWriter/JPetWriter.o ../JPetTSlot/Dict.o
#../JPetSignal/Dict.o
>>>>>>> 79eada6ef598973e7d79f35c7e438b4f0190d1eb
###################
%.o: %.cpp
	$(CO) -o $@ $(CFLAGS)  -c $<
%.exe: %.o
	$(CO)  -o $@ $(LDFLAGS) $< $(SRC_OBJS)

all: $(TESTS)
clean:
	rm -f *.exe 
