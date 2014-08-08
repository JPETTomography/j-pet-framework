/**
  *  @copyright Copyright (c) 2014, J-PET collaboration 
  *  @file JPetManager.cp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "./JPetManager.h"
#include "../../JPetLoggerInclude.h"
//#include "../JPetAnalysisModule/JPetAnalysisModule.h"
#include <cassert>
#include <ctime>

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
  // write to log about starting
  INFO( "========== Starting processing tasks: " + GetTimeString() + " ==========" );

  UnpackFile();
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

    INFO( "======== Finished processing all tasks: " + GetTimeString() + " ========\n" );
}

void JPetManager::ParseCmdLine(int argc, char** argv){
    fCmdParser.parse(argc, (const char **)argv);
    if (fCmdParser.paramIsSet()){
        fParamManager.readFile(fCmdParser.getParam().c_str());
    }
    if(fCmdParser.fileTypeIsSet()) {
      if (fCmdParser.getFileType()=="hld") {
        fUnpacker.setParams(fCmdParser.getFileName().c_str());
      }
    }
}

JPetManager::~JPetManager()
{
  std::vector<JPetAnalysisModule*>::iterator taskIter;
  for (taskIter = fTasks.begin(); taskIter != fTasks.end(); taskIter++) {
    delete (*taskIter);
    *taskIter = 0;
  }
}

/**
 * @brief Get Input File name stripped off the extension and the suffixes like .tslot.* or .phys.*
 *
 * Example: if the file given on command line was ../file.phys.hit.root, this method will return ../file
 */
const char * JPetManager::getInputFileName() const{
  std::string name = fCmdParser.getFileName().c_str(); 
  // strip suffixes of type .tslot.* and .phys.*
  int pos = name.find(".tslot");
  if( pos == std::string::npos ){
    pos = name.find(".phys");
  }
  if( pos == std::string::npos ){
    pos = name.find(".hld");
  }
  if( pos != std::string::npos ){
    name.erase( pos );
  }
  return name.c_str();
}

/**
 * @brief returns the time TString in the format dd.mm.yyyy HH:MM
 */
TString JPetManager::GetTimeString() const
{
  time_t _tm =time(NULL );
  struct tm * curtime = localtime ( &_tm );
  char buf[100];
  strftime( buf, 100, "%m.%d.%Y %R", curtime);
  
  return TString( buf );
}
