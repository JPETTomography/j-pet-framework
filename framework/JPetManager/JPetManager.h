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

using TaskGenerator = std::function< std::unique_ptr<JPetAnalysisModule>() >;
using TaskGeneratorChain = std::vector<const TaskGenerator>;

template <typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params)
{
 return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

template <typename T, typename... Ts>
std::function<std::unique_ptr<T>()> makeTaskGenerator(Ts&&... params)
{
 return [&](){return make_unique<T>(std::forward<Ts>(params)...);};
}

class JPetManager: public TNamed {
 public:
  static JPetManager& GetManager();
  ~JPetManager();
  void Init(){};
  void Run();
  void AddTask(JPetAnalysisModule* mod);
  void AddTaskGeneratorChain(std::shared_ptr< TaskGeneratorChain > taskGeneratorChain) {ftaskGeneratorChain = taskGeneratorChain;}
  void ParseCmdLine(int argc, char** argv);
  std::vector<std::string> getInputFileNames() const;
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
  void ProcessFromCmdLineArgs(int fileIndex);
  bool userBoundsAreCorrect(long long checkedEvent);
  void manageProgressBar(long long done, long long end);
  void processEventsInRange(long long begin, long long end);
  void prepareCurrentTaskForFile(const string& file);
  void setEventBounds(long long& begin, long long& end, long long& eventCount);

  JPetCmdParser fCmdParser;
  JPetParamManager fParamManager;
  JPetUnpacker fUnpacker;
  std::list<JPetAnalysisModule*> fTasks;
  std::list<JPetAnalysisModule*>::iterator currentTask;
  std::shared_ptr<TaskGeneratorChain> ftaskGeneratorChain;
  bool fIsProgressBarEnabled;
};
#endif /*  !JPETMANAGER_H */
