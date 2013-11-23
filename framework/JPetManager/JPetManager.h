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

#include <vector>
#include <TNamed.h> 

class JPetAnalysisModule;

class JPetManager: public TNamed {
 public:
  static JPetManager& GetManager();
  ~JPetManager();
  //dodalem klamry, bo kod nie chcial sie linkowac - Damian
  void Init(){};
  void Run();
  void AddTask(JPetAnalysisModule* mod);
  void ParseCmdLine(int argc, char** argv) {fCmdParser.parse(argc, argv);}
  const char* getInputFileName() {return fCmdParser.getFileName().c_str(); }
 
  ClassDef(JPetManager,1);

 private:
  JPetCmdParser fCmdParser;
  JPetManager();
  JPetManager(const JPetManager&);
  void operator=(const JPetManager&); 
  std::vector<JPetAnalysisModule*> fTasks;
};
#endif /*  !JPETMANAGER_H */
