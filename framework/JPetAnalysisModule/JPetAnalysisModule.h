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
#include <THashTable.h>
#include <TH1F.h>
#include <TH2F.h>

/**
 * @brief Template of a single module of the analysis representing one stage of the processing.
 *
 * In order to implement one stage of data analysis, user should create a class inheriting from JPetAnalysisModule and fill its methods with custom analysis code. Next, the Analysis Module object must be created and added as a task to the JPetManager in order to be executed. 
 The following methods can be filled with the user code:
 + createInputObjects
 + createOutputObjects
 + exec
 + terminate

 Moreover, the addStatsObject(TObject*) method can be used to store any TObject (like TH1 or TGraph) in an internal TList. Such stored objects can be accessed by getStatsObjects()->At(i) where i is the number of stored object. Add objects from the list will be written to the ROOT file at the end of processing. This mechanism is intended for saving any statistics of the data processing (See workdir/AnalysisExample).
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
  virtual void createInputObjects(const char* inputFilename=0)=0; //
  virtual void createOutputObjects(const char* outputFilename=0)=0; //
  virtual void exec()=0; // called for every event
  virtual long long getEventNb()=0;
  virtual void runSubmodules();
  virtual void terminate()=0; // called once when analysis terminates

  int addStatsObject(TObject * statObj);
  const THashTable * getStatsObjects() const;

  // more convenient methods to access histograms from the statsObjects list
  TH1F * getHisto1D(const char * name);

  TH2F * getHisto2D(const char * name);

  TObject * getStatsObject(const char * name);


  ClassDef(JPetAnalysisModule,1);

protected:
  virtual void addSubmodule( JPetAnalysisModule* new_submodule );
  TTree fSubmoduleSharedTree;
  TTree* fSuperSharedTree;
  std::vector< JPetAnalysisModule* > fSubmodules;
  THashTable fStats; ///< a hash table to store all objects for statistics of the processing, i.e. histograms

};
#endif /*  !JPETANALYSISMODULE_H */
