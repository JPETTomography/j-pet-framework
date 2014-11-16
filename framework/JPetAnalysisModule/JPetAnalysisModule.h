/**
 *  @copyright Copyright (c) 2013, Wojciech Krzemien
 *  @file JPetAnalysisModule.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief
 */ 

#ifndef JPETANALYSISMODULE_H 
#define JPETANALYSISMODULE_H

#include <vector>
#include <TNamed.h>
#include <TTree.h>
#include <TList.h>

/**
 * @brief Template of a single module of the analysis representing one stage of the processing.
 *
 * In order to implement one stage of data analysis, user should create a class inheriting from JPetAnalysisModule and fill its methods with custom analysis code. Next, the Analysis Module object must be created and added as a task to the JPetManager in order to be executed. 
 The following methods can be filled with the user code:
 + CreateInputObjects
 + CreateOutputObjects
 + Exec
 + Terminate

 Moreover, the AddStatsObject(TObject*) method can be used to store any TObject (like TH1 or TGraph) in an internal TList. Such stored objects can be accessed by GetStatsObjects()->At(i) where i is the number of stored object. Add objects from the list will be written to the ROOT file at the end of processing. This mechanism is intended for saving any statistics of the data processing (See workdir/AnalysisExample).
 */
class JPetAnalysisModule: public TNamed 
{
public:
  JPetAnalysisModule();
  JPetAnalysisModule(const char* name, const char* title, TTree * shared_tree = NULL);
  
private:
  JPetAnalysisModule(const JPetAnalysisModule &analysisModule);
  JPetAnalysisModule& operator=(const JPetAnalysisModule &analysisModule);
  
public:
  virtual ~JPetAnalysisModule(); 
  virtual void CreateInputObjects(const char* inputFilename=0)=0; //
  virtual void CreateOutputObjects(const char* outputFilename=0)=0; //
  virtual void Exec()=0; // called for every event
  virtual long long GetEventNb()=0;
  virtual void RunSubmodules();
  virtual void Terminate()=0; // called once when analysis terminates

  int AddStatsObject(TObject * statObj);
  const TList * GetStatsObjects() const; 

  ClassDef(JPetAnalysisModule,1);

protected:
  virtual void AddSubmodule( JPetAnalysisModule* new_submodule );
  TTree fSubmoduleSharedTree;
  TTree* fSuperSharedTree;
  std::vector< JPetAnalysisModule* > fSubmodules;
  TList fStats; ///< a list to store all objects for statistics of the processing, i.e. histograms
};
#endif /*  !JPETANALYSISMODULE_H */
