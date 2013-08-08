CC    = g++
LD    = g++
COPTS    = `root-config --cflags`
#C++ Files
SOURCES =  JPetSignal.cpp 
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = $(SOURCES:.cpp=.h) 

%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS)
all: $(OBJECTS) 
clean:
	@rm -f $(OBJECTS)
