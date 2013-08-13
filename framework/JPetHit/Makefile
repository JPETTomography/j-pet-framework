CC    = g++
LD    = g++
COPTS    = `root-config --cflags`
#C++ Files
SOURCES =  JPetHit.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = $(SOURCES:.cpp=.h) 

%.o: %.cc
	$(CC) $^ -o $@  -c $(COPTS)
all: $(OBJECTS) 
clean:
	@rm -f $(OBJECTS)
