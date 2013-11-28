/**
 *  @copyright Copyright (c) 2013, Wojciech Krzemien
 *  @file JPetAnalysisModule.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief
 */ 

#ifndef JPETANALYSISMODULE_H 
#define JPETANALYSISMODULE_H

#include "TNamed.h" 

class JPetAnalysisModule: public TNamed {
 public:
  JPetAnalysisModule();
  JPetAnalysisModule(const char* name, const char* title); 
  virtual ~JPetAnalysisModule(); 
  virtual void CreateInputObjects(const char* inputFilename=0)=0; //
  virtual void CreateOutputObjects(const char* outputFilename=0)=0; //
  virtual void Exec()=0; // called for every event
  virtual long long GetEventNb()=0;
  virtual void Terminate()=0; // called once when analysis terminates 

  ClassDef(JPetAnalysisModule,1);
};
#endif /*  !JPETANALYSISMODULE_H */
