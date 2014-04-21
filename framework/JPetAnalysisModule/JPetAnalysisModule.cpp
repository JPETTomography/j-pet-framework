#include "JPetAnalysisModule.h"

ClassImp(JPetAnalysisModule);

JPetAnalysisModule::JPetAnalysisModule()
	:fSuperSharedTree(NULL)
{ }

JPetAnalysisModule::JPetAnalysisModule(const char* name, const char* title, TTree * shared_tree)
  : TNamed(name, title)
  , fSuperSharedTree( shared_tree )
{ }

JPetAnalysisModule::~JPetAnalysisModule()
{
	for (int i = 0; i < fSubmodules.size(); i++)
		delete fSubmodules[i];
	
}

void JPetAnalysisModule::RunSubmodules(){
	for (int i = 0; i < fSubmodules.size(); i++)
		fSubmodules[i]->Exec();
}

void JPetAnalysisModule::AddSubmodule( JPetAnalysisModule* new_submodule ){
	fSubmodules.push_back( new_submodule );
}