#include "./JPetScopeModule.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <utility>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <TSystem.h>
#include <TApplication.h>

#include "../JPetManager/JPetManager.h"
#include "../JPetParamBank/JPetParamBank.h"
#include "../JPetPhysSignal/JPetPhysSignal.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetRecoSignal/JPetRecoSignal.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetScopeReader/JPetScopeReader.h"
#include "../JPetTreeHeader/JPetTreeHeader.h"
#include "../JPetWriter/JPetWriter.h"

#include <iostream>

using namespace std;
using namespace boost::filesystem;
using boost::property_tree::ptree;

ClassImp(JPetScopeModule);

JPetScopeModule::JPetScopeModule(): JPetAnalysisModule(), fEventNb(0), fReader(new JPetScopeReader()), fWriter(nullptr) {
  gSystem->Load("libTree");
}

JPetScopeModule::JPetScopeModule(const char* name, const char* title): JPetAnalysisModule(name, title), fEventNb(0), fReader(new JPetScopeReader()), fWriter(nullptr)  {
  gSystem->Load("libTree");
}

JPetScopeModule::~JPetScopeModule() {

  if (fReader != nullptr) {
    delete fReader;
    fReader = nullptr;
  }

  if (fWriter != nullptr) {
    delete fWriter;
    fWriter = nullptr;
  }

}

