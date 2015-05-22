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
#include "../JPetScopeReader/JPetScopeReader.h"

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
  ProcessFromCmdLineArgs();
  JPetWriter* currentWriter = 0;
  std::list<JPetAnalysisModule*>::iterator taskIter;
  // pseudo-input container
  long long  kNevent = 0;
  long long kFirstEvent = 0;
  long long kLastEvent = 0;
  for (taskIter = fTasks.begin(); taskIter != fTasks.end(); taskIter++) {
    (*taskIter)->createInputObjects( getBaseInputFileName().c_str() ); /// readers
    (*taskIter)->createOutputObjects( getBaseInputFileName().c_str() ); /// writers + histograms
    kNevent = (*taskIter)->getEventNb();
    kFirstEvent = 0;
    kLastEvent = kNevent - 1;

    // handle the user-provided range of events to process,
    // but only for the first module to process
    if ( taskIter == fTasks.begin() ) { // only for first module
      if ( fCmdParser.getLowerEventBound() != -1 &&
           fCmdParser.getHigherEventBound() != -1 &&
           fCmdParser.getHigherEventBound() < kNevent) { // only if user provided reasonable bounds
        kFirstEvent = fCmdParser.getLowerEventBound();
        kLastEvent = fCmdParser.getHigherEventBound();
        kNevent = kLastEvent - kFirstEvent + 1;
      }
    }

    for (long long i = kFirstEvent; i <= kLastEvent; i++) {
      if (fIsProgressBarEnabled) {
        printf("\r[%6.4f%% %%]", setProgressBar(i, kNevent));
      }
      (*taskIter)->exec();
    }
    (*taskIter)->terminate();
  }

  INFO( "======== Finished processing all tasks: " + GetTimeString() + " ========\n" );
}

///> Initialize and process things based on the command line arguments.
void JPetManager::ProcessFromCmdLineArgs()
{
  if (fCmdParser.isRunNumberSet()) { /// we should connect to the database
      fParamManager.getParametersFromDatabase(fCmdParser.getRunNumber()); /// @todo some error handling
    }
        
    if (fCmdParser.isProgressBarSet()) {
      fIsProgressBarEnabled = true;
    }
    if (fCmdParser.IsFileTypeSet()) {
      if (fCmdParser.getFileType() == "scope") {
        JPetScopeReader* module = new JPetScopeReader("JPetScopeReader", "Process Oscilloscope ASCII data into JPetRecoSignal structures.");
        module->setFileName(getInputFileName().c_str());
        fTasks.push_front(module);
      } else if (fCmdParser.getFileType() == "hld") {
       fUnpacker.setParams(fCmdParser.getFileName().c_str());
       UnpackFile();
      }
    }


}

void JPetManager::ParseCmdLine(int argc, char** argv)
{
  fCmdParser.parse(argc, (const char**)argv);

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
std::string JPetManager::getBaseInputFileName() const
{
  std::string name = fCmdParser.getFileName().c_str();
  int pos = name.find(".");
  if ( pos != std::string::npos ) {
    name.erase( pos );
  }  
  return name;
}

/**
 * @brief Get full Input File name including extension
 */
std::string JPetManager::getInputFileName() const
{
  return fCmdParser.getFileName().c_str();
}

/**
 * @brief returns the time TString in the format dd.mm.yyyy HH:MM
 */
TString JPetManager::GetTimeString() const
{
  time_t _tm = time(NULL );
  struct tm* curtime = localtime ( &_tm );
  char buf[100];
  strftime( buf, 100, "%d.%m.%Y %R", curtime);

  return TString( buf );
}

float JPetManager::setProgressBar(int currentEventNumber, int numberOfEvents)
{
  return ( ((float)currentEventNumber) / numberOfEvents ) * 100;
}
