/**
 *  @copyright Copyright (c) 2014, Wojciech Krzemien
 *  @file JPetTask.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief
 */ 

#ifndef JPETTASK_H 
#define JPETTASK_H 
#include "../JPetTaskInterface/JPetTaskInterface.h"
#include <TNamed.h>

class JPetWriter;

class JPetTask: public JPetTaskInterface
{
 public:
  JPetTask();
  virtual void init(const JPetTaskInterface::Options& opts);
  virtual void exec();
  virtual void terminate();
  virtual void addSubTask(JPetTaskInterface*) {};
  virtual void setParamManager(JPetParamManager*paramManager) {};
  virtual void setWriter(JPetWriter* writer) {};
  virtual void setEvent(TNamed* ev);
  virtual TNamed* getEvent() {return fEvent;}
 protected:
  TNamed* fEvent;
  
};
#endif /*  !JPETTASK_H */
