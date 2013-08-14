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
MODULES = DummyClass JPetManager JPetSignal JPetSigCh JPetTSlot
TESTS = $(MODULES:=Test.exe) 
###################
SRC_DIR = ..
SRC_MODULES = $(foreach MODULE, $(MODULES), $(SRC_DIR)/$(MODULE)/$(MODULE).cpp) 
SRC_OBJS = $(SRC_MODULES:.cpp=.o) ../JPetLogger/JPetLogger.o ../JPetSigCh/JPetSigCh.o
###################
%.o: %.cpp
	$(CO) -o $@ $(CFLAGS)  -c $<
%.exe: %.o
	$(CO)  -o $@ $(LDFLAGS) $< $(SRC_OBJS)

all: $(TESTS)
clean:
	rm -f *.exe 
