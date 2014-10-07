OS = $(shell uname)
CC    = g++
LD    = $(CC)
COPTS    = `root-config --cflags` -fPIC
LDOPTS    = `root-config --glibs`
DEBUG = -g
LD_BOOST_FLAGS = -lboost_program_options -lboost_filesystem -lboost_system  
LDOPTS	+= $(LD_BOOST_FLAGS)
LDOPTS	+= $(DEBUG)
################
UNPACKER_PATH = $(PWD)/framework/JPetUnpacker/
UNPACKER_LIB = Unpacker2
################
SRC_DIR = $(PWD)/framework
#Modules that should have ROOT dictionnaries
DMODULES = JPetAnalysisModule JPetBarrelSlot JPetEvent JPetHit JPetMacroLoader JPetPM JPetScin JPetSigCh JPetSignal JPetTRB JPetTSlot JPetUnpacker JPetFrame JPetFEB JPetLayer JPetSetup JPetSlot JPetTOMB JPetUser JPetTreeHeader JPetParamBank
DICTS   = $(DMODULES)
READERS = JPetReader JPetHLDReader
WRITERS = JPetWriter
#Modules that without ROOT dictionnaries
NONDMODULES = DummyClass JPetLogger JPetCmdParser JPetParamManager JPetManager $(READERS) $(WRITERS)
MODULES = $(DMODULES) $(NONDMODULES)
################
SRC_MODULES = $(foreach MODULE, $(MODULES), $(SRC_DIR)/$(MODULE)/$(MODULE).cpp) 
SRC_HEADERS = $(SRC_MODULES:.cpp=.h)
################
TEST_DIR = $(SRC_DIR)/tests
################
WORK_DIR = workdir/FrameworkExamples
EXAMPLE_DIRS = $(sort $(dir $(wildcard $(WORK_DIR)/*/)))
################
SOURCES = $(SRC_MODULES)
HEADERS = JPetLoggerInclude.h #Event.h TDCHit.h ADCHit.h Sig.h
HEADERS += $(SRC_HEADERS)
HEADERS += linkdef.h
OBJECTS = $(SOURCES:.cpp=.o)
DICT_OBJS = $(foreach DICT, $(DICTS), $(SRC_DIR)/$(DICT)/$(DICT)Dict.o)
################
LIBFRAMEWORK = libJPetFramework.so
LIB_LDOPTS = $(LDOPTS)
OSX_LIB_COPTS += -install_name @rpath/$(LIBFRAMEWORK)
OSX_LIB_LDOPTS = -rpath $(UNPACKER_PATH)
LINUX_LIB_LDOPTS = -Wl,-rpath=$(UNPACKER_PATH)
ifeq ($(OS), Darwin)
	LIB_LDOPTS += $(OSX_LIB_LDOPTS)
else
	LIB_LDOPTS += $(LINUX_LIB_LDOPTS)
endif
LIB_LDOPTS += -L$(UNPACKER_PATH) -l$(UNPACKER_LIB)
################
.cpp.o:
	$(CC) -o $@ $^ -c $(COPTS)
################
all: modules dbhandler
#Dictionary for ROOT classes
Dict.cpp: 
	@echo "Generating dictionary ..."
	@rootcint -f  Dict.cpp -c -P -I$(ROOTSYS) $(HEADERS)
modules:
	@($(foreach MODULE, $(MODULES), cd $(SRC_DIR)/$(MODULE);$(MAKE)||exit $$?;))
sharedlib: modules
	$(LD) -shared -o $(LIBFRAMEWORK) $(OBJECTS) $(DICT_OBJS) $(LIB_LDOPTS);
ifeq ($(OS), Darwin)
	install_name_tool -id @rpath/$(LIBFRAMEWORK) $(LIBFRAMEWORK)
endif
dbhandler:
	cd $(SRC_DIR)/DBHandler; $(MAKE) sharedlib;
################
tests: modules
	cd $(TEST_DIR); $(MAKE)
tests_run: tests
	cd $(TEST_DIR); ./run_tests.pl 
################
documentation:
	doxygen Doxyfile
clean:         
	@rm -rf $(OBJECTS)  $(EXECUTABLE) *.o *.d Dict.cpp Dict.h $(LIBFRAMEWORK) latex html
	@($(foreach MODULE, $(MODULES),$(MAKE) -C $(SRC_DIR)/$(MODULE) clean;))
	@($(foreach EXAMPLE, $(EXAMPLE_DIRS), $(MAKE) -C $(EXAMPLE) clean;))
	$(MAKE) -C $(SRC_DIR)/DBHandler clean
	$(MAKE) -C $(TEST_DIR) clean
	$(MAKE) -C $(SRC_DIR)/tests clean