void JPetScopeModule::createInputObjects(const char* inputFilename)
{
  INFO( Form("Starting %s.", GetName() ) );

  // Create property tree

  ptree prop_tree;

  // Check file type
  
  string ext = path(fInFilename).extension().string();

  // Read configuration data to property tree
  
  if (ext.compare(".ini") == 0) {
    read_ini(fInFilename.Data(), prop_tree);
  } else if (ext.compare(".info") == 0) {
    read_info(fInFilename.Data(), prop_tree);
  } else if (ext.compare(".json") == 0) {
    read_json(fInFilename.Data(), prop_tree);
  } else if (ext.compare(".xml") == 0) {
    read_xml(fInFilename.Data(), prop_tree);
  } else {
    ERROR("Cannot open config file. Exiting");
    exit(-1); 
  }

  // Fill fConfigs
  
  for (ptree::const_iterator it = prop_tree.begin(); it != prop_tree.end(); ++it) {

    int pmid1, pmid2, pmid3, pmid4;
    int scinid1, scinid2;

    string files_location;

    const ptree& conf_data = it->second;

    pmid1 = conf_data.get("pm1.id", 0);
    pmid2 = conf_data.get("pm2.id", 0);
    pmid3 = conf_data.get("pm3.id", 0);
    pmid4 = conf_data.get("pm4.id", 0);

    scinid1 = conf_data.get("scin1.id", 0);
    scinid2 = conf_data.get("scin2.id", 0);

    files_location = conf_data.get<string>("location");

    // Create ParamBank

    JPetPM pm1;
    JPetPM pm2;
    JPetPM pm3;
    JPetPM pm4;

    JPetScin scin1;
    JPetScin scin2;

    pm1.setID(pmid1);
    pm2.setID(pmid2);
    pm3.setID(pmid3);
    pm4.setID(pmid4);

    scin1.setID(scinid1);
    scin2.setID(scinid2);

    JPetParamBank* param_bank = new JPetParamBank();
    param_bank->addPM(pm1);
    param_bank->addPM(pm2);
    param_bank->addPM(pm3);
    param_bank->addPM(pm4);
    param_bank->addScintillator(scin1);
    param_bank->addScintillator(scin2);

    (param_bank->getPM(0)).setScin(param_bank->getScintillator(0));
    (param_bank->getPM(1)).setScin(param_bank->getScintillator(0));
    (param_bank->getPM(2)).setScin(param_bank->getScintillator(1));
    (param_bank->getPM(3)).setScin(param_bank->getScintillator(1));

    // Fill Configs

    string collimator_function;
    int a, b, c, n;
    BOOST_FOREACH(const ptree::value_type& v, conf_data.get_child("collimator")) {
      collimator_function = v.second.get<string>("positions");
      n = sscanf(collimator_function.c_str(), "%d %d %d", &a, &b, &c);

      if (n > 0) {
        if (n == 1) {b = a; c = 1;}
	if (n == 2) {c = 1;}

	for (int j = a; j <=b; j+= c) {

	  fConfigs.push_back(ScopeConfig());
	  vector <ScopeConfig> :: iterator current_config = fConfigs.end() - 1;

	  // Add config name
	  (*current_config).pName         = it->first;

	  // Add collimator position
	  (*current_config).pCollPosition = j;

	  // Add param bank
	  (*current_config).pParamBank    = param_bank;

	  // Add PMs
	  (*current_config).pPM1          = &(param_bank->getPM(0));
	  (*current_config).pPM2          = &(param_bank->getPM(1));
	  (*current_config).pPM3          = &(param_bank->getPM(2));
	  (*current_config).pPM4          = &(param_bank->getPM(3));

	  // Add Scintillators
	  (*current_config).pScin1        = &(param_bank->getScintillator(0));
	  (*current_config).pScin2        = &(param_bank->getScintillator(1));

	  // Add filename prefixes
	  (*current_config).pPrefix1      = conf_data.get<string>("pm1.prefix");
	  (*current_config).pPrefix2      = conf_data.get<string>("pm2.prefix");
	  (*current_config).pPrefix3      = conf_data.get<string>("pm3.prefix");
	  (*current_config).pPrefix4      = conf_data.get<string>("pm4.prefix");

	  // Add oscilloscope files
	  string starting_loc  = path(fInFilename).parent_path().string();
                 starting_loc += "/";
                 starting_loc += files_location;
	         starting_loc += "/";
	         starting_loc += to_string (j);

          path current_dir(starting_loc);
          boost::regex pattern(Form("%s_\\d*.txt", (*current_config).pPrefix1.c_str()));
	  
	  if (exists(current_dir))
            for (recursive_directory_iterator iter(current_dir), end; iter != end; ++iter) {
              string name = iter->path().leaf().string();
              string dir;
              if (regex_match(name, pattern)) {
                name[1] = ((*current_config).pPrefix1)[1];
                dir = iter->path().parent_path().string();
                dir += "/";
                dir += name;
		(*current_config).pFiles.insert(dir);
              }
            }
            else {
              string msg  = "Directory: \"";
                     msg += current_dir.string();
                     msg += "\" does not exist.";
              ERROR(msg.c_str());
            }
	  
	  // Set Iterator to begining
	  (*current_config).pIter         = (*current_config).pFiles.begin();
	}
      }
    }
  }
  fIter = fConfigs.begin();
  fWriter = nullptr;
  
  fEventNb = 0;
  for (vector <ScopeConfig> :: iterator it = fConfigs.begin(); it != fConfigs.end(); ++it) {
    fEventNb += (*it).pFiles.size();
  }
}

void JPetScopeModule::createOutputObjects(const char* outputFilename) {
  
  if (fConfigs.empty()) {
    ERROR("No files for processing.");
  }
  else {
    terminate();

    INFO (Form("Creating root file for configuration %s and position %d", ((*fIter).pName).c_str(), (*fIter).pCollPosition));

    string out_fn(fOutFilename.Data());
    int last_dot = out_fn.find_last_of(".");

    string out_fn2  = out_fn.substr(0,last_dot+1);
           out_fn2 += (*fIter).pName;
	   out_fn2 += ".";
           out_fn2 += to_string((*fIter).pCollPosition);
           out_fn2 += out_fn.substr(last_dot);

    fWriter = new JPetWriter(out_fn2.c_str());

    fHeader = new JPetTreeHeader(JPetManager::GetManager().getRunNumber());
    fHeader->setBaseFileName(JPetManager::GetManager().getInputFileName().c_str());
    fHeader->addStageInfo(GetName(), GetTitle(), MODULE_VERSION, JPetManager::GetManager().GetTimeString());
    fHeader->setSourcePosition((*fIter).pCollPosition);

    fWriter->writeHeader(fHeader);
    fWriter->writeObject((*fIter).pParamBank, "ParamBank");
  }
}

void JPetScopeModule::exec() {  
  
  while (fIter != fConfigs.end()) {
  while ((*fIter).pIter != (*fIter).pFiles.end()) {

    JPetPhysSignal psig1, psig2, psig3, psig4;
    JPetHit hit1, hit2;
    
    string osc_file = *((*fIter).pIter);
    string filename;

    int tslot_index;
    sscanf(path(osc_file).filename().string().c_str(), "%*3s %d", &tslot_index);
    
    //INFO (Form("Processing file: %s", osc_file.c_str()));
    JPetRecoSignal& rsig1 = fReader->generateSignal(osc_file.c_str());
    rsig1.setPM(*((*fIter).pPM1));
    rsig1.setTSlotIndex(tslot_index);
    psig1.setRecoSignal(rsig1);
    
    filename = path(*((*fIter).pIter)).filename().string();
    filename[1] = ((*fIter).pPrefix2)[1];
    osc_file = path(*((*fIter).pIter)).parent_path().string();
    osc_file+= "/";
    osc_file+= filename;

    //INFO (Form("Processing file: %s", osc_file.c_str()));   
    JPetRecoSignal& rsig2 = fReader->generateSignal(osc_file.c_str());
    rsig2.setPM(*((*fIter).pPM2));
    rsig2.setTSlotIndex(tslot_index);
    psig2.setRecoSignal(rsig2);
    
    filename = path(*((*fIter).pIter)).filename().string();
    filename[1] = ((*fIter).pPrefix3)[1];
    osc_file = path(*((*fIter).pIter)).parent_path().string();
    osc_file+= "/";
    osc_file+= filename;

    //INFO (Form("Processing file: %s", osc_file.c_str()));   
    JPetRecoSignal& rsig3 = fReader->generateSignal(osc_file.c_str());
    rsig3.setPM(*((*fIter).pPM3));
    rsig3.setTSlotIndex(tslot_index);
    psig3.setRecoSignal(rsig3);
    
    filename = path(*((*fIter).pIter)).filename().string();
    filename[1] = ((*fIter).pPrefix4)[1];
    osc_file = path(*((*fIter).pIter)).parent_path().string();
    osc_file+= "/";
    osc_file+= filename;

    //INFO (Form("Processing file: %s", osc_file.c_str())); 
    JPetRecoSignal& rsig4 = fReader->generateSignal(osc_file.c_str());
    rsig4.setPM(*((*fIter).pPM4));
    rsig4.setTSlotIndex(tslot_index);
    psig4.setRecoSignal(rsig4);
    
    hit1.setSignals(psig1, psig2);
    hit1.setScinID((*fIter).pScin1->getID());

    hit2.setSignals(psig3, psig4);
    hit2.setScinID((*fIter).pScin2->getID());

    JPetLOR event;

    event.setHits(hit1, hit2);

    fWriter->write(event);

    break;
  }
  ((*fIter).pIter)++;
  break;
  }
  if((*fIter).pIter == (*fIter).pFiles.end()) {
    fIter++;
    createOutputObjects();
  }
}

void JPetScopeModule::terminate() {
//  assert(fWriter);
  if(fWriter)
  if(fWriter->isOpen()) {
    fWriter->closeFile();
    delete fWriter;
    fWriter = nullptr;
  }
}

void JPetScopeModule::setFileName(const char* name)
{
  fInFilename = TString(name);
  fOutFilename = TString(name);
  fOutFilename.ReplaceAll(".ini", "");
  fOutFilename.ReplaceAll(".info", "");
  fOutFilename.ReplaceAll(".json", "");
  fOutFilename.ReplaceAll(".xml", "");
  fOutFilename.Append(".scope.eve.root");
}
