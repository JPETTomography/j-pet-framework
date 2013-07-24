/**
 *  @copyright Copyright (c) 2013, Wojciech Krzemien
 *  @file JPetManager.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief 
 */ 

#ifndef JPETMANAGER_H 
#define JPETMANAGER_H 

#include <vector>
#include <TNamed.h> 

class JPetAnalysisModule;

class JPetManager: public TNamed {
 public:
  static JPetManager& GetManager();
  ~JPetManager();
  void Init();
  void Run();
  void AddTask(JPetAnalysisModule* mod);
  
 private:
  JPetManager();
  JPetManager(const JPetManager&);
  void operator=(const JPetManager&); 
  std::vector<JPetAnalysisModule*> fTasks;
};
#endif /*  !JPETMANAGER_H */
