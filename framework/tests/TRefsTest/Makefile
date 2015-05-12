###################
#THIS PART CAN BE MODIFIED
PROJECT= TRefsTest
EXTRA_MODULES =FakeParamBank TestEvent 
#classes that need Dictionnaries 
DICT = TestEventDict.cpp FakeParamBank.cpp
###################
OS = $(shell uname)
CO = g++
CFLAGS = -Wall `root-config --cflags`
###################
LDFLAGS = -Wall  `root-config --glibs --ldflags` 
LD_BOOST_FLAGS =  -lboost_unit_test_framework -lboost_filesystem -lboost_system -lboost_program_options
LDFLAGS += ${LD_BOOST_FLAGS}
###################
TEST_EXEC = $(PROJECT).exe 
SRC_EXTRA_MODULES = $(EXTRA_MODULES:=.cpp)
SRC_MODULES = $(PROJECT).cpp $(SRC_EXTRA_MODULES) 
OBJ_MODULES = $(SRC_MODULES:.cpp=.o) 
OBJ_ALL = $(OBJ_MODULES)
###################
HEADERS = $(EXTRA_MODULES:=.h)  
###################
LOG = JPet.log
###################
OBJ_DICT1 = TestEventDict.o
OBJ_DICT2 = FakeParamBankDict.o
OBJ_ALL += $(OBJ_DICT1)
OBJ_ALL += $(OBJ_DICT2)
###################
TEST_FILE_CREATOR=createTestRootFile.x
OBJ_PART= createTestRootFile.o TestEvent.o FakeParamBank.o
OBJ_PART += $(OBJ_DICT1)
OBJ_PART += $(OBJ_DICT2)
###################
%.o: %.cpp
	$(CO) -o $@ $(CFLAGS) -c $< 
%.exe:$(OBJ_ALL)
	$(CO) -o $@  $(OBJ_ALL) $(LDFLAGS) 
%.x:$(OBJ_PART)
	$(CO) -o $@  $(OBJ_PART) $(LDFLAGS) 

all: $(TEST_FILE_CREATOR) $(TEST_EXEC) 
	./$(TEST_FILE_CREATOR)
TestEventDict.cpp:
	echo "Generating dictionary ..."
	rootcint -f $@ -c -P -I$(ROOTSYS) TestEvent.h TestEventLinkDef.h
FakeParamBankDict.cpp:
	echo "Generating dictionary ..."
	rootcint -f $@ -c -P -I$(ROOTSYS) FakeParamBank.h FakeParamBankLinkDef.h
clean:
	rm -f *.exe *.o *Dict* *.root $(LOG) *.x
