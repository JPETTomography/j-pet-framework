/**
 *	@brief example of module running submodules
 */
#ifndef _JPETANALYSISMODULE_A_H_
#define _JPETANALYSISMODULE_A_H_

#include <cstddef>

#include <JPetAnalysisModule/JPetAnalysisModule.h>

class JPetAnalysisModuleA: public JPetAnalysisModule {
  
  public:

  JPetAnalysisModuleA();
  JPetAnalysisModuleA(const char* name, const char* title);
  virtual ~JPetAnalysisModuleA(){}
  virtual void createInputObjects(const char* inputFilename=0){}
  virtual void createOutputObjects(const char* outputFilename=0){}
  virtual void exec();
  virtual long long getEventNb() {return fEventNb;}
  virtual void terminate(){}

  private:
  int fEventNb;
};

#endif
