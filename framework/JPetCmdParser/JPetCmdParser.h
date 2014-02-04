#ifndef _JPET_CMD_PARSER_H_
#define _JPET_CMD_PARSER_H_

class JPetCmdParser;

#ifndef __CINT__
#include "boost/program_options.hpp" // Library parsing command line arguments
#include <string>

namespace po = boost::program_options;

class JPetCmdParser {
public:
    JPetCmdParser();
    void parse(int argc, char** argv);
    const std::string& getFileName() { return fVariablesMap["file"].as<std::string>();}
	/**
     * @brief Method returning lower bound of events to process or -1 if they were not specified.
     */
    int getLowerEventBound() {return fVariablesMap["range"].as< std::vector<int> >()[0];}
    /**
     * @brief Method returning higher bound of events to process or -1 if they were not specified.
     */
    int getHigherEventBound() {return fVariablesMap["range"].as< std::vector<int> >()[1];}
    bool paramIsSet() { return (bool)fVariablesMap.count("param"); }
    const std::string& getParam() {return fVariablesMap["param"].as< std::string >(); }
    
private:
	po::options_description fOptDescriptions;
	po::variables_map fVariablesMap;

};

#endif /* __CINT__ */
#endif /* _JPET_CMD_PARSER_H_ */
