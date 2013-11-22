#ifndef _JPET_CMD_PARSER_H_
#define _JPET_CMD_PARSER_H_

class JPetCmdParser;

#ifndef __CINT__
#include <boost/program_options.hpp> // Library parsing command line arguments
#include <string>

namespace po = boost::program_options;
using namespace std;

class JPetCmdParser {
public:
	JPetCmdParser();
    void parse(int argc, char** argv);
    const string& getFileName() { return fVariablesMap["file"].as<string>();}
	int getLowerEventBound() { return fVariablesMap["range"].as< vector<int> >()[0];}
    int getHigherEventBound() { return fVariablesMap["range"].as< vector<int> >()[1];}
    
private:
	po::options_description fOptDescriptions;
	po::variables_map fVariablesMap;

};

#endif /* __CINT__ */
#endif /* _JPET_CMD_PARSER_H_ */