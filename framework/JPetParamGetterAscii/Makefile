CC            =  g++
LD            =  g++
COPTS         =  $(shell root-config --cflags) -fPIC -O2
LDOPTS        =  $(shell root-config --glibs) -g
CFLAGS        =  -std=c++11
SOURCES       =  JPetParamGetterAscii.cpp JPetParamSaverAscii.cpp
OBJECTS       =  $(SOURCES:.cpp=.o)
HEADERS       =  $(SOURCES:.cpp=.h) 
HEADERS       =  $(HEADERS) JPetParamAsciiConstants.h

%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS) $(CFLAGS)
all:  $(OBJECTS)
clean:
	rm -f $(OBJECTS) *Dict*
