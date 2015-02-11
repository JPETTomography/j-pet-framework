###################
#THIS PART CAN BE MODIFIED
PROJECT=JPetBarrelSlot
EXTRA_MODULES =
#classes that need Dictionnaries 
DICTS =JPetBarrelSlot
PQXX_LIB_SET = 
DBHANDLER_LIB_SET = 
UNPACKER_LIB_SET = 
###################
OS = $(shell uname)
CO = g++
CFLAGS = -Wall `root-config --cflags`
###################
LDFLAGS = -Wall `root-config --glibs --ldflags` 
LD_BOOST_FLAGS =  -lboost_unit_test_framework -lboost_filesystem -lboost_system -lboost_program_options
LDFLAGS += ${LD_BOOST_FLAGS}
###################
TEST_EXEC = $(PROJECT)Test.exe 
SRC_DIR = $(PWD)/../..
SRC_MODULE =  $(SRC_DIR)/$(PROJECT)/$(PROJECT).cpp 
OBJ_MODULE = $(SRC_MODULE:.cpp=.o) 
SRC_EXTRA = $(foreach MODULE, $(EXTRA_MODULES), $(SRC_DIR)/$(MODULE)/$(MODULE).cpp) 
OBJ_EXTRA= $(SRC_EXTRA:.cpp=.o) 
OBJ_ALL = $(OBJ_MODULE)
OBJ_ALL += $(OBJ_EXTRA)
###################
#ROOT DICTIONNARIES
OBJ_DICT =$(foreach DICT, $(DICTS), $(SRC_DIR)/$(DICT)/$(DICT)Dict.o) 
OBJ_ALL += $(OBJ_DICT)
###################
LOG = JPet.log
###################
ifeq (${PQXX_LIB_SET}, YES)
 LD_PQXX_FLAGS = -lpqxx -lpq
 LDFLAGS += ${LD_PQXX_FLAGS}
endif
###################
ifeq ($(DBHANDLER_LIB_SET), YES)
 LIBDBHANDLER = $(SRC_DIR)/DBHandler/libdbhandler.so
 LDFLAGS += ${LIBDBHANDLER}
endif
###################
ifeq ($(UNPACKER_LIB_SET), YES)
 UNPACKER_DIR = $(PWD)/../../JPetUnpacker
 OBJ_ALL += $(UNPACKER_DIR)/libUnpacker2.so
 ifeq ($(OS),Darwin)
   LDFLAGS += -rpath @loader_path/$(UNPACKER_DIR)
 endif
endif
%.o: %.cpp
	$(CO) -o $@ $(CFLAGS) -c $<
%.exe: %.o
	$(CO) -o $@ $< $(OBJ_ALL) $(LDFLAGS) 

###################
%Test.o: %Test.cpp
%Test.exe: %Test.o
###################
all: $(TEST_EXEC) 
clean:
	rm -f *.exe *.o $(LOG) 
