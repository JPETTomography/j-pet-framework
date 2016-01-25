###################
#
# Makefile for Unit Tests
#
###################
# uwaga na flage -lconfig++
######################################
all:
	g++ ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../DBHandlerHelper.cpp ../DBHandlerTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main
	
dbHandlerTest:
	g++ ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../DBHandlerHelper.cpp ../DBHandlerTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main
dbHandlerTestLogs:
	g++ ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../DBHandlerHelper.cpp ../DBHandlerTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main --log_level=test_suite

paramServerTest:
	g++ ../../HeaderFiles/SerializableMap.hpp ../../SourceFiles/RunData.cpp ../../SourceFiles/PhotoMultiplierMap.cpp ../../SourceFiles/RunDataMap.cpp ../../SourceFiles/TRBThresholdMap.cpp ../../SourceFiles/PhotoMultiplierIdMap.cpp ../../SourceFiles/TOMBInputMap.cpp ../../SourceFiles/PassedInformationMap.cpp ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../../SourceFiles/ParamServer.cpp ../ParamServerTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main
paramServerTestLogs:
	g++ ../../HeaderFiles/SerializableMap.hpp ../../SourceFiles/RunData.cpp ../../SourceFiles/PhotoMultiplierMap.cpp  ../../SourceFiles/RunDataMap.cpp ../../SourceFiles/TRBThresholdMap.cpp ../../SourceFiles/PhotoMultiplierIdMap.cpp ../../SourceFiles/TOMBInputMap.cpp ../../SourceFiles/PassedInformationMap.cpp ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../../SourceFiles/ParamServer.cpp ../ParamServerTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main --log_level=test_suite
	
paramDataTest:
	g++ ../../HeaderFiles/SerializableMap.hpp ../../SourceFiles/RunData.cpp ../../SourceFiles/PhotoMultiplierMap.cpp ../../SourceFiles/RunDataMap.cpp ../../SourceFiles/TRBThresholdMap.cpp ../../SourceFiles/PhotoMultiplierIdMap.cpp ../../SourceFiles/TOMBInputMap.cpp ../../SourceFiles/PassedInformationMap.cpp ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../../SourceFiles/ParamServer.cpp ../../SourceFiles/ParamData.cpp ../ParamDataTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main
paramDataTestLogs:
	g++ ../../HeaderFiles/SerializableMap.hpp ../../SourceFiles/RunData.cpp ../../SourceFiles/PhotoMultiplierMap.cpp  ../../SourceFiles/RunDataMap.cpp ../../SourceFiles/TRBThresholdMap.cpp ../../SourceFiles/PhotoMultiplierIdMap.cpp ../../SourceFiles/TOMBInputMap.cpp ../../SourceFiles/PassedInformationMap.cpp ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../../SourceFiles/ParamServer.cpp ../../SourceFiles/ParamData.cpp ../ParamDataTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main --log_level=test_suite
	
functionsTest:
	g++ ../../SourceFiles/Functions.cpp ../FunctionsTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main
functionsTestLogs:
	g++ ../../SourceFiles/Functions.cpp ../FunctionsTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main --log_level=test_suite
		
runDataTest:
	g++ ../../SourceFiles/RunData.cpp ../RunDataTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main
runDataTestLogs:	
	g++ ../../SourceFiles/RunData.cpp ../RunDataTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main --log_level=test_suite
###################

photoMultiplierMapTest:
	g++ ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../../HeaderFiles/SerializableMap.hpp ../../SourceFiles/PhotoMultiplierMap.cpp ../PhotoMultiplierMapTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main

runDataMapTest:
	g++ ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../../HeaderFiles/SerializableMap.hpp ../../SourceFiles/RunData.cpp ../../SourceFiles/RunDataMap.cpp ../RunDataMapTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main

TRBThresholdMapTest:
	g++ ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../../HeaderFiles/SerializableMap.hpp ../../SourceFiles/TRBThresholdMap.cpp ../TRBThresholdMapTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main

photoMultiplierIdMapTest:
	g++ ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../../HeaderFiles/SerializableMap.hpp ../../SourceFiles/PhotoMultiplierIdMap.cpp ../PhotoMultiplierIdMapTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main

TOMBInputMapTest:
	g++ ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../../HeaderFiles/SerializableMap.hpp ../../SourceFiles/TOMBInputMap.cpp ../TOMBInputMapTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main

passedInformationMapTest:
	g++ ../../SourceFiles/Functions.cpp ../../SourceFiles/DBHandler.cpp ../../HeaderFiles/SerializableMap.hpp ../../SourceFiles/PassedInformationMap.cpp ../PassedInformationMapTestSuite.cpp -std=c++0x -lconfig++ -Wall -lpqxx -lpq -o main && ./main

###################
runAllTests:
	make dbHandlerTest paramServerTest paramDataTest functionsTest runDataTest photoMultiplierMapTest runDataMapTest TRBThresholdMapTest photoMultiplierIdMapTest TOMBInputMapTest passedInformationMapTest
###################
clean:
	rm -f *.cpp~ && rm -f *~ && rm -f main
###################
