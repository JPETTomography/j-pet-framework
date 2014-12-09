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

void JPetAnalysisModule::runSubmodules(){
	for (int i = 0; i < fSubmodules.size(); i++)
		fSubmodules[i]->exec();
}

void JPetAnalysisModule::addSubmodule( JPetAnalysisModule* new_submodule ){
	fSubmodules.push_back( new_submodule );
}

int JPetAnalysisModule::addStatsObject(TObject * statObj){
  fStats.Add( statObj );
  return fStats.GetEntries();
}

const TList * JPetAnalysisModule::getStatsObjects() const{
  return &fStats;
}
