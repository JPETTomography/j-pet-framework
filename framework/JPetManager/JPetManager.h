/**
 *  @copyright Copyright (c) 2013, Wojciech Krzemien
 *  @file JPetManager.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief 
 */ 

#ifndef JPETMANAGER_H 
#define JPETMANAGER_H 

#include "../JPetAnalysisModule/JPetAnalysisModule.h"
#include "../JPetCmdParser/JPetCmdParser.h"
#include "../JPetParamManager/JPetParamManager.h"
#include "../JPetUnpacker/JPetUnpacker.h"

//#include <vector>
#include <list>
#include <TNamed.h> 
#include <TString.h>

class JPetAnalysisModule;
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
  void AddTask(JPetAnalysisModule* mod);
  void ParseCmdLine(int argc, char** argv);
  std::string getInputFileName() const;
  std::string getBaseInputFileName() const;
  int getRunNumber() const;
  JPetParamManager & getParamManagerInstance() { return fParamManager; }
  void UnpackFile() { if(fCmdParser.IsFileTypeSet()) fUnpacker.exec();}
  TString GetTimeString() const;

//  ClassDef(JPetManager,1);

 private:
  JPetManager();
  JPetManager(const JPetManager&);
  void operator=(const JPetManager&); 
  
  float setProgressBar(int currentEventNumber, int numberOfEvents);
  void ProcessFromCmdLineArgs();

  JPetCmdParser fCmdParser;
  JPetParamManager fParamManager;
  JPetUnpacker fUnpacker;
  std::list<JPetAnalysisModule*> fTasks;
  bool fIsProgressBarEnabled;
};
#endif /*  !JPETMANAGER_H */
