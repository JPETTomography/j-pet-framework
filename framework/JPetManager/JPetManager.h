/**
 *  @copyright Copyright (c) 2013, Wojciech Krzemien
 *  @file JPetManager.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief Main manager of the analysis performed with the J-PET Framework.
 */ 

#ifndef JPETMANAGER_H 
#define JPETMANAGER_H 

#include "../JPetCmdParser/JPetCmdParser.h"
#include "../JPetAnalysisRunner/JPetAnalysisRunner.h"


/**
 * @brief Main manager of the analysis performed with the J-PET Framework.
 *
 * Each anaylsis program needs an instance of the JPetManager which is responsible for parsing the command line arguments
 * registering processing tasks, and
 * sending it to AnalysisRunners which executes the registered tasks in threads.
 */

class JPetManager 
{
 public:
  static JPetManager& getManager();
  ~JPetManager();
  void run();
  void addTaskGeneratorChain( TaskGeneratorChain* taskGeneratorChain);
  void parseCmdLine(int argc, char** argv);

 private:
  std::vector<std::string> getFullInputFileNames() const;
  int getRunNumber() const;

  JPetManager(){/**/};
  JPetManager(const JPetManager&);
  void operator=(const JPetManager&); 

  JPetCmdParser fCmdParser;
  TaskGeneratorChain* ftaskGeneratorChain;
};
#endif /*  !JPETMANAGER_H */
