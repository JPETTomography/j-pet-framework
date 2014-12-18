CC            =  g++
LD            =  g++
COPTS         =  -Wall `root-config --cflags` -fPIC -O2
LDOPTS        =  -Wall `root-config --glibs` -g
#C++ Files
SOURCES       =  JPetTRB.cpp
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
