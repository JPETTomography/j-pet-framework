/**
 *  @copyright Copyright (c) 2014, Wojciech Krzemien
 *  @file JPetTask.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief
 */ 

#ifndef JPETTASK_H 
#define JPETTASK_H 
#include "../JPetTaskInterface/JPetTaskInterface.h"
#include "../JPetParamBank/JPetParamBank.h"
#include "../JPetStatistics/JPetStatistics.h"
#include <TNamed.h>

class JPetWriter;

class JPetTask: public JPetTaskInterface, public TNamed
{
 public:
  JPetTask(const char * name="", const char * description="");
  virtual void init(const JPetTaskInterface::Options& opts);
  virtual void exec();
  virtual void terminate();
  virtual void addSubTask(JPetTaskInterface*) {};
  virtual void setParamManager(JPetParamManager*paramManager);
  virtual void setStatistics(JPetStatistics* statistics);
  virtual void setWriter(JPetWriter* writer) {};
  virtual void setEvent(TNamed* ev);
  const JPetParamBank& getParamBank();
  JPetStatistics & getStatistics();
  
virtual TNamed* getEvent() {return fEvent;}
 protected:
  TNamed* fEvent;
  JPetParamManager* fParamManager;
  JPetStatistics * fStatistics;
  
};
#endif /*  !JPETTASK_H */
