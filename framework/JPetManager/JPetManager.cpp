/**
  *  @copyright Copyright (c) 2014, J-PET collaboration 
  *  @file JPetManager.cp
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
  UnpackFile(); /// @todo some more clever way :P
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

    fCmdParser.parse(argc, (const char **)argv);
    if (fCmdParser.paramIsSet()){
        fParamManager.readFile(fCmdParser.getParam().c_str());
    }
    if(fCmdParser.fileTypeIsSet()) {
      /// @todo fileType should be probably enum not string
      if (fCmdParser.getFileType()=="hld") {
        /// @todo other two parameters must be also set somewhere
        fUnpacker.setParams(fCmdParser.getFileName().c_str());
      }
    }
/*    
    if(fCmdParser.isRunNumberSet())
    {
      std::cout << "fParamManager.getDataSize() = " << fParamManager.getDataSize() << std::endl;
      std::cout << "fCmdParser.isRunNumberSet()" << std::endl;
      fParamManager.fillKBsData(fCmdParser.getRunNumber());
      std::cout << "fParamManager.getKBsDataSize() = " << fParamManager.getKBsDataSize() << std::endl;
    }
    */

    if(fCmdParser.isRunNumberSet())
    {
std::cout << "Scins" << std::endl;      
std::cout << "fParamManager.getDataSize() = " << fParamManager.getDataSize(JPetParamManager::kScintillator) << std::endl;
      
std::cout << "PMs" << std::endl;      
std::cout << "fParamManager.getDataSize() = " << fParamManager.getDataSize(JPetParamManager::kPM) << std::endl;
      
std::cout << "KBs" << std::endl;      
std::cout << "fParamManager.getDataSize() = " << fParamManager.getDataSize(JPetParamManager::kKB) << std::endl;
      
std::cout << "TRBs" << std::endl;      
std::cout << "fParamManager.getDataSize() = " << fParamManager.getDataSize(JPetParamManager::kTRB) << std::endl;
      
std::cout << "TOMBs" << std::endl;      
std::cout << "fParamManager.getDataSize() = " << fParamManager.getDataSize(JPetParamManager::kTOMB) << std::endl;

      fParamManager.fillContainers(fCmdParser.getRunNumber());

std::cout << "Scins" << std::endl;      
std::cout << "fParamManager.getDataSize() = " << fParamManager.getDataSize(JPetParamManager::kScintillator) << std::endl;
      
std::cout << "PMs" << std::endl;      
std::cout << "fParamManager.getDataSize() = " << fParamManager.getDataSize(JPetParamManager::kPM) << std::endl;
      
std::cout << "KBs" << std::endl;      
std::cout << "fParamManager.getDataSize() = " << fParamManager.getDataSize(JPetParamManager::kKB) << std::endl;
      
std::cout << "TRBs" << std::endl;      
std::cout << "fParamManager.getDataSize() = " << fParamManager.getDataSize(JPetParamManager::kTRB) << std::endl;
      
std::cout << "TOMBs" << std::endl;      
std::cout << "fParamManager.getDataSize() = " << fParamManager.getDataSize(JPetParamManager::kTOMB) << std::endl;
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
