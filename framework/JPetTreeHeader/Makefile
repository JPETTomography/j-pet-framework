CC            =  g++
LD            =  g++
COPTS         =  `root-config --cflags` -fPIC
LDOPTS        =  `root-config --glibs`
#C++ Files
SOURCES       =  JPetTreeHeader.cpp JPetTSlotRawHeader.cpp
OBJECTS       =  $(SOURCES:.cpp=.o)
DICT_OBJECTS  =  $(SOURCES:.cpp=Dict.cpp)
OBJECTS      +=  $(SOURCES:.cpp=Dict.o)
HEADERS       =  $(SOURCES:.cpp=.h) 


%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS)
all: $(DICT_OBJECTS) $(OBJECTS) sharedlib

sharedlib: $(OBJECTS)
	$(LD) -shared -o libJPetTreeHeader.so  JPetTreeHeader.o JPetTSlotRawHeader.o JPetTSlotRawHeaderDict.o $(LDOPTS)

#
# Important to use the ACLIC compilation for JPetTslotRawHeader:
# JPetTslotRawHeader.h+
# due to some ROOT idiosyncracy
# see http://root.cern.ch/phpBB3/viewtopic.php?f=3&t=4817
#
HEADERS_DICT =  $(HEADERS:.h=.h+) 
%Dict.cpp:
	@echo "Generating dictionary ..."
	@rootcint -f $@ -c -P -I$(ROOTSYS) JPetTSlotRawHeader.h linkdef.h
clean:
	rm -f $(OBJECTS) *Dict*
