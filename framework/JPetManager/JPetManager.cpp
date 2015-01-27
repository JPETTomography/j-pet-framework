/**
  *  @copyright Copyright (c) 2014, J-PET collaboration
  *  @file JPetManager.cp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "./JPetManager.h"

#include <cassert>
#include <ctime>
#include <string>

#include "../../JPetLoggerInclude.h"
#include "../JPetScopeModule/JPetScopeModule.h"

//ClassImp(JPetManager);

JPetManager& JPetManager::GetManager()
{
  static JPetManager instance;
  return instance;
}

JPetManager::JPetManager(): TNamed("JPetMainManager", "JPetMainManager"), fIsProgressBarEnabled(false)
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

  if (fCmdParser.IsFileTypeSet()) {
    if (fCmdParser.getFileType() == "scope") {
      JPetScopeModule* module = new JPetScopeModule("JPetScopeModule", "Process Oscilloscope ASCII data into JPetEvent structures.");
      module->setFileName(getInputFileName().c_str());
      fTasks.push_front(module);
    } else {
      UnpackFile();
    }
  }

  JPetWriter* currentWriter = 0;
  std::list<JPetAnalysisModule*>::iterator taskIter;
  // pseudo-input container
  long long  kNevent = 0;
  for (taskIter = fTasks.begin(); taskIter != fTasks.end(); taskIter++) {
    (*taskIter)->createInputObjects( getInputFileName().c_str() ); /// readers
    (*taskIter)->createOutputObjects( getInputFileName().c_str() ); /// writers + histograms
    kNevent = (*taskIter)->getEventNb();
    for (long long i = 0; i < kNevent; i++) {
      if(fIsProgressBarEnabled)
      {
	std::cout << "Progressbar: " << setProgressBar(i, kNevent) << " %" << std::endl;
      }
      (*taskIter)->exec();
    }
    (*taskIter)->terminate();
  }

  INFO( "======== Finished processing all tasks: " + GetTimeString() + " ========\n" );
}

void JPetManager::ParseCmdLine(int argc, char** argv)
{
  fCmdParser.parse(argc, (const char**)argv);

  if (fCmdParser.isRunNumberSet()) { /// we should connect to the database
    fParamManager.getParametersFromDatabase(fCmdParser.getRunNumber()); /// @todo some error handling
  }
  if (fCmdParser.IsFileTypeSet()) {
    if (fCmdParser.getFileType() == "hld") {
      fUnpacker.setParams(fCmdParser.getFileName().c_str());
    }
  }
  if (fCmdParser.isProgressBarSet()) {
    fIsProgressBarEnabled = true;
  }
}

int JPetManager::getRunNumber() const
{
  if (fCmdParser.isRunNumberSet()) {
    return fCmdParser.getRunNumber();
  }
  return -1;
}

JPetManager::~JPetManager()
{
  std::list<JPetAnalysisModule*>::iterator taskIter;
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
std::string JPetManager::getInputFileName() const
{
  std::string name = fCmdParser.getFileName().c_str();
  // strip suffixes of type .tslot.* and .phys.*
  int pos = name.find(".tslot");
  if ( pos == std::string::npos ) {
    pos = name.find(".phys");
  }
  if ( pos == std::string::npos ) {
    pos = name.find(".hld");
  }
  if ( pos == std::string::npos ) {
    pos = name.find(".root");
  }
  if ( pos != std::string::npos ) {
    name.erase( pos );
  }
  return name;
}

/**
 * @brief returns the time TString in the format dd.mm.yyyy HH:MM
 */
TString JPetManager::GetTimeString() const
{
  time_t _tm = time(NULL );
  struct tm* curtime = localtime ( &_tm );
  char buf[100];
  strftime( buf, 100, "%m.%d.%Y %R", curtime);

  return TString( buf );
}

float JPetManager::setProgressBar(int currentEventNumber, int numberOfEvents)
{
  return ( ((float)currentEventNumber) / numberOfEvents ) * 100;
}
