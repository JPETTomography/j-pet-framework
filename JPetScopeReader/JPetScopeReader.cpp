/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetScopeReader.cpp
 *  @brief Module for oscilloscope data
 *  Reads oscilloscope ASCII data and procudes JPetRecoSignal structures.
 */

#include "./JPetScopeReader.h"

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

#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetManager/JPetManager.h"
#include "../JPetParamBank/JPetParamBank.h"
#include "../JPetPhysSignal/JPetPhysSignal.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetRecoSignal/JPetRecoSignal.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetScopeReader/JPetScopeReader.h"
#include "../JPetTreeHeader/JPetTreeHeader.h"
#include "../JPetWriter/JPetWriter.h"
#include "../CommonTools/CommonTools.h"

#include <iostream>

using namespace std;
using namespace boost::filesystem;
using boost::property_tree::ptree;

JPetScopeReader::JPetScopeReader(JPetScopeTask * task): JPetTaskLoader(), fEventNb(0), fWriter(nullptr) {
  gSystem->Load("libTree");

  addSubTask(task);
}


JPetScopeReader::~JPetScopeReader() {

  if (fWriter != nullptr) {
    delete fWriter;
    fWriter = nullptr;
  }

}

JPetParamBank const& JPetScopeReader::createParamBank(ptree const& conf_data) {
    
    // Read Data from config tree
//wk to powinno byc robione przez ScopeConfigParser
//

    int bslotid1, bslotid2;
    bool bslotactive1, bslotactive2;
    string bslotname1, bslotname2;
    float bslottheta1, bslottheta2;
    int bslotframe1, bslotframe2;

    bslotid1 = conf_data.get("bslot1.id", -1);
    bslotid2 = conf_data.get("bslot2.id", -1);

    bslotactive1 = conf_data.get("bslot1.active", false);
    bslotactive2 = conf_data.get("bslot2.active", false);

    bslotname1 = conf_data.get("bslot1.name", string(""));
    bslotname2 = conf_data.get("bslot2.name", string(""));

    bslottheta1 = conf_data.get("bslot1.theta", -1.f);
    bslottheta2 = conf_data.get("bslot2.theta", -1.f);

    bslotframe1 = conf_data.get("bslot1.frame", -1);
    bslotframe2 = conf_data.get("bslot2.frame", -1);

    int pmid1, pmid2, pmid3, pmid4;

    pmid1 = conf_data.get("pm1.id", 0);
    pmid2 = conf_data.get("pm2.id", 0);
    pmid3 = conf_data.get("pm3.id", 0);
    pmid4 = conf_data.get("pm4.id", 0);

    int scinid1, scinid2;

    scinid1 = conf_data.get("scin1.id", 0);
    scinid2 = conf_data.get("scin2.id", 0);

// wk do tego momentu
    // Create Parametric objects
    
    JPetBarrelSlot bslot1 (bslotid1, bslotactive1, bslotname1, bslottheta1, bslotframe1);
    JPetBarrelSlot bslot2 (bslotid2, bslotactive2, bslotname2, bslottheta2, bslotframe2);
    
    JPetPM pm1(pmid1);
    JPetPM pm2(pmid2);
    JPetPM pm3(pmid3);
    JPetPM pm4(pmid4);

    /**
    * A		B
    * PM1	PM2
    * PM3	PM4
    */
    pm1.setSide(JPetPM::SideA);
    pm2.setSide(JPetPM::SideB);
    pm3.setSide(JPetPM::SideA);
    pm4.setSide(JPetPM::SideB);
    
    JPetScin scin1(scinid1);
    JPetScin scin2(scinid2);

    JPetParamBank* param_bank = new JPetParamBank();

    param_bank->addBarrelSlot(bslot1);
    param_bank->addBarrelSlot(bslot2);

    param_bank->addPM(pm1);
    param_bank->addPM(pm2);
    param_bank->addPM(pm3);
    param_bank->addPM(pm4);

    param_bank->addScintillator(scin1);
    param_bank->addScintillator(scin2);

    (param_bank->getPM(pmid1)).setScin(param_bank->getScintillator(scinid1));
    (param_bank->getPM(pmid2)).setScin(param_bank->getScintillator(scinid1));
    (param_bank->getPM(pmid3)).setScin(param_bank->getScintillator(scinid2));
    (param_bank->getPM(pmid4)).setScin(param_bank->getScintillator(scinid2));

    (param_bank->getPM(pmid1)).setBarrelSlot(param_bank->getBarrelSlot(bslotid1));
    (param_bank->getPM(pmid2)).setBarrelSlot(param_bank->getBarrelSlot(bslotid1));
    (param_bank->getPM(pmid3)).setBarrelSlot(param_bank->getBarrelSlot(bslotid2));
    (param_bank->getPM(pmid4)).setBarrelSlot(param_bank->getBarrelSlot(bslotid2));

    (param_bank->getScintillator(scinid1)).setBarrelSlot(param_bank->getBarrelSlot(bslotid1));
    (param_bank->getScintillator(scinid2)).setBarrelSlot(param_bank->getBarrelSlot(bslotid2));

    return *param_bank;
}

