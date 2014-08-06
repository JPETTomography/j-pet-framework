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

#include <vector>
#include <list>
#include <TNamed.h> 

class JPetAnalysisModule;
class JPetReader;
class JPetWriter;

class JPetManager: public TNamed {
 public:
  static JPetManager& GetManager();
  ~JPetManager();
  void Init(){};
  void Run();
  void AddTask(JPetAnalysisModule* mod);
  void ParseCmdLine(int argc, char** argv);
  const char* getInputFileName() const;
  JPetParamManager & getParamManagerInstance() { return fParamManager; }
  void UnpackFile() { if(fCmdParser.fileTypeIsSet()) fUnpacker.Exec();}
 
  ClassDef(JPetManager,1);

 private:
  JPetManager();
  JPetManager(const JPetManager&);
  void operator=(const JPetManager&); 

  JPetCmdParser fCmdParser;
  JPetParamManager fParamManager;
  JPetUnpacker fUnpacker;
  std::vector<JPetAnalysisModule*> fTasks;
};
#endif /*  !JPETMANAGER_H */
