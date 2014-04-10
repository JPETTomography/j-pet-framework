#include "JPetAnalysisModule.h"

ClassImp(JPetAnalysisModule);

JPetAnalysisModule::JPetAnalysisModule(const char* name, const char* title, TTree * shared_tree = NULL)
  : TNamed(name, title)
  , fSuperSharedTree( shared_tree )
{ }

JPetAnalysisModule::JPetAnalysisModule() 
{ }

JPetAnalysisModule::~JPetAnalysisModule()
{
	for (int i = 0; i < fSubmodules.size(); i++)
		delete fSubmodules[i];
	
}


