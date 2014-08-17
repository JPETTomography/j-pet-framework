CC            =  g++
LD            =  g++
COPTS         =  `root-config --cflags`
LDOPTS        =  -Wl,--no-as-needed `root-config --glibs` -g
COMMON_OBJS   =  ../Dict.o ../EventClass.o ../ParamClass.o

CLASSES	      =  gen5 read5
OBJECTS       =  $(CLASSES:=.o)
EXECUTABLES   =  $(CLASSES:=.x)

%.o: %.cpp
	$(CC) $^ -o $@  -c $(COPTS)

%.x: %.o
	$(LD) -o $@ $^ $(COMMON_OBJS) $(LDOPTS)

all: $(EXECUTABLES)

clean:
	rm -f $(OBJECTS) $(EXECUTABLES) *.root
