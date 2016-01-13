#ifndef JPET_ANALYSIS_MODULE_KB_H
#define JPET_ANALYSIS_MODULE_KB_H

#include <cstddef>
#include <TFile.h>
#include <TList.h>

#include <JPetAnalysisModule/JPetAnalysisModule.h>
#include <JPetManager/JPetManager.h>
#include <JPetWriter/JPetWriter.h>


class JPetAnalysisModuleContainers: public JPetAnalysisModule
{
private:
  int fEventNb;
  JPetManager& m_manager;
  
public:
  JPetAnalysisModuleContainers(void);
  JPetAnalysisModuleContainers(const char* name, const char* title);
  virtual ~JPetAnalysisModuleContainers(void);
  virtual void createInputObjects(const char* inputFilename=0);
  virtual void createOutputObjects(const char* outputFilename=0);
  virtual void exec(void);
  virtual inline long long getEventNb(void) {return fEventNb;}
  virtual void terminate(void);

  ClassDef(JPetAnalysisModuleContainers, 1);
};

#endif	// JPET_ANALYSIS_MODULE_KB_H
