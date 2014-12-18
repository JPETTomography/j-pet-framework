CC    = g++
LD    = g++
COPTS    = `root-config --cflags` -fPIC -O2
LDOPTS    = `root-config --glibs` -g
#C++ Files
SOURCES =  JPetWriter.cpp 
OBJECTS       =  $(SOURCES:.cpp=.o)
#DICT_OBJECTS  =  $(SOURCES:.cpp=Dict.cpp)
#OBJECTS      +=  $(SOURCES:.cpp=Dict.o)
HEADERS       =  $(SOURCES:.cpp=.h) 
#LINKDEF       =  $(SOURCES:.cpp=LinkDef.h) 


%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS)
all: $(DICT_OBJECTS) $(OBJECTS)
#%Dict.cpp:
#	@echo "Generating dictionary ..."
#	rootcint -f $@ -c -P -I$(ROOTSYS) $(HEADERS) $(LINKDEF)
clean:
	rm -f $(OBJECTS) *Dict*
