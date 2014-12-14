CC = g++
LD = $(CC)
#######################
COPTS = -Wall -fPIC `root-config --cflags` -std=c++0x -O2
LDOPTS = -Wall `root-config --glibs` -lboost_program_options -lboost_system -lboost_regex -lboost_filesystem
#######################
SOURCES       =  JPetScopeModule.cpp
OBJECTS       =  $(SOURCES:.cpp=.o)
DICT_OBJECTS  =  $(SOURCES:.cpp=Dict.cpp)
OBJECTS      +=  $(SOURCES:.cpp=Dict.o)
HEADERS       =  $(SOURCES:.cpp=.h)

%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS)
all: $(DICT_OBJECTS) $(OBJECTS)
%Dict.cpp:
	@echo "Generating dictionary ..."
	@rootcint -f $@ -c -P -I$(ROOTSYS) $(HEADERS)
clean:
	rm -f $(OBJECTS) *Dict*
