/**
  *  @copyright Copyright (c) 2013, Wojciech Krzemien
  *  @file JPetManager.cc
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "./JPetManager.h"
//#include "../JPetAnalysisModule/JPetAnalysisModule.h"
#include <cassert>

ClassImp(JPetManager);

JPetManager& JPetManager::GetManager()
{
  static JPetManager instance;
  return instance;
}

JPetManager::JPetManager(): TNamed("JPetMainManager", "JPetMainManager")
{

}

// adds the given analysis module to a list of registered task
// @todo check if the module is not already registered
void JPetManager::AddTask(JPetAnalysisModule* mod)
{
  assert(mod);
  fTasks.push_back(mod);
}

void JPetManager::Run()
{

  JPetWriter* currentWriter = 0;
  std::vector<JPetAnalysisModule*>::iterator taskIter;
  // pseudo-input container
  long long  kNevent = 0;
    for (taskIter = fTasks.begin(); taskIter != fTasks.end(); taskIter++) {
    (*taskIter)->CreateInputObjects(); /// readers
    (*taskIter)->CreateOutputObjects(); /// writers + histograms
    // tutaj pobierz liczbe zdarzen/obiektow z kontenera wejsciowego
    // (*taskIter)->GetInputModule() czy cos w tym stylu
    kNevent = (*taskIter)->GetEventNb();
    for (long long i = 0; i < kNevent; i++) {
      (*taskIter)->Exec();
    }
    (*taskIter)->Terminate();
  }
}

void JPetManager::ParseCmdLine(int argc, char** argv){
    fCmdParser.parse(argc, argv);
    if (fCmdParser.paramIsSet()){
        fParamManager.readFile(fCmdParser.getParam().c_str());
    }
}

JPetManager::~JPetManager()
{
  std::vector<JPetAnalysisModule*>::iterator taskIter;
  for (taskIter = fTasks.begin(); taskIter != fTasks.end(); taskIter++) {
    (*taskIter)->Terminate();
    delete (*taskIter);
    *taskIter = 0;
  }
}
