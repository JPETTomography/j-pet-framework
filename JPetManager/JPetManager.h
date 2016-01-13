/**
 *  @copyright Copyright (c) 2015, J-PET collaboration
 *  @file JPetManager.h
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief Main manager of the analysis performed with the J-PET Framework.
 */

#ifndef JPETMANAGER_H
#define JPETMANAGER_H

#include "../JPetOptions/JPetOptions.h"
#include "../JPetTaskExecutor/JPetTaskExecutor.h"

/**
 * @brief Main manager of the analysis performed with the J-PET Framework.
 *
 * Each analysis program needs an instance of the JPetManager which is responsible for parsing the command line arguments
 * registering processing tasks, and
 * sending it to JPetExecutor which executes the registered tasks in threads.
 */

class JPetManager
{
public:
  static JPetManager& getManager();
  ~JPetManager();
  void run();
  void registerTask(const TaskGenerator& taskGen);
  void parseCmdLine(int argc, char** argv);
  inline std::vector<JPetOptions> getOptions() const {
    return fOptions;
  }

private:
  JPetManager() {
    fTaskGeneratorChain = new TaskGeneratorChain;
  }
  JPetManager(const JPetManager&);
  void operator=(const JPetManager&);

  std::vector<JPetOptions> fOptions;
  TaskGeneratorChain* fTaskGeneratorChain;
};
#endif /*  !JPETMANAGER_H */
