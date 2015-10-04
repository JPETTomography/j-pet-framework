/**
 *  @copyright Copyright (c) 2013, Wojciech Krzemien
 *  @file JPetManager.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief Main manager of the analysis performed with the J-PET Framework.
 */ 

#ifndef JPETMANAGER_H 
#define JPETMANAGER_H 

#include <memory>
//#include "../JPetCmdParser/JPetCmdParser.h"
#include "../JPetOptions/JPetOptions.h"
#include "../JPetTaskExecutor/JPetTaskExecutor.h"

class JPetTaskIO;

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
  void registerTask(const TaskGenerator& taskGen);
  void addTaskGeneratorChain( TaskGeneratorChain* taskGeneratorChain);
  void parseCmdLine(int argc, char** argv);
  inline std::vector<JPetOptions> getOptions() const { return fOptions;}

 private:

  JPetManager() { fTaskGeneratorChain = new TaskGeneratorChain; }
  JPetManager(const JPetManager&);
  void operator=(const JPetManager&); 

  std::vector<JPetOptions> fOptions;
  
  TaskGeneratorChain* fTaskGeneratorChain;
};
#endif /*  !JPETMANAGER_H */
