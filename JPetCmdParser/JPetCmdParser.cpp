/**
 *  @copyright Copyright (c) 2014, J-PET collaboration
 *  @file JPetCmdParser.cpp
 *  @author Karol Stola
 */

#include "JPetCmdParser.h"
#include <iostream>
#include "../CommonTools/CommonTools.h"
#include "../../JPetLoggerInclude.h"

JPetCmdParser::JPetCmdParser(): fOptionsDescriptions("Allowed options")
{
  std::vector<int> tmp;
  tmp.push_back(-1);
  tmp.push_back(-1);

  fOptionsDescriptions.add_options()
  ("help,h", "produce help message")
  ("type,t", po::value<std::string>()->required()->implicit_value(""), "type of file: hld, root or scope")
  ("file,f", po::value< std::vector<std::string> >()->required()->multitoken(), "File(s) to open")
  ("range,r", po::value< std::vector<int> >()->multitoken()->default_value(tmp, ""), "Range of events to process.")
  ("param,p", po::value<std::string>(), "File with TRB numbers.")
  ("runId,i", po::value<int>(), "Run id.")
  ("progressBar,b", "Progress bar.");
}

JPetCmdParser::~JPetCmdParser()
{
  /**/
}

std::vector<JPetOptions> JPetCmdParser::parseAndGenerateOptions(int argc, const char** argv)
{
  po::variables_map variablesMap;
  if (argc == 1) {
    ERROR("No options provided.");
    std::cerr << "No options provided" << "\n";
    std::cerr << getOptionsDescription() << "\n";
    exit(-1);
  }

  po::store(po::parse_command_line(argc, argv, fOptionsDescriptions), variablesMap);

  /* print out help */
  if (variablesMap.count("help")) {
    std::cout << getOptionsDescription() << "\n";
    exit(0);
  }
  po::notify(variablesMap);
  if (!areCorrectOptions(variablesMap)) {
    exit(-1);
  }

  return generateOptions(variablesMap);
}

bool JPetCmdParser::areCorrectOptions(const po::variables_map& variablesMap) const
{
  /* Parse range of events */
  if (variablesMap.count("range")) {
    if (variablesMap["range"].as< std::vector<int> >().size() != 2) {
      ERROR("Wrong number of bounds in range.");
      std::cerr << "Wrong number of bounds in range: " << variablesMap["range"].as< std::vector<int> >().size() << std::endl;
      return false;
    }
    if (
      variablesMap["range"].as< std::vector<int> >()[0]
      > variablesMap["range"].as< std::vector<int> >()[1]) {
      ERROR("Wrong range of events.");
      std::cerr << "Wrong range of events." << std::endl;
      return false;
    }
  }

  if (!isCorrectFileType(getFileType(variablesMap))) {
    ERROR("Wrong type of file.");
    std::cerr << "Wrong type of file: " << getFileType(variablesMap) << std::endl;
    std::cerr << "Possible options: hld, root or scope" << std::endl;
    return false;
  }

  if (isRunNumberSet(variablesMap)) {
    int l_runId = variablesMap["runId"].as<int>();

    if (l_runId <= 0) {
      ERROR("Wrong number of run id.");
      std::cerr << "Wrong number of run id: " << l_runId << std::endl;
      return false;
    }
  }

  if (isProgressBarSet(variablesMap)) {
    int l_progressBar = variablesMap["progressBar"].as<int>();

    if (l_progressBar != 0 && l_progressBar != 1) {
      ERROR("Wrong parameter of progressbar.");
      std::cerr << "Wrong parameter of progressbar: " << l_progressBar << std::endl;
      return false;
    }
  }

  std::vector<std::string> fileNames(variablesMap["file"].as< std::vector<std::string> >());
  for (int i = 0; i < fileNames.size(); i++) {
    if ( ! CommonTools::ifFileExisting(fileNames[i]) ) {
      std::string fileName = fileNames[i];
      ERROR("File : " + fileName + " does not exist.");
      std::cerr << "File : " << fileNames[i] << " does not exist" << std::endl;
      return false;
    }
  }
  return true;
}

std::vector<JPetOptions> JPetCmdParser::generateOptions(const po::variables_map& optsMap) const
{
  std::map<std::string, std::string> options = JPetOptions::getDefaultOptions();
  auto fileType = getFileType(optsMap);
  if (isCorrectFileType(fileType)) {
    options.at("inputFileType") = fileType;
  }
  if (isRunNumberSet(optsMap)) {
    options.at("runId") = std::to_string(getRunNumber(optsMap));
  }
  if (isProgressBarSet(optsMap)) {
    options.at("progressBar") = "true";
  }
  auto firstEvent  = getLowerEventBound(optsMap);
  auto lastEvent  = getHigherEventBound(optsMap);
  if (firstEvent >= 0) options.at("firstEvent") = std::to_string(firstEvent);
  if (lastEvent >= 0) options.at("lastEvent") = std::to_string(lastEvent);
  auto files = getFileNames(optsMap); 
  std::vector<JPetOptions>  optionContainer;
  for (auto file :files) {
    options.at("inputFile") = file;
    optionContainer.push_back(JPetOptions(options));
  }
  return optionContainer;
}

//#endif /* __CINT__ */
