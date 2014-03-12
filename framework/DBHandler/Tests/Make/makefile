#
# Makefile for Unit Tests
#

# uwaga na flage -lconfig++

all:
	g++ ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../DBHandlerHelper.cpp ../DBHandlerTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main
dbHandlerTest:
	g++ ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../DBHandlerHelper.cpp ../DBHandlerTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main
dbHandlerTestLogs:
	g++ ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../DBHandlerHelper.cpp ../DBHandlerTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main --log_level=test_suite
paramServerTest:
	g++ ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../../SourceFiles/ParamServer.cpp ../DBHandlerHelper.cpp ../ParamServerTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main
paramServerTestLogs:
	g++ ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../../SourceFiles/ParamServer.cpp ../DBHandlerHelper.cpp ../ParamServerTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main --log_level=test_suite
functionsTest:
	g++ ../../SourceFiles/Functions.cpp ../FunctionsTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main
functionsTestLogs:
	g++ ../../SourceFiles/Functions.cpp ../FunctionsTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main --log_level=test_suite	

runAllTests:
	make dbHandlerTest paramServerTest functionsTest

clean:
	rm -f *.cpp~ && rm -f *~ && rm -f main
