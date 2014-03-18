#
# Makefile for DBHadler code
#

all:
	g++ ../SourceFiles/RunData.cpp ../SourceFiles/DBHandler.cpp ../SourceFiles/ParamServer.cpp ../SourceFiles/Functions.cpp ../SourceFiles/Main.cpp -I/usr/local/include/ -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main
clean:
	rm -f *.cpp~ && rm -f *~ && rm -f main
