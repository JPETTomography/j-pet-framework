#include "./JPetScopeModule.h"

#include <cassert>
#include <string>

#include "boost/regex.hpp"
#include "boost/filesystem.hpp"

#include <TSystem.h>
#include <TApplication.h>
#include <TCanvas.h>

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetSignal/JPetSignal.h"
#include "../JPetManager/JPetManager.h"

using namespace std;
using namespace boost::filesystem;

ClassImp(JPetScopeModule);

static set <string> :: iterator fIt;

JPetScopeModule::JPetScopeModule(): JPetAnalysisModule() {
  gSystem->Load("libTree");
}

JPetScopeModule::JPetScopeModule(const char* name, const char* title): JPetAnalysisModule(name, title) {
  gSystem->Load("libTree");
}

JPetScopeModule::~JPetScopeModule() {
  if (fWriter != NULL) delete fWriter;
}

void JPetScopeModule::createInputObjects(const char* inputFilename)
{
  INFO( Form("Starting %s.", GetName() ) );
  
  fConfigFile.open(fInFilename);
  if (!fConfigFile.is_open()) {
    ERROR("Cannot open config file. Exiting");
    exit(-1);
  }
  
  string buf, starting_loc = path(fInFilename).parent_path().string();
  char cbuf[3];
  //int p1, p2, p3, p4, s1, s2, coll;

  // Read configuration data 
  for (int i = 0; i<1; ++i){  
  getline(fConfigFile, buf);

  while (fConfigFile.good() && buf.size() < 2) getline(fConfigFile, buf);
  if (!fConfigFile.good()) break;

  buf.erase(0,2);
  sscanf(buf.c_str(), "%d %s", &(fConfig.pm1), cbuf);
  fConfig.file1 = string(cbuf);


  getline(fConfigFile, buf);
  
  while (fConfigFile.good() && buf.size() < 2) getline(fConfigFile, buf);
  if (!fConfigFile.good()) break;

  buf.erase(0,2);
  sscanf(buf.c_str(), "%d %s", &(fConfig.pm2), cbuf);
  fConfig.file2 = string(cbuf);


  getline(fConfigFile, buf);

  while (fConfigFile.good() && buf.size() < 2) getline(fConfigFile, buf);
  if (!fConfigFile.good()) break;

  buf.erase(0,2);
  sscanf(buf.c_str(), "%d %s", &(fConfig.pm3), cbuf);
  fConfig.file3 = string(cbuf);


  getline(fConfigFile, buf);

  while (fConfigFile.good() && buf.size() < 2) getline(fConfigFile, buf);
  if (!fConfigFile.good()) break;

  buf.erase(0,2);
  sscanf(buf.c_str(), "%d %s", &(fConfig.pm4), cbuf);
  fConfig.file4 = string(cbuf);


  getline(fConfigFile, buf);

  while (fConfigFile.good() && buf.size() < 2) getline(fConfigFile, buf);
  if (!fConfigFile.good()) break;

  buf.erase(0,5);
  sscanf(buf.c_str(), "%d", &(fConfig.scin1));


  getline(fConfigFile, buf);

  while (fConfigFile.good() && buf.size() < 2) getline(fConfigFile, buf);
  if (!fConfigFile.good()) break;

  buf.erase(0,5);
  sscanf(buf.c_str(), "%d", &(fConfig.scin2));

  fConfigFile.close();
  }

  // Add oscilloscope files
  
  path current_dir(starting_loc.empty() ? starting_loc : ".");
  boost::regex pattern("C\\d_\\d*.txt");

  for (recursive_directory_iterator iter(current_dir), end; iter != end; ++iter) {
    string name = iter->path().leaf().string();
    string dir;
    if (regex_match(name, pattern)) {
      name[1] = (fConfig.file1)[1];
      dir = iter->path().parent_path().string();
      dir += "/";
      dir += name;
      fFiles.insert(dir);
    }
  }

  fIt = fFiles.begin();

}

void JPetScopeModule::createOutputObjects(const char* outputFilename) {
  fWriter = new JPetWriter(fOutFilename);
}

void JPetScopeModule::exec() {  
  
  if (fIt != fFiles.end()) {
    
    string osc_file = *fIt;
    string filename;
    
    fReader.setPMID(fConfig.pm1);

    JPetSignal* sig1 = fReader.generateSignal(osc_file.c_str());
                sig1->setPMID(fConfig.pm1);
    
    filename = path(*fIt).filename().string();
    filename[1] = (fConfig.file2)[1];
    osc_file = path(*fIt).parent_path().string();
    osc_file+= "/";
    osc_file+= filename;
    
    fReader.setPMID(fConfig.pm2);

    JPetSignal* sig2 = fReader.generateSignal(osc_file.c_str());
                sig2->setPMID(fConfig.pm2);
    
    filename = path(*fIt).filename().string();
    filename[1] = (fConfig.file3)[1];
    osc_file = path(*fIt).parent_path().string();
    osc_file+= "/";
    osc_file+= filename;

    
    fReader.setPMID(fConfig.pm3);

    JPetSignal* sig3 = fReader.generateSignal(osc_file.c_str());
                sig3->setPMID(fConfig.pm3);
    
    filename = path(*fIt).filename().string();
    filename[1] = (fConfig.file4)[1];
    osc_file = path(*fIt).parent_path().string();
    osc_file+= "/";
    osc_file+= filename;

  
    fReader.setPMID(fConfig.pm4);

    JPetSignal* sig4 = fReader.generateSignal(osc_file.c_str());
                sig4->setPMID(fConfig.pm4);

    JPetHit* hit1 = new JPetHit();
    JPetHit* hit2 = new JPetHit();

    hit1->setSignals(*sig1, *sig2);
    hit1->setScinID(fConfig.scin1);

    hit2->setSignals(*sig3, *sig4);
    hit2->setScinID(fConfig.scin2);

    JPetEvent* event = new JPetEvent();

    event->setHits(*hit1, *hit2);

    fWriter->Write(*event);

    delete sig1;
    delete sig2;
    delete sig3;
    delete sig4;
    delete hit1;
    delete hit2;
    delete event;

    ++fIt;

  }
}

void JPetScopeModule::terminate() {

  fWriter->CloseFile();
}


void JPetScopeModule::setFileName(const char* name)
{
  fInFilename = TString(name);
  fOutFilename = TString(name);
  fOutFilename.ReplaceAll(".cfg", "");
  fOutFilename.Append(".scope.eve.root");
}
