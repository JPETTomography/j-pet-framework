###################
#THIS PART CAN BE MODIFIED
PROJECT=TRefsTest
EXTRA_MODULE =TestEvent
#classes that need Dictionnaries 
DICT = TestEventDict.cpp
###################
OS = $(shell uname)
CO = g++
CFLAGS = -Wall `root-config --cflags`
###################
LDFLAGS = -Wall -Wl,--no-as-needed `root-config --glibs --ldflags` 
LD_BOOST_FLAGS =  -lboost_unit_test_framework -lboost_filesystem -lboost_system -lboost_program_options
LDFLAGS += ${LD_BOOST_FLAGS}
###################
TEST_EXEC = $(PROJECT).exe 
SRC_MODULES = $(PROJECT).cpp $(EXTRA_MODULE).cpp $(DICT)
OBJ_MODULES = $(SRC_MODULES:.cpp=.o) 
###################
HEADERS = $(EXTRA_MODULE).h
###################
LOG = JPet.log

###################
all: $(OBJ_MODULES) 
	$(CO)  $(OBJ_MODULES)  $(LDFLAGS) -o $(TEST_EXEC)
%.o: %.cpp
	$(CO) -o $@ $(CFLAGS) -c $<

$(DICT):
	@echo "Generating dictionary ..."
	rootcint -f $@ -c -P -I$(ROOTSYS) $(HEADERS) TestEventLinkDef.h
clean:
	rm -f *.exe *.o *Dict* *.root $(LOG) 
