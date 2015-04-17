CC = g++
LD = $(CC)
#######################
COPTS = -Wall -fPIC `root-config --cflags` -std=c++0x -O2
LDOPTS = -Wall `root-config --glibs` -lboost_program_options -lboost_system -lboost_regex -lboost_filesystem
#######################
SOURCES       =  JPetScopeReader.cpp
OBJECTS       =  $(SOURCES:.cpp=.o)
HEADERS       =  $(SOURCES:.cpp=.h) 
#LINKDEF       =  $(SOURCES:.cpp=LinkDef.h) 


%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS)
all: $(OBJECTS)
clean:
	rm -f $(OBJECTS)
