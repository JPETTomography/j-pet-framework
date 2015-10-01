/**
 *  @copyright Copyright (c) 2014, Wojciech Krzemien
 *  @file JPetTaskInterface.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief
 */ 

#ifndef JPETTASKINTERFACE_H 
#define JPETTASKINTERFACE_H 

#include <map>
#include <string>

class JPetParamManager;

class JPetTaskInterface {
 public:
  typedef std::map<std::string, std::string> Options;
  virtual ~JPetTaskInterface() {;}
  virtual void init(const Options& options)=0;
  virtual void exec()=0;
  virtual void terminate()=0;
  virtual void addSubTask(JPetTaskInterface* subtask)=0;
  virtual void setParamManager(JPetParamManager*paramManager)=0;
  

};
#endif /*  !JPETTASKINTERFACE_H */
