#include "JPetParamManager.h"

using namespace std;

void JPetParamManager::readFile(const char * file_name){
	assert(file_name != NULL);
	
	string line;
	
	ifstream file(file_name);
	if( ! file.is_open() ){
		ERROR("No such file!");
		return;
	}
	
	/*while ( !file.eof() ){
		int trb = 0, scin = 0;
		
		getline(file, line);
		istringstream iss(line);
		
		iss >> trb;
		iss >> scin;
		fTRBNumbers.push_back(trb);
		fScinNumbers.push_back(scin);
	}*/
}

bool JPetParamManager::setWriter(JPetWriter *writer)
{
  if(writer != NULL)
  {
    fWriter = writer;
    return true;
  }
  return false;
}

bool JPetParamManager::setReader(JPetReader *reader)
{
  if(reader != NULL)
  {
    fReader = reader;
    return true;
  }
  return false;
}

void JPetParamManager::addScintillator(JPetScin &scintillator)
{
  fScintillators.push_back(&scintillator);
}

std::vector<JPetScin*> JPetParamManager::getScintillators()
{
  return fScintillators;
}

JPetScin* JPetParamManager::getScintillator(int i)
{
  if(i < fScintillators.size())
  {
    return fScintillators.at(i);
  }
  return NULL;
}

void JPetParamManager::addPM(JPetPM &pm)
{
  fPMs.push_back(&pm);
}

std::vector<JPetPM*> JPetParamManager::getPMs()
{
  return fPMs;
}

JPetPM* JPetParamManager::getPM(int i)
{
  if(i < fPMs.size())
  {
    return fPMs.at(i);
  }
  return NULL;
}

void JPetParamManager::addKB(JPetKB &kb)
{
  fKBs.push_back(&kb);
}

std::vector<JPetKB*> JPetParamManager::getKB()
{
  return fKBs;
}

JPetKB* JPetParamManager::getKB(int i)
{
  if(i < fKBs.size())
  {
    return fKBs.at(i);
  }
  return NULL;
}

void JPetParamManager::addTRB(JPetTRB &trb)
{
  fTRBs.push_back(&trb);
}

std::vector<JPetTRB*> JPetParamManager::getTRB()
{
  return fTRBs;
}

JPetTRB* JPetParamManager::getTRB(int i)
{
  if(i < fTRBs.size())
  {
    return fTRBs.at(i);
  }
  return NULL;
}

void JPetParamManager::setTOMB(JPetTOMB &tomb)
{
  fTOMB = &tomb;
}

JPetTOMB* JPetParamManager::getTOMB()
{
  return fTOMB;
}

bool JPetParamManager::writerAllContainers(const char *fileName)
{
  if(fWriter != NULL)
  {
    // TODO work out WriteObject() in JPetWriter
    // Scin
    //for(std::vector<JPetScin*>::iterator it = fScintillators.begin() ; it != fScintillators.end(); ++it)
      //fWriter->WriteObject(it, fileName);
    // PM
    //for(std::vector<JPetPM*>::iterator it = fPMs.begin() ; it != fPMs.end(); ++it)
      //fWriter->WriteObject(it, fileName);
    // KBs
    //for(std::vector<JPetKB*>::iterator it = fKBs.begin() ; it != fKBs.end(); ++it)
      //fWriter->WriteObject(it, fileName);
    // TRBs
    //for(std::vector<JPetTRB*>::iterator it = fTRBs.begin() ; it != fTRBs.end(); ++it)
      //fWriter->WriteObject(it, fileName);
    // TOMB
    //fWriter->Write(fTOMB);
    
    return true;
  }
  return false;
}

bool JPetParamManager::readAllContainers(const char *fileName)
{
  if(fReader != NULL)
  {
    //fReader->ReadData();
    return true;
  }
  return false;
}
