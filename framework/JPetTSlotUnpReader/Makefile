CC = g++
COPTS = `root-config --cflags`
#C++ Files
SOURCES = JPetTSlotUnpReader.cpp Event.cpp ADCHit.cpp TDCHit.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = $(SOURCES:.cpp=.h) 

%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS)
all: $(OBJECTS) 
	echo $(OBJECTS)
clean:
	rm -f $(OBJECTS)
