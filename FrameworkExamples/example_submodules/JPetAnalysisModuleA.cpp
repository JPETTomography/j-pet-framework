#include "./JPetAnalysisModuleA.h"

#include <JPetSigCh/JPetSigCh.h>
#include <JPetSignal/JPetSignal.h>
#include "JPetAnalysisModuleA_1.h"
#include "JPetAnalysisModuleA_2.h"

#include <vector>

using namespace std;

JPetAnalysisModuleA::JPetAnalysisModuleA():
  JPetAnalysisModule("module A", "the great"),
  fEventNb(0)
{
	addSubmodule( new JPetAnalysisModuleA_1(&fSubmoduleSharedTree) );
	addSubmodule( new JPetAnalysisModuleA_2(&fSubmoduleSharedTree) );
}

JPetAnalysisModuleA::JPetAnalysisModuleA(const char* name, const char* title):
  JPetAnalysisModule(name, title),
  fEventNb(0)
{
  
}

void JPetAnalysisModuleA::exec()
{
  std::cout << "\nHere I am, the main module" << std::endl;
  std::cout << "Now I will run the submodules!" << std::endl;
  runSubmodules();
  std::cout << "\nI'm back, the main module, reading what my submodules made in my fSubmoduleSharedTree\n" << std::endl;
}
