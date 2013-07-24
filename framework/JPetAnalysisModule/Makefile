CC    = g++
LD    = g++
COPTS    = `root-config --cflags`
LDOPTS    = `root-config --glibs` -g
#C++ Files
SOURCES =  JPetAnalysisModule.cpp 
OBJECTS = $(SOURCES:.cpp=.o)
#Dictionary classes
HEADERS = $(SOURCES:.cpp=.h) 

%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS)
all: $(OBJECTS) 
clean:
	rm -f $(OBJECTS)
