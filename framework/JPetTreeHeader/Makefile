CC            =  g++
LD            =  g++
COPTS         =  `root-config --cflags` -fPIC -O2
LDOPTS        =  `root-config --glibs`
#C++ Files
SOURCES       =  JPetTreeHeader.cpp
OBJECTS       =  $(SOURCES:.cpp=.o)
DICT_OBJECTS  =  $(SOURCES:.cpp=Dict.cpp)
OBJECTS      +=  $(SOURCES:.cpp=Dict.o)
HEADERS       =  $(SOURCES:.cpp=.h) 


%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS)
all: $(DICT_OBJECTS) $(OBJECTS)

# sharedlib: $(OBJECTS)
# 	$(LD) -shared -o libJPetTreeHeader.so  JPetTreeHeader.o JPetTSlotRawHeader.o JPetTSlotRawHeaderDict.o $(LDOPTS)

%Dict.cpp:
	@echo "Generating dictionary ..."
	@rootcint -f $@ -c -P -I$(ROOTSYS) $(HEADERS) linkdef.h
clean:
	rm -f $(OBJECTS) *Dict*
