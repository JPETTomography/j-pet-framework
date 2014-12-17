#include "./JPetScopeModule.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <utility>

#include "boost/regex.hpp"
#include "boost/filesystem.hpp"

#include <TSystem.h>
#include <TApplication.h>
#include <TCanvas.h>

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetSignal/JPetSignal.h"
#include "../JPetManager/JPetManager.h"
#include "../JPetTreeHeader/JPetTreeHeader.h"

using namespace std;
using namespace boost::filesystem;

ClassImp(JPetScopeModule);

static multimap <int, string> :: iterator fIt;

JPetScopeModule::JPetScopeModule(): JPetAnalysisModule() {
  gSystem->Load("libTree");
}

JPetScopeModule::JPetScopeModule(const char* name, const char* title): JPetAnalysisModule(name, title) {
  gSystem->Load("libTree");
}

JPetScopeModule::~JPetScopeModule() {
  if (fWriter != 0) {
    delete fWriter;
    fWriter = 0;
  }
}

int JPetScopeModule::readFromConfig (int to_erase, const char* fmt, ...) {

  va_list args;
  va_start (args, fmt);

  string buf;

  getline (fConfigFile, buf);
  while (fConfigFile.good() && buf.size() < 2 ) getline(fConfigFile, buf);
  if (!fConfigFile.good()) {va_end(args); return -1;}

  buf.erase(0, to_erase);
  int ret = vsscanf(buf.c_str(), fmt, args);

  va_end(args);

  return ret;
}

void JPetScopeModule::createInputObjects(const char* inputFilename)
{
  INFO( Form("Starting %s.", GetName() ) );
  
  fConfigFile.open(fInFilename);
  if (!fConfigFile.is_open()) {
    ERROR("Cannot open config file. Exiting");
    exit(-1);
  }
  
  string buf;
  string cfg_dir = path(fInFilename).parent_path().string();
  string data_dir;
  char cbuf[256];
  int a, b, c;
  //int p1, p2, p3, p4, s1, s2, coll;

  // Read configuration data 
  for (int i = 0; i<1; ++i){  

  if (readFromConfig(2, "%d %s", &(fConfig.pm1), cbuf) <= 0) break;
  fConfig.file1 = string(cbuf);

  if (readFromConfig(2, "%d %s", &(fConfig.pm2), cbuf) <= 0) break;
  fConfig.file2 = string(cbuf);

  if (readFromConfig(2, "%d %s", &(fConfig.pm3), cbuf) <= 0) break;
  fConfig.file3 = string(cbuf);

  if (readFromConfig(2, "%d %s", &(fConfig.pm4), cbuf) <= 0) break;
  fConfig.file4 = string(cbuf);

  if (readFromConfig(5, "%d", &(fConfig.scin1)) <= 0) break;

  if (readFromConfig(5, "%d", &(fConfig.scin2)) <= 0) break;

  if (readFromConfig(0, "%s", cbuf) <= 0) break;
  data_dir = string(cbuf);

  while (true) {
    a = 0;
    b = 0;
    c = 0;
    int d = readFromConfig(0, "%d %d %d", &a, &b, &c);
    if (d <= 0) break;
    else if (d == 1) {
      // Add single position
      fCollPositions.insert(a);
    }
    else {
      if (d == 2) {c = 1;}
      // Add multiple positions
      for (int j = a; j <= b; j += c) {
        fCollPositions.insert(j);
      }
    }
  }

  }

  // Add oscilloscope files
  for (set<int>::iterator it = fCollPositions.begin(); it != fCollPositions.end(); ++it) {
    string starting_loc  = cfg_dir;
           starting_loc += "/";
           starting_loc += data_dir;
	   starting_loc += "/";
	   starting_loc += to_string (*it);

    path current_dir(starting_loc);
    boost::regex pattern(Form("%s_\\d*.txt", fConfig.file1.c_str()));

    for (recursive_directory_iterator iter(current_dir), end; iter != end; ++iter) {
      string name = iter->path().leaf().string();
      string dir;
      if (regex_match(name, pattern)) {
        name[1] = (fConfig.file1)[1];
        dir = iter->path().parent_path().string();
        dir += "/";
        dir += name;
	int tpos = *it;
        fFiles.insert(pair<int, string> (tpos, dir));
      }
    }
  }
  fIt = fFiles.begin();
  printFiles();
  fWriter = 0;
}

