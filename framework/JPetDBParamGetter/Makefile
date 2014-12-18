CC            =  g++
LD            =  g++
COPTS         =  `root-config --cflags` -fPIC -O2
LDOPTS        =  `root-config --glibs` -g
CFLAGS        =  -std=c++0x
SOURCES       =  JPetDBParamGetter.cpp
OBJECTS       =  $(SOURCES:.cpp=.o)
HEADERS       =  $(SOURCES:.cpp=.h) 

%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS) $(CFLAGS)
all:  $(OBJECTS)
clean:
	rm -f $(OBJECTS) *Dict*
