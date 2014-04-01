CC =  g++
LD = $(CC) 
COPTS =  `root-config --cflags` -fPIC
LDOPTS =  `root-config --glibs`
DEBUG = -g
LD_BOOST_FLAGS =  -lboost_filesystem -lboost_system  
LDOPTS	+= $(LD_BOOST_FLAGS)
LDOPTS	+= $(DEBUG)
#C++ Files
SOURCES       =  JPetUnpacker.cpp
OBJECTS       =  $(SOURCES:.cpp=.o)
DICT_OBJECTS  =  $(SOURCES:.cpp=Dict.cpp)
OBJECTS      +=  $(SOURCES:.cpp=Dict.o)
HEADERS       =  $(SOURCES:.cpp=.h) 

%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS)
all: Unpacker $(OBJECTS) $(DICT_OBJECTS)
Unpacker:
	@(cd ./Unpacker2/tinyxml2-master/; g++ -c -fPIC tinyxml2.cpp; ar rvs tinyxml2.a tinyxml2.o)
	@(cd ./Unpacker2/; $(MAKE))
	@(mv ./Unpacker2/libUnpacker2.so .)
	@(cp ./Unpacker2/conf.xml .)
%Dict.cpp:
	@echo "Generating dictionary ..."
	@rootcint -f $@ -c -P -I$(ROOTSYS) $(HEADERS)
clean:
	@(cd ./Unpacker2/tinyxml2-master/; rm -f *.a *.o)
	@(cd ./Unpacker2/; $(MAKE) clean)
	rm -f $(OBJECTS) *Dict* libUnpacker2.so 
