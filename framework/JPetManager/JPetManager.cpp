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
	INFO( "========== Starting processing tasks: " + GetTimeString() + " ==========" );

	vector<string> fileNames = getInputFileNames();

	for(int i = 0; i < fileNames.size(); i++)
	{
		ProcessFromCmdLineArgs(i);
		currentTask = fTasks.begin();
		long long  kNevent = (*currentTask)->getEventNb();
		long long kFirstEvent = 0;
		long long kLastEvent = 0;
		for (currentTask = fTasks.begin(); currentTask != fTasks.end(); currentTask++) {
			prepareCurrentTaskForFile(fileNames[i]);
			setEventBounds(kFirstEvent, kLastEvent, kNevent);
			processEventsInRange(kFirstEvent, kLastEvent);
			(*currentTask)->terminate();
		}
	}

	INFO( "======== Finished processing all tasks: " + GetTimeString() + " ========\n" );
}

///> Initialize and process things based on the command line arguments.
void JPetManager::ProcessFromCmdLineArgs(int fileIndex)
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
			module->setFileName(getInputFileNames()[fileIndex].c_str());
			fTasks.push_front(module);
		} else if (fCmdParser.getFileType() == "hld") {
			fUnpacker.setParams(fCmdParser.getFileNames()[fileIndex].c_str());
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
std::vector<std::string> JPetManager::getInputFileNames() const
{
	std::vector<std::string> fileNames = fCmdParser.getFileNames();
	std::vector<std::string> parsedNames;
	for(int i = 0; i < fileNames.size(); i++){
		std::string name = fileNames[i].c_str();
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
		parsedNames.push_back(name);
	}
	return parsedNames;
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

bool JPetManager::userBoundsAreCorrect(long long numberOfEvents)
{
	return fCmdParser.getLowerEventBound() != -1 &&
			fCmdParser.getHigherEventBound() != -1 &&
			fCmdParser.getHigherEventBound() < numberOfEvents;
}

void JPetManager::manageProgressBar(long long done, long long end)
{
	if (fIsProgressBarEnabled) {
		printf("\r[%6.4f% %]", setProgressBar(done, end));
	}
}

void JPetManager::processEventsInRange(long long begin, long long end)
{
	for (long long i = begin; i <= end; i++)
	{
		manageProgressBar(i, end);
		(*currentTask)->exec();
	}
}

void JPetManager::prepareCurrentTaskForFile(const string& file)
{
	(*currentTask)->createInputObjects( file.c_str() ); /// readers
	(*currentTask)->createOutputObjects( file.c_str() ); /// writers + histograms
}

void JPetManager::setEventBounds(long long& begin, long long& end, long long& eventCount)
{
	if (userBoundsAreCorrect(eventCount) && currentTask == fTasks.begin())
	{
		begin = fCmdParser.getLowerEventBound();
		end = fCmdParser.getHigherEventBound();
		eventCount = end - begin + 1;
	}
	else
	{
		eventCount = (*currentTask)->getEventNb();
		begin = 0;
		end = eventCount - 1;
	}
}
