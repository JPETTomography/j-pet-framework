CC            =  g++
LD            =  g++
COPTS         =  `root-config --cflags` -fPIC
LDOPTS        =  `root-config --glibs` -g
#C++ Files
SOURCES       =  DummyClass.cpp
OBJECTS       =  $(SOURCES:.cpp=.o)
HEADERS       =  $(SOURCES:.cpp=.h) 

%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS)
all: $(OBJECTS)
clean:
	rm -f $(OBJECTS) *Dict*