void JPetScopeReader::createInputObjects(const char*) {

  // Create property tree

  ptree prop_tree;

  // Check file type
  
  string ext = path((const char*)fInFilename).extension().string();

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

    string files_location;

    const ptree& conf_data = it->second;

    files_location = conf_data.get<string>("location");

    JPetParamBank const& param_bank = createParamBank (conf_data);

//wk to trzeba wyabstrahowac jako metode ktora zwraca zestaw nazw plikow wyjsciowych
    // Fill Configs

    string collimator_function;
    int a, b, c, n;
    BOOST_FOREACH(const ptree::value_type& v, conf_data.get_child("collimator")) {

      if (ext.compare(".json") == 0) collimator_function = v.second.get<string>("positions");
      else collimator_function = v.second.data();

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
	  (*current_config).pParamBank    = &param_bank;

	  // Add PMs
			auto PMiter = param_bank.getPMs().begin();
	  (*current_config).pPM1 = (*PMiter).second;
			PMiter++;
	  (*current_config).pPM2 = (*PMiter).second;
			PMiter++;
	  (*current_config).pPM3 = (*PMiter).second;
			PMiter++;
	  (*current_config).pPM4 = (*PMiter).second;

	  // Add Scintillators
			auto scinIter = param_bank.getScintillators().begin();
	  (*current_config).pScin1 = (*scinIter).second;
			scinIter++;
	  (*current_config).pScin2 = (*scinIter).second;

	  // Add filename prefixes
	  (*current_config).pPrefix1      = conf_data.get<string>("pm1.prefix");
	  (*current_config).pPrefix2      = conf_data.get<string>("pm2.prefix");
	  (*current_config).pPrefix3      = conf_data.get<string>("pm3.prefix");
	  (*current_config).pPrefix4      = conf_data.get<string>("pm4.prefix");

	  // Add oscilloscope files
	  string starting_loc  = path((const char*)fInFilename).parent_path().string();
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
  //wk to trzeba wyabstrahowac jako metode end
  }

  fWriter = nullptr;
  
  fEventNb = 0;
  for (vector <ScopeConfig> :: iterator it = fConfigs.begin(); it != fConfigs.end(); ++it) {
    fEventNb += (*it).pFiles.size();
  }
}

void JPetScopeReader::createOutputObjects(const char*) {
  fIter = fConfigs.begin();
}

void JPetScopeReader::createNewWriter() {
  
  if (fConfigs.empty()) {
    ERROR("No files for processing.");
  }
  else {
    terminate();

    INFO (Form("Creating root file for configuration %s and position %d", ((*fIter).pName).c_str(), (*fIter).pCollPosition));

//wk wyodrebnij to jako metode
    string out_fn(fOutFilename.Data());
    int last_dot = out_fn.find_last_of(".");
    string out_fn2  = out_fn.substr(0,last_dot );
           out_fn2 += "_";
           out_fn2 += (*fIter).pName;
	   out_fn2 += "_";
           out_fn2 += to_string((*fIter).pCollPosition);
	   out_fn2 += ".reco.sig";
           out_fn2 += out_fn.substr(last_dot);
//wk az do tego miejsca, petoda zwraca stringa 
    
    fWriter = new JPetWriter(out_fn2.c_str());

    auto optionContainer = JPetManager::getManager().getOptions();
    assert(optionContainer.size() ==1);
    auto options = optionContainer.front();
    fHeader = new JPetTreeHeader(options.getRunNumber());
    fHeader->setBaseFileName(options.getInputFile());
    fHeader->addStageInfo(fTask->GetName(), fTask->GetTitle(), 0, CommonTools::getTimeString());
    fHeader->setSourcePosition((*fIter).pCollPosition);
    fWriter->writeHeader(fHeader);
  }
}

void JPetScopeReader::init() {

  INFO( "Starting Scope Reader Module." );

  createInputObjects();
  createOutputObjects();
}

void JPetScopeReader::exec() {

  assert(fTask);
  
  JPetTaskInterface::Options emptyOpts;
  fTask->init(emptyOpts);

  for(fIter = fConfigs.begin();fIter != fConfigs.end();fIter++){
    
    createNewWriter();
    fTask->setWriter(fWriter);
   
    for((*fIter).pIter = (*fIter).pFiles.begin();(*fIter).pIter != (*fIter).pFiles.end(); (*fIter).pIter++){

      dynamic_cast<JPetScopeTask*>(fTask)->setScopeConfig(&(*fIter));
      fTask->exec();      
      
    }
    
    fWriter->writeObject((*fIter).pParamBank, "ParamBank");	    
    
  }
}

void JPetScopeReader::terminate() {

  if(fWriter)
  if(fWriter->isOpen()) {
    fWriter->closeFile();
    delete fWriter;
    fWriter = nullptr;
  }
}

void JPetScopeReader::setFileName(const char* name)
{
  fInFilename = TString(name);
  fOutFilename = TString(name);
  fOutFilename.ReplaceAll(".ini", "");
  fOutFilename.ReplaceAll(".info", "");
  fOutFilename.ReplaceAll(".json", "");
  fOutFilename.ReplaceAll(".xml", "");
  fOutFilename.Append(".root");
}



