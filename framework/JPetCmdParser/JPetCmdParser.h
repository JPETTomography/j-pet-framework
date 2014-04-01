/**
 *  @copyright Copyright (c) 2014, J-PET collaboration
 *  @file JPetCmdParser.h
 *  @author Karol Stola
 *  @brief 
 */

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
    inline const std::string& getFileName() const { return fVariablesMap["file"].as<std::string>();}
    inline const std::string& getFileType() const { return fVariablesMap["type"].as<std::string>();}
    inline bool fileTypeIsSet() const { return (bool)fVariablesMap.count("type"); }
	/**
     * @brief Method returning lower bound of events range to process or -1 if they were not specified.
     */
    inline int getLowerEventBound() const {return fVariablesMap["range"].as< std::vector<int> >()[0];}
    /**
     * @brief Method returning higher bound of events range to process or -1 if they were not specified.
     */
    inline int getHigherEventBound() const {return fVariablesMap["range"].as< std::vector<int> >()[1];}
    inline bool paramIsSet() const { return (bool)fVariablesMap.count("param"); }
    inline const std::string& getParam() const {return fVariablesMap["param"].as< std::string >(); }
    
private:
	po::options_description fOptDescriptions;
	po::variables_map fVariablesMap;

};

#endif /* __CINT__ */
#endif /* _JPET_CMD_PARSER_H_ */
