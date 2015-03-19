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
#include "../JPetRecoSignal/JPetRecoSignal.h"
#include "../JPetPhysSignal/JPetPhysSignal.h"
#include "../JPetManager/JPetManager.h"
#include "../JPetParamBank/JPetParamBank.h"
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

int JPetScopeModule::readFromConfig (const char* fmt, ...) {

  va_list args;
  va_start (args, fmt);

  string buf;

  getline (fConfigFile, buf);
  while (fConfigFile.good() && buf.size() < 2 ) getline(fConfigFile, buf);
  if (!fConfigFile.good()) {va_end(args); return -1;}

  //buf.erase(0, to_erase);
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

  if (readFromConfig("%*2c %d %s", &(fConfig.pm1), cbuf) <= 0) break;
  fConfig.file1 = string(cbuf);

  if (readFromConfig("%*2c %d %s", &(fConfig.pm2), cbuf) <= 0) break;
  fConfig.file2 = string(cbuf);

  if (readFromConfig("%*2c %d %s", &(fConfig.pm3), cbuf) <= 0) break;
  fConfig.file3 = string(cbuf);

  if (readFromConfig("%*2c %d %s", &(fConfig.pm4), cbuf) <= 0) break;
  fConfig.file4 = string(cbuf);

  if (readFromConfig("%*5c %d", &(fConfig.scin1)) <= 0) break;

  if (readFromConfig("%*5c %d", &(fConfig.scin2)) <= 0) break;

  if (readFromConfig("%s", cbuf) <= 0) break;
  data_dir = string(cbuf);

  while (true) {
    a = 0;
    b = 0;
    c = 0;
    int d = readFromConfig("%d %d %d", &a, &b, &c);
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

  //Create ParamBank
  JPetPM pm1;
  JPetPM pm2;
  JPetPM pm3;
  JPetPM pm4;
  pm1.setID(fConfig.pm1);
  pm2.setID(fConfig.pm2);
  pm3.setID(fConfig.pm3);
  pm4.setID(fConfig.pm4);

  JPetScin scin1;
  JPetScin scin2;
  scin1.setID(fConfig.scin1);
  scin2.setID(fConfig.scin2);

  fParamBank = new JPetParamBank();
  fParamBank->addPM(pm1);
  fParamBank->addPM(pm2);
  fParamBank->addPM(pm3);
  fParamBank->addPM(pm4);
  fParamBank->addScintillator(scin1);
  fParamBank->addScintillator(scin2);

  fConfig.ppm1   = &(fParamBank->getPM(0));
  fConfig.ppm2   = &(fParamBank->getPM(1));
  fConfig.ppm3   = &(fParamBank->getPM(2));
  fConfig.ppm4   = &(fParamBank->getPM(3));
  fConfig.pscin1 = &(fParamBank->getScintillator(0));
  fConfig.pscin2 = &(fParamBank->getScintillator(1));

  fConfig.ppm1->setScin(*(fConfig.pscin1));
  fConfig.ppm2->setScin(*(fConfig.pscin1));
  fConfig.ppm3->setScin(*(fConfig.pscin2));
  fConfig.ppm4->setScin(*(fConfig.pscin2));


  // Add oscilloscope files
  for (set<int>::iterator it = fCollPositions.begin(); it != fCollPositions.end(); ++it) {
    string starting_loc  = cfg_dir;
           starting_loc += "/";
           starting_loc += data_dir;
	   starting_loc += "/";
	   starting_loc += to_string (*it);

    path current_dir(starting_loc);
    boost::regex pattern(Form("%s_\\d*.txt", fConfig.file1.c_str()));
    
    if (exists(current_dir))
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
    else {
      string msg  = "Directory: \"";
             msg += current_dir.string();
             msg += "\" does not exist.";
      ERROR(msg.c_str());
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
    fWriter->writeObject(fParamBank, "ParamBank");
  }
}

void JPetScopeModule::exec() {  
  
  while (fIt != fFiles.end()) {
    
    if ((*fIt).first != fCurrentPosition) createOutputObjects();

    JPetPhysSignal psig1, psig2, psig3, psig4;
    JPetHit hit1, hit2;
    
    string osc_file = (*fIt).second;
    string filename;

    int tslot_index;
    sscanf(path(osc_file).filename().string().c_str(), "%*3s %d", &tslot_index);
    
    INFO (Form("Processing file: %s", osc_file.c_str()));
    JPetRecoSignal& rsig1 = fReader.generateSignal(osc_file.c_str());
    rsig1.setPM(*(fConfig.ppm1));
    rsig1.setTSlotIndex(tslot_index);
    psig1.setRecoSignal(rsig1);
    
    filename = path((*fIt).second).filename().string();
    filename[1] = (fConfig.file2)[1];
    osc_file = path((*fIt).second).parent_path().string();
    osc_file+= "/";
    osc_file+= filename;

    INFO (Form("Processing file: %s", osc_file.c_str()));   
    JPetRecoSignal& rsig2 = fReader.generateSignal(osc_file.c_str());
    rsig2.setPM(*(fConfig.ppm2));
    rsig2.setTSlotIndex(tslot_index);
    psig2.setRecoSignal(rsig2);
    
    filename = path((*fIt).second).filename().string();
    filename[1] = (fConfig.file3)[1];
    osc_file = path((*fIt).second).parent_path().string();
    osc_file+= "/";
    osc_file+= filename;

    INFO (Form("Processing file: %s", osc_file.c_str()));   
    JPetRecoSignal& rsig3 = fReader.generateSignal(osc_file.c_str());
    rsig3.setPM(*(fConfig.ppm3));
    rsig3.setTSlotIndex(tslot_index);
    psig3.setRecoSignal(rsig3);

    
    filename = path((*fIt).second).filename().string();
    filename[1] = (fConfig.file4)[1];
    osc_file  = path((*fIt).second).parent_path().string();
    osc_file += "/";
    osc_file += filename;

    INFO (Form("Processing file: %s", osc_file.c_str())); 
    JPetRecoSignal& rsig4 = fReader.generateSignal(osc_file.c_str());
    rsig4.setPM(*(fConfig.ppm4));
    rsig4.setTSlotIndex(tslot_index);
    psig4.setRecoSignal(rsig4);
    
    hit1.setSignals(psig1, psig2);
    hit1.setScinID(fConfig.scin1);

    hit2.setSignals(psig3, psig4);
    hit2.setScinID(fConfig.scin2);

    JPetLOR event;

    event.setHits(hit1, hit2);

    fWriter->write(event);

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
