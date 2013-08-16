CC    = g++
LD    = g++
COPTS    = `root-config --cflags`
LDOPTS    = `root-config --glibs` -g
#C++ Files
SOURCES =  JPetBarrelSlot.cpp 
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS += Dict.o
HEADERS = $(SOURCES:.cpp=.h) 

%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS)
all: $(OBJECTS)
Dict.cpp: 
	@echo "Generating dictionary ..."
	@rootcint -f  Dict.cpp -c -P -I$(ROOTSYS) $(HEADERS)
clean:
	rm -f $(OBJECTS)
