CC            =  g++
LD            =  g++
COPTS         =  `root-config --cflags`
LDOPTS        =  -Wl,--no-as-needed `root-config --glibs` -g

CLASSES       =  ParamClass EventClass
OBJECTS       =  $(CLASSES:=.o)
HEADERS       =  $(CLASSES:=.h)

EXECUTABLE    =  run.x

%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS)

all: Dict.o $(OBJECTS)
	cd ./test1/; make;
	cd ./test2/; make;
	cd ./test3/; make;
	cd ./test4/; make;
	cd ./test5/; make;
	cd ./test6/; make;
	cd ./test7/; make;
	cd ./test8/; make;
	cd ./test9/; make;

Dict.cpp:
	@echo "Generating dictionary ..."
	@rootcint -f $@ -c -P -I$(ROOTSYS) $(HEADERS) TestLinkDef.h

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) *Dict*
	cd ./test1/; make clean;
	cd ./test2/; make clean;
	cd ./test3/; make clean;
	cd ./test4/; make clean;
	cd ./test5/; make clean;
	cd ./test6/; make clean;
	cd ./test7/; make clean;
	cd ./test8/; make clean;
	cd ./test9/; make clean;