void JPetScopeModule::createOutputObjects(const char* outputFilename) {
  
  if (fFiles.empty()) {
    ERROR("No files for processing.");
  }
  else {
    fCurrentPosition = (*fIt).first;
    terminate();

    INFO (Form("Creating root file for position %d", fCurrentPosition));

    string out_fn(fOutFilename.Data());
    int last_dot = out_fn.find_last_of(".");

    string out_fn2  = out_fn.substr(0,last_dot+1);
           out_fn2 += to_string(fCurrentPosition);
           out_fn2 += out_fn.substr(last_dot);

    fWriter = new JPetWriter(out_fn2.c_str());

    fHeader = new JPetTreeHeader(JPetManager::GetManager().getRunNumber());
    fHeader->setBaseFileName(JPetManager::GetManager().getInputFileName().c_str());
    fHeader->addStageInfo(GetName(), GetTitle(), MODULE_VERSION, JPetManager::GetManager().GetTimeString());
    fHeader->setSourcePosition(fCurrentPosition);

    fWriter->writeHeader(fHeader);
  }
}

void JPetScopeModule::exec() {  
  
  while (fIt != fFiles.end()) {
    
    if ((*fIt).first != fCurrentPosition) createOutputObjects();
    
    string osc_file = (*fIt).second;
    string filename;
    
    INFO (Form("Processing file: %s", osc_file.c_str()));
    fReader.setPMID(fConfig.pm1);
    JPetSignal* sig1 = fReader.generateSignal(osc_file.c_str());
    if(sig1 == 0) break;
    sig1->setPMID(fConfig.pm1);
    
    filename = path((*fIt).second).filename().string();
    filename[1] = (fConfig.file2)[1];
    osc_file = path((*fIt).second).parent_path().string();
    osc_file+= "/";
    osc_file+= filename;

    INFO (Form("Processing file: %s", osc_file.c_str()));   
    fReader.setPMID(fConfig.pm2);
    JPetSignal* sig2 = fReader.generateSignal(osc_file.c_str());
    if(sig2 == 0) break;
    sig2->setPMID(fConfig.pm2);
    
    filename = path((*fIt).second).filename().string();
    filename[1] = (fConfig.file3)[1];
    osc_file = path((*fIt).second).parent_path().string();
    osc_file+= "/";
    osc_file+= filename;

    INFO (Form("Processing file: %s", osc_file.c_str()));   
    fReader.setPMID(fConfig.pm3);
    JPetSignal* sig3 = fReader.generateSignal(osc_file.c_str());
    if(sig3 == 0) break;
    sig3->setPMID(fConfig.pm3);
    
    filename = path((*fIt).second).filename().string();
    filename[1] = (fConfig.file4)[1];
    osc_file  = path((*fIt).second).parent_path().string();
    osc_file += "/";
    osc_file += filename;

    INFO (Form("Processing file: %s", osc_file.c_str())); 
    fReader.setPMID(fConfig.pm4);
    JPetSignal* sig4 = fReader.generateSignal(osc_file.c_str());
    if(sig4 == 0) break;
    sig4->setPMID(fConfig.pm4);

    JPetHit* hit1 = new JPetHit();
    JPetHit* hit2 = new JPetHit();

    hit1->setSignals(*sig1, *sig2);
    hit1->setScinID(fConfig.scin1);

    hit2->setSignals(*sig3, *sig4);
    hit2->setScinID(fConfig.scin2);

    JPetEvent* event = new JPetEvent();

    event->setHits(*hit1, *hit2);

    fWriter->write(*event);

    delete sig1;
    delete sig2;
    delete sig3;
    delete sig4;
    delete hit1;
    delete hit2;
    delete event;

    break;
  }
  fIt++;
}

void JPetScopeModule::terminate() {
//  assert(fWriter);
  if(fWriter)
  if(fWriter->isOpen()) {
    //std::cout <<"in JPetScope terminate()" <<std::endl;
    fWriter->closeFile();
    delete fWriter;
    fWriter = 0;
  }
}

void JPetScopeModule::printCollPositions () {
  INFO ("Printing all collimator positions:");
  for (set<int>::iterator iter = fCollPositions.begin(); iter != fCollPositions.end(); ++iter) {
    INFO (Form("collimator position: %d", *iter));
  }
}

void JPetScopeModule::printFiles () {
  INFO ("Printing all files:");
  for (map<int, string>::iterator iter = fFiles.begin(); iter != fFiles.end(); ++iter) {
    INFO (Form("%3d %s", (*iter).first, (*iter).second.c_str()));
  }
}

void JPetScopeModule::setFileName(const char* name)
{
  fInFilename = TString(name);
  fOutFilename = TString(name);
  fOutFilename.ReplaceAll(".cfg", "");
  fOutFilename.Append(".scope.eve.root");
}
