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
  const int kNevent = 10;
  int input[kNevent] = {1};
  for (taskIter = fTasks.begin(); taskIter != fTasks.end(); taskIter++) {
    (*taskIter)->CreateInputObjects(); /// readers
    (*taskIter)->CreateOutputObjects(); /// writers + histograms
    // tutaj pobierz liczbe zdarzen/obiektow z kontenera wejsciowego
    // (*taskIter)->GetInputModule() czy cos w tym stylu
    for (int i = 0; i < kNevent; i++) {
      (*taskIter)->Exec();
    }
    (*taskIter)->Terminate();
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
