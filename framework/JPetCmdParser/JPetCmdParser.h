/**
 *  @copyright Copyright (c) 2014, J-PET collaboration
 *  @file JPetCmdParser.h
 *  @author Karol Stola
 *  @brief 
 */

#ifndef _JPET_CMD_PARSER_H_
#define _JPET_CMD_PARSER_H_

class JPetCmdParser;

#include "boost/program_options.hpp" // Library parsing command line arguments
#include <string>

namespace po = boost::program_options;

class JPetCmdParser {
public:
  JPetCmdParser();
  ~JPetCmdParser();
  
private:
  JPetCmdParser(const JPetCmdParser &cmdParser);
  JPetCmdParser& operator=(const JPetCmdParser &cmdParser);
  
public:
  void parse(int argc, const char** argv);
  inline const std::string& getFileName() const { return fVariablesMap["file"].as<std::string>();}
  bool isCorrectFileType(const std::string& type) const;
  inline const std::string& getFileType() const { return fVariablesMap["type"].as<std::string>();}
  inline bool IsFileTypeSet() const { return (bool)fVariablesMap.count("type"); }
      /**
    * @brief Method returning lower bound of events range to process or -1 if they were not specified.
    */
  inline int getLowerEventBound() const {return fVariablesMap["range"].as< std::vector<int> >()[0];}
  /**
    * @brief Method returning higher bound of events range to process or -1 if they were not specified.
    */
  inline int getHigherEventBound() const {return fVariablesMap["range"].as< std::vector<int> >()[1];}
  inline bool isParamSet() const { return (bool)fVariablesMap.count("param"); }
  inline const std::string& getParam() const {return fVariablesMap["param"].as< std::string >(); }

  inline bool isRunNumberSet() const { return (bool)fVariablesMap.count("runId"); }
  inline const int getRunNumber() const { return fVariablesMap["runId"].as<int>();}
  
  inline bool isProgressBarSet() const { return (bool)fVariablesMap.count("progressBar"); }

private:
      po::options_description fOptDescriptions;
      po::variables_map fVariablesMap;
};

#endif /* _JPET_CMD_PARSER_H_ */
