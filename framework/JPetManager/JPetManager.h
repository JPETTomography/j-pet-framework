/**
 *  @copyright Copyright (c) 2013, Wojciech Krzemien
 *  @file JPetManager.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief 
 */ 

#ifndef JPETMANAGER_H 
#define JPETMANAGER_H 

//#include "../JPetAnalysisModule/JPetAnalysisModule.h"
#include "../JPetCmdParser/JPetCmdParser.h"
//#include "../JPetParamManager/JPetParamManager.h"
//#include "../JPetUnpacker/JPetUnpacker.h"
#include "../JPetAnalysisRunner/JPetAnalysisRunner.h"
//#include "../JPetCommonAnalysisModule/JPetCommonAnalysisModule.h"

#include <list>
#include <TNamed.h> 
#include <TString.h>
#include <TProof.h>


class JPetReader;
class JPetWriter;

/**
 * @brief Main manager of the analysis performed with the J-PET Framework.
 *
 * Each anaylsis program needs an instance of the JPetManager which is responsible for parsing command  line arguments, handling data from the database and for executing subsequent Analysis Modules.
 */

class JPetManager: public TNamed {
 public:
  static JPetManager& GetManager();
  ~JPetManager();
  void Init(){};
  void Run();
  void AddTaskGeneratorChain( TaskGeneratorChain* taskGeneratorChain);
  void ParseCmdLine(int argc, char** argv);
  std::vector<std::string> getFullInputFileNames() const;

  int getRunNumber() const;
  TString GetTimeString() const;

//  ClassDef(JPetManager,1);

 private:
  JPetManager();
  JPetManager(const JPetManager&);
  void operator=(const JPetManager&); 

  JPetCmdParser fCmdParser;
  TaskGeneratorChain* ftaskGeneratorChain;
};
#endif /*  !JPETMANAGER_H */
