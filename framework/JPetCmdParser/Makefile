CC            =  g++
LD            =  g++
COPTS         =  `root-config --cflags`-lboost_program_options
LDOPTS        =  `root-config --glibs` -g 
#C++ Files
SOURCES       =  JPetCmdParser.cpp
OBJECTS       =  $(SOURCES:.cpp=.o)
#DICT_OBJECTS  =  $(SOURCES:.cpp=Dict.cpp)
#OBJECTS      +=  $(SOURCES:.cpp=Dict.o)
HEADERS       =  $(SOURCES:.cpp=.h)
#HEADERS      +=  /usr/local/include/boost/program_options.hpp

%.o: %.cpp
	$(CC) $^  -o $@  -c $(COPTS)
all: $(DICT_OBJECTS) $(OBJECTS)
#%Dict.cpp:
#	@echo $(HEADERS)
#	@echo "Genarating dictionary ..."
#	@rootcint -f $@ -c -P -I$(ROOTSYS) $(HEADERS)
clean:
	rm -f $(OBJECTS) *Dict*
