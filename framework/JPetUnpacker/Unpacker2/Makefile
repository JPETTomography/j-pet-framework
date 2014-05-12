#Wojciech :Krzemien 13.02.2006
#Makefile for DriftChamber simulation
# 
# make run, make clean, make tar
#===============================================================================
DIR=Unpacker2
###################
ARCH         := $(shell root-config --arch)
PLATFORM      = $(ARCH)
###################
NAME1 = Unpacker2
NAME2 = Event
NAME3 = UnpackingModule
NAME5 = Unpacker_HPTDC_HR
NAME6 = Unpacker_HPTDC_VHR
NAME7 = mydict
NAME8 = TDCHit
NAME9 = ADCHit
NAME10 = Unpacker_HUB2
NAME11 = Unpacker_TRB2
NAME12 = Unpacker_Shower
NAME13 = Unpacker_Ecal_ADC
NAME14 = Unpacker_TRB3
NAME15 = Unpacker_Lattice_TDC
###################
LINKDEF = wkLinkDef.h
###################
EXEC1 = myroot.x
###################
OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS5 = $(NAME5).o
OBJS6 = $(NAME6).o
OBJS7 = $(NAME7).o
OBJS8 = $(NAME8).o
OBJS9 = $(NAME9).o
OBJS10 = $(NAME10).o
OBJS11 = $(NAME11).o
OBJS12 = $(NAME12).o
OBJS13 = $(NAME13).o
OBJS14 = $(NAME14).o
OBJS15 = $(NAME15).o
###################
HEADS1 = $(NAME1).h 
HEADS2 = $(NAME2).h 
HEADS3 = $(NAME3).h 
HEADS5 = $(NAME5).h 
HEADS6 = $(NAME6).h 
HEADS7 = $(NAME7).h 
HEADS8 = $(NAME8).h
HEADS9 = $(NAME9).h
HEADS10 = $(NAME10).h
HEADS11 = $(NAME11).h
HEADS12 = $(NAME12).h
HEADS13 = $(NAME13).h
HEADS14 = $(NAME14).h
HEADS15 = $(NAME15).h
# ###################
LIB_SHARED = lib$(NAME1).so
###################
ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)
###################
CFLAGS = -O -Wall -g -fPIC 
LDFLAGS=-O
###################
CFLAGS     += $(ROOTCFLAGS)
LIBS          = $(ROOTLIBS) $(SYSLIBS) ./tinyxml2-master/tinyxml2.a
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)
###################
CO = g++
LD = $(CO)
###################
%.o: %.cc %.h
	$(CO) $(CFLAGS) -c $<
%.o: %.cc
	$(CO) $(CFLAGS) -c $<
###################
$(LIB_SHARED): $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS5) $(OBJS6) $(OBJS8) $(OBJS9) $(OBJS10) $(OBJS11) $(OBJS12) $(OBJS13) $(OBJS14) $(OBJS15)  $(OBJS7)
	$(LD) -shared -o $@ $(LDFLAGS) $^ $(LIBS) $(GLIBS) 
###################
run: $(EXEC1)
	./$(EXEC1)
###################
clean:
	rm -f *.o *.x core core* a.out *.so mydict.*
###################
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR) )
###################
$(NAME7).cc:$(HEADS1) $(HEADS2) $(HEADS3) $(HEADS5) $(HEADS6) $(HEADS8) $(HEADS9) $(HEADS10) $(HEADS11) $(HEADS12) $(HEADS13) $(HEADS14) $(HEADS15)  $(LINKDEF)
	@echo "Generation dictrionary..."
	@rootcint -f $(NAME7).cc -c -p $(HEADS1) $(HEADS2) $(HEADS3) $(HEADS5) $(HEADS6) $(HEADS8) $(HEADS9) $(HEADS10) $(HEADS11) $(HEADS12) $(HEADS13) $(HEADS14) $(HEADS15)  $(LINKDEF)
###################
