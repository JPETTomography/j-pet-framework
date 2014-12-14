CC            =  g++
LD            =  g++
COPTS         =  `root-config --cflags` -fPIC -std=c++0x -O2
LDOPTS        =  `root-config --glibs` -g
#C++ Files
SOURCES       =  JPetScopeReader.cpp
OBJECTS       =  $(SOURCES:.cpp=.o)
HEADERS       =  $(SOURCES:.cpp=.h) 

%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS)
all: $(OBJECTS)
clean:
	rm -f $(OBJECTS) *Dict*
