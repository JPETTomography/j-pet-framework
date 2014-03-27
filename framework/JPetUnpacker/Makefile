CC            =  g++
LD            =  g++
COPTS         =  `root-config --cflags` -fPIC
LDOPTS        =  `root-config --glibs` -g
#C++ Files
SOURCES       =  JPetUnpacker.cpp
OBJECTS       =  $(SOURCES:.cpp=.o)
DICT_OBJECTS  =  $(SOURCES:.cpp=Dict.cpp)
OBJECTS      +=  $(SOURCES:.cpp=Dict.o)
HEADERS       =  $(SOURCES:.cpp=.h) 

%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS)
all: Unpacker $(DICT_OBJECTS) $(OBJECTS)
Unpacker:
	@(cd ./Unpacker2/tinyxml2-master/; g++ -c -fPIC tinyxml2.cpp; ar rvs tinyxml2.a tinyxml2.o)
	@(cd ./Unpacker2/; $(MAKE))
	@(mv ./Unpacker2/libUnpacker2.so .)
%Dict.cpp:
	@echo "Generating dictionary ..."
	@rootcint -f $@ -c -P -I$(ROOTSYS) $(HEADERS)
clean:
	@(cd ./Unpacker2/tinyxml2-master/; rm *.a *.o)
	@(cd ./Unpacker2/; $(MAKE) clean)
	rm -f $(OBJECTS) *Dict*
