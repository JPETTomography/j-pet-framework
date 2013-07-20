CC    = g++
LD    = g++
COPTS    = `root-config --cflags` -I/usr/local/root/include -g
#COPTS    = `root-config --cflags` -I/home/silarski/root/include -g
LDOPTS    = `root-config --libs` -g
#C++ Files
SOURCES =  main.cpp  Dict.cpp Event.cpp TDCHit.cpp ADCHit.cpp Sig.cpp JPetLogger.cpp
OBJECTS = $(SOURCES:.cpp=.o)
#Dictionary classes
HEADERS = Event.h TDCHit.h ADCHit.h Sig.h JPetLogger.h JPetLoggerInclude.h linkdef.h 
EXECUTABLE=main
all: $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(LD) -o $@ $^ $(LDOPTS)
#C++ files
.cpp.o:
	$(CC) -o $@ $^ -c $(COPTS)
#Dictionary for ROOT classes
Dict.cpp: $(HEADERS)
	@echo "Generating dictionary ..."
	@rootcint -f  Dict.cpp -c -P -I$ROOTSYS  $(HEADERS)
clean:;         @rm -f $(OBJECTS)  $(EXECUTABLE) *.o *.d Dict.cpp Dict.h