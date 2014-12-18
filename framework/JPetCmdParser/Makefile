###################
CC            =  g++
LD            =  g++
COPTS         =  `root-config --cflags` -fPIC -O2
LDOPTS        =  `root-config --glibs` -lboost_program_options
#C++ Files
SOURCES       =  JPetCmdParser.cpp
OBJECTS       =  $(SOURCES:.cpp=.o)
#DICT_OBJECTS  =  $(SOURCES:.cpp=Dict.cpp)
#OBJECTS      +=  $(SOURCES:.cpp=Dict.o)
HEADERS       =  $(SOURCES:.cpp=.h)

%.o: %.cpp
	$(CC) $^  -o $@  -c $(COPTS)
all: $(OBJECTS) 
#$(DICT_OBJECTS)
#%Dict.cpp:
#	@echo $(HEADERS)
#	@echo "Generating dictionary ..."
#	@rootcint -f $@ -c -P -I$(ROOTSYS) $(HEADERS)
clean:
	rm -f $(OBJECTS) *Dict*
