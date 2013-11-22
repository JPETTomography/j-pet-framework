#ifndef _JPET_CMD_PARSER_H_
#define _JPET_CMD_PARSER_H_

#include <boost/program_options.hpp>
#include <string>

namespace po = boost::program_options;
using namespace std;

class JPetCmdParser {
public:
	JPetCmdParser(int argc, char** argv);
	
private:
	po::options_description fOptDescriptions;
	po::variables_map fVariablesMap;
};

#endif