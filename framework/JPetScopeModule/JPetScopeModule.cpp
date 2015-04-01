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
#include <TCanvas.h>

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetRecoSignal/JPetRecoSignal.h"
#include "../JPetPhysSignal/JPetPhysSignal.h"
#include "../JPetManager/JPetManager.h"
#include "../JPetParamBank/JPetParamBank.h"
#include "../JPetTreeHeader/JPetTreeHeader.h"

#include <iostream>

using namespace std;
using namespace boost::filesystem;
using boost::property_tree::ptree;

//ClassImp(JPetScopeModule);

JPetScopeModule::JPetScopeModule(): JPetAnalysisModule(), fSize(0) {
  gSystem->Load("libTree");
}

JPetScopeModule::JPetScopeModule(const char* name, const char* title): JPetAnalysisModule(name, title), fSize(0) {
  gSystem->Load("libTree");
}

JPetScopeModule::~JPetScopeModule() {
  if (fWriter != 0) {
    delete fWriter;
    fWriter = 0;
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
    
    configStruct* conf = new configStruct();
    conf->pname = it->first;

    const ptree& conf_data = it->second;

    pmid1 = conf_data.get("pm1.id", 0);
    pmid2 = conf_data.get("pm2.id", 0);
    pmid3 = conf_data.get("pm3.id", 0);
    pmid4 = conf_data.get("pm4.id", 0);

    scinid1 = conf_data.get("scin1.id", 0);
    scinid2 = conf_data.get("scin2.id", 0);

    files_location = conf_data.get<string>("location");

    string collimator_function;
    set <int> collimator_positions;
    int a, b, c, n;
    BOOST_FOREACH(const ptree::value_type& v, conf_data.get_child("collimator")) {
      collimator_function = v.second.get<string>("positions");
      n = sscanf(collimator_function.c_str(), "%d %d %d", &a, &b, &c);
      
      if (n == 1) {
        // Add single position
        collimator_positions.insert(a);
      }
      else {
        if (n == 2) {c = 1;}
        // Add multiple positions
        for (int j = a; j <= b; j += c) {
          collimator_positions.insert(j);
        }
      }
    }

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

    conf->pparambank = new JPetParamBank();
    conf->pparambank->addPM(pm1);
    conf->pparambank->addPM(pm2);
    conf->pparambank->addPM(pm3);
    conf->pparambank->addPM(pm4);
    conf->pparambank->addScintillator(scin1);
    conf->pparambank->addScintillator(scin2);

    conf->ppm1   = &(conf->pparambank->getPM(0));
    conf->ppm2   = &(conf->pparambank->getPM(1));
    conf->ppm3   = &(conf->pparambank->getPM(2));
    conf->ppm4   = &(conf->pparambank->getPM(3));
    conf->pscin1 = &(conf->pparambank->getScintillator(0));
    conf->pscin2 = &(conf->pparambank->getScintillator(1));

    conf->ppm1->setScin(*(conf->pscin1));
    conf->ppm2->setScin(*(conf->pscin1));
    conf->ppm3->setScin(*(conf->pscin2));
    conf->ppm4->setScin(*(conf->pscin2));

    // Add filename prefixes
    
    conf->ppref1 = conf_data.get<string>("pm1.prefix");
    conf->ppref2 = conf_data.get<string>("pm2.prefix");
    conf->ppref3 = conf_data.get<string>("pm3.prefix");
    conf->ppref4 = conf_data.get<string>("pm4.prefix");
  
    // Add oscilloscope files
    for (set<int>::iterator it = collimator_positions.begin(); it != collimator_positions.end(); ++it) {
      string starting_loc  = path(fInFilename).parent_path().string();
             starting_loc += "/";
             starting_loc += files_location;
	     starting_loc += "/";
	     starting_loc += to_string (*it);

      path current_dir(starting_loc);
      boost::regex pattern(Form("%s_\\d*.txt", conf->ppref1.c_str()));
    
      if (exists(current_dir))
      for (recursive_directory_iterator iter(current_dir), end; iter != end; ++iter) {
        string name = iter->path().leaf().string();
        string dir;
        if (regex_match(name, pattern)) {
          name[1] = (conf->ppref1)[1];
          dir = iter->path().parent_path().string();
          dir += "/";
          dir += name;
	  int tpos = *it;
          conf->pfiles.insert(pair<int, string> (tpos, dir));
        }
      }
      else {
        string msg  = "Directory: \"";
               msg += current_dir.string();
               msg += "\" does not exist.";
        ERROR(msg.c_str());
      }
    }
    conf->pit = conf->pfiles.begin();
    fConfigs.push_back(conf);

  }
  fIt = fConfigs.begin();
  fWriter = 0;
  
  fSize = 0;
  for (vector <configStruct*> :: iterator it = fConfigs.begin(); it != fConfigs.end(); ++it) {
    fSize += (*it)->pfiles.size();
  }
}

void JPetScopeModule::createOutputObjects(const char* outputFilename) {
  cout << "calling this fancy method." << endl;
  if (fConfigs.empty()) {
    ERROR("No files for processing.");
  }
  else {
    fCurrentPosition = (*((*fIt)->pit)).first;
    terminate();

    INFO (Form("Creating root file for configuration %s and position %d", ((*fIt)->pname).c_str(), fCurrentPosition));

    string out_fn(fOutFilename.Data());
    int last_dot = out_fn.find_last_of(".");

    string out_fn2  = out_fn.substr(0,last_dot+1);
           out_fn2 += (*fIt)->pname;
	   out_fn2 += ".";
           out_fn2 += to_string(fCurrentPosition);
           out_fn2 += out_fn.substr(last_dot);

    fWriter = new JPetWriter(out_fn2.c_str());

    fHeader = new JPetTreeHeader(JPetManager::GetManager().getRunNumber());
    fHeader->setBaseFileName(JPetManager::GetManager().getInputFileName().c_str());
    fHeader->addStageInfo(GetName(), GetTitle(), MODULE_VERSION, JPetManager::GetManager().GetTimeString());
    fHeader->setSourcePosition(fCurrentPosition);

    fWriter->writeHeader(fHeader);
    fWriter->writeObject((*fIt)->pparambank, "ParamBank");
  }
}

void JPetScopeModule::exec() {  
  
  while (fIt != fConfigs.end()) {
  while ((*fIt)->pit != (*fIt)->pfiles.end()) {
    
    if ( (*((*fIt)->pit)).first != fCurrentPosition ) createOutputObjects();

    JPetPhysSignal psig1, psig2, psig3, psig4;
    JPetHit hit1, hit2;
    
    string osc_file = (*((*fIt)->pit)).second;
    string filename;

    int tslot_index;
    sscanf(path(osc_file).filename().string().c_str(), "%*3s %d", &tslot_index);
    
    //INFO (Form("Processing file: %s", osc_file.c_str()));
    JPetRecoSignal& rsig1 = fReader.generateSignal(osc_file.c_str());
    rsig1.setPM(*((*fIt)->ppm1));
    rsig1.setTSlotIndex(tslot_index);
    psig1.setRecoSignal(rsig1);
    
    filename = path((*((*fIt)->pit)).second).filename().string();
    filename[1] = ((*fIt)->ppref2)[1];
    osc_file = path((*((*fIt)->pit)).second).parent_path().string();
    osc_file+= "/";
    osc_file+= filename;

    //INFO (Form("Processing file: %s", osc_file.c_str()));   
    JPetRecoSignal& rsig2 = fReader.generateSignal(osc_file.c_str());
    rsig2.setPM(*((*fIt)->ppm2));
    rsig2.setTSlotIndex(tslot_index);
    psig2.setRecoSignal(rsig2);
    
    filename = path((*((*fIt)->pit)).second).filename().string();
    filename[1] = ((*fIt)->ppref3)[1];
    osc_file = path((*((*fIt)->pit)).second).parent_path().string();
    osc_file+= "/";
    osc_file+= filename;

    //INFO (Form("Processing file: %s", osc_file.c_str()));   
    JPetRecoSignal& rsig3 = fReader.generateSignal(osc_file.c_str());
    rsig3.setPM(*((*fIt)->ppm3));
    rsig3.setTSlotIndex(tslot_index);
    psig3.setRecoSignal(rsig3);

    
    filename = path((*((*fIt)->pit)).second).filename().string();
    filename[1] = ((*fIt)->ppref4)[1];
    osc_file  = path((*((*fIt)->pit)).second).parent_path().string();
    osc_file += "/";
    osc_file += filename;

    //INFO (Form("Processing file: %s", osc_file.c_str())); 
    JPetRecoSignal& rsig4 = fReader.generateSignal(osc_file.c_str());
    rsig4.setPM(*((*fIt)->ppm4));
    rsig4.setTSlotIndex(tslot_index);
    psig4.setRecoSignal(rsig4);
    
    hit1.setSignals(psig1, psig2);
    hit1.setScinID((*fIt)->pscin1->getID());

    hit2.setSignals(psig3, psig4);
    hit2.setScinID((*fIt)->pscin2->getID());

    JPetLOR event;

    event.setHits(hit1, hit2);

    fWriter->write(event);

    break;
  }
  ((*fIt)->pit)++;
  break;
  }
  if((*fIt)->pit == (*fIt)->pfiles.end()) fIt++;
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

void JPetScopeModule::setFileName(const char* name)
{
  fInFilename = TString(name);
  fOutFilename = TString(name);
  fOutFilename.ReplaceAll(".cfg", "");
  fOutFilename.Append(".scope.eve.root");
}
