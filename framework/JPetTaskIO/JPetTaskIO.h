/**
 *  @copyright Copyright (c) 2015, Wojciech Krzemien
 *  @file JPetTaskIO.h 
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief
 */ 

#ifndef JPETTASKIO_H 
#define JPETTASKIO_H 
#include "../JPetTaskInterface/JPetTaskInterface.h"
#include "../JPetParamManager/JPetParamManager.h"

#include "../JPetOptions/JPetOptions.h"

class JPetWriter;
class JPetReader;
class JPetTreeHeader;
class JPetTask;


/**
 * @brief Class representing computing task with input/output operations.
 *
 */
class JPetTaskIO: public JPetTaskInterface
{
 public:
  JPetTaskIO();
  virtual void init(const JPetOptions::Options& opts);
  virtual void exec();
  virtual void terminate();
  virtual ~JPetTaskIO();
  virtual void addSubTask(JPetTaskInterface* subtask) {fTask = (JPetTask*)subtask; };
  void setOptions(const JPetOptions& opts) { fOptions = opts;}

  void manageProgressBar(long long done, long long end);
  float setProgressBar(int currentEventNumber, int numberOfEvents);

  void setParamManager(JPetParamManager*paramManager) {fParamManager = paramManager;}

 protected:
  virtual void createInputObjects(const char* inputFilename);
  virtual void createOutputObjects(const char* outputFilename);
  void setUserLimits(const JPetOptions& opts, long long& firstEvent,long long& lastEvent) const;
  


  JPetTask* fTask;
  int fEventNb;
  JPetOptions fOptions; //options like max num of events, first event, last event, inputFileType, outputFileType
  JPetWriter* fWriter;
  JPetReaderInterface* fReader;
  JPetTreeHeader* fHeader;

/// from CommonAnalysisModule
  const JPetParamBank & getParamBank();
  JPetParamManager& getParamManager() {return *fParamManager;}

private:
  JPetParamManager* fParamManager;

};
#endif /*  !JPETTASKIO_H */
