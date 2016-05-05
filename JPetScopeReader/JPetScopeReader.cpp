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
#include "../JPetScopeConfigParser/JPetScopeConfigParser.h"

#include <iostream>

using namespace std;
using namespace boost::filesystem;
using boost::property_tree::ptree;


JPetScopeReader::JPetScopeReader(JPetScopeTask* task): JPetTaskLoader(), fEventNb(0), fWriter(nullptr)
{
  gSystem->Load("libTree");
  addSubTask(task);
}


JPetScopeReader::~JPetScopeReader()
{

  if (fWriter != nullptr) {
    delete fWriter;
    fWriter = nullptr;
  }

}

void JPetScopeReader::createInputObjects(const char* inputFileName)
{
  JPetScopeConfigParser confParser;
  auto configs = confParser.getConfigs(fOptions.getScopeConfigFile());

  assert(configs.size()==1); ///wk for a moment
  for (const auto & config : configs) {
    if(!getParamManager().getParametersFromScopeConfig(config)) { 
      ERROR("Unable to generate Param Bank from Scope Config");
    } 
  }
  /// inputFile is in this context the directory with oscilloscope files
  auto inputScopeFiles = createInputScopeFileNames(fOptions.getInputFile());

///

  /*  // Create property tree*/

  //ptree prop_tree;

  //// Check file type

  //string ext = path((const char*)fInFilename).extension().string();

  //// Read configuration data to property tree

  //if (ext.compare(".ini") == 0) {
  //read_ini(fInFilename.Data(), prop_tree);
  //} else if (ext.compare(".info") == 0) {
  //read_info(fInFilename.Data(), prop_tree);
  //} else if (ext.compare(".json") == 0) {
  //read_json(fInFilename.Data(), prop_tree);
  //} else if (ext.compare(".xml") == 0) {
  //read_xml(fInFilename.Data(), prop_tree);
  //} else {
  //ERROR("Cannot open config file. Exiting");
  //exit(-1);
  //}

  // Fill fConfigs
  //for (ptree::const_iterator it = prop_tree.begin(); it != prop_tree.end(); ++it) {

  //string files_location;

  //const ptree& conf_data = it->second;

  //files_location = conf_data.get<string>("location");

  //JPetParamBank const& param_bank = createParamBank (conf_data);

////wk to trzeba wyabstrahowac jako metode ktora zwraca zestaw nazw plikow wyjsciowych
  //// Fill Configs

  //string collimator_function;
  //int a, b, c, n;
  //BOOST_FOREACH(const ptree::value_type& v, conf_data.get_child("collimator")) {

  //if (ext.compare(".json") == 0) collimator_function = v.second.get<string>("positions");
  //else collimator_function = v.second.data();

  //n = sscanf(collimator_function.c_str(), "%d %d %d", &a, &b, &c);

  //if (n > 0) {
  //if (n == 1) {b = a; c = 1;}
  //if (n == 2) {c = 1;}

  //for (int j = a; j <=b; j+= c) {

  //fConfigs.push_back(ScopeConfig());
  //vector <ScopeConfig> :: iterator current_config = fConfigs.end() - 1;

  //// Add config name
  //(*current_config).pName         = it->first;

  //// Add collimator position
  //(*current_config).pCollPosition = j;

  //// Add param bank
  //(*current_config).pParamBank    = &param_bank;

  //// Add PMs
  //(*current_config).pPM1          = &(param_bank.getPM(0));
  //(*current_config).pPM2          = &(param_bank.getPM(1));
  //(*current_config).pPM3          = &(param_bank.getPM(2));
  //(*current_config).pPM4          = &(param_bank.getPM(3));

  //// Add Scintillators
  //(*current_config).pScin1        = &(param_bank.getScintillator(0));
  //(*current_config).pScin2        = &(param_bank.getScintillator(1));

  //// Add filename prefixes
  //(*current_config).pPrefix1      = conf_data.get<string>("pm1.prefix");
  //(*current_config).pPrefix2      = conf_data.get<string>("pm2.prefix");
  //(*current_config).pPrefix3      = conf_data.get<string>("pm3.prefix");
  //(*current_config).pPrefix4      = conf_data.get<string>("pm4.prefix");

  //// Add oscilloscope files
  //string starting_loc  = path((const char*)fInFilename).parent_path().string();
  //starting_loc += "/";
  //starting_loc += files_location;
  //starting_loc += "/";
  //starting_loc += to_string (j);

  //path current_dir(starting_loc);
  //boost::regex pattern(Form("%s_\\d*.txt", (*current_config).pPrefix1.c_str()));

  //if (exists(current_dir))
  //for (recursive_directory_iterator iter(current_dir), end; iter != end; ++iter) {
  //string name = iter->path().leaf().string();
  //string dir;
  //if (regex_match(name, pattern)) {
  //name[1] = ((*current_config).pPrefix1)[1];
  //dir = iter->path().parent_path().string();
  //dir += "/";
  //dir += name;
  //(*current_config).pFiles.insert(dir);
  //}
  //}
  //else {
  //string msg  = "Directory: \"";
  //msg += current_dir.string();
  //msg += "\" does not exist.";
  //ERROR(msg.c_str());
  //}

  //// Set Iterator to begining
  //(*current_config).pIter         = (*current_config).pFiles.begin();
  //}
  //}
  //}
  ////wk to trzeba wyabstrahowac jako metode end
  //}

  //fWriter = nullptr;

  //fEventNb = 0;
  //for (vector <ScopeConfig> :: iterator it = fConfigs.begin(); it != fConfigs.end(); ++it) {
  //fEventNb += (*it).pFiles.size();
  //}
}



std::vector<std::string> JPetScopeReader::createInputScopeFileNames(const std::string& inputPathToScopeFiles) const
{
  std::vector<std::string> scopeFiles;
  path current_dir(inputPathToScopeFiles);
  if (exists(current_dir)) {
    for (recursive_directory_iterator iter(current_dir), end; iter != end; ++iter) {
      std::string filename = iter->path().leaf().string();
      if( isCorrectScopeFileName(filename)) {
        scopeFiles.push_back(iter->path().parent_path().string() + "/" + filename);
      }
    }
    
  } else {
    string msg  = "Directory: \"";
    msg += current_dir.string();
    msg += "\" does not exist.";
    ERROR(msg.c_str());
  }

  //boost::regex pattern(Form("%s_\\d*.txt", (*current_config).pPrefix1.c_str()));

  //if (exists(current_dir)) {
    //for (recursive_directory_iterator iter(current_dir), end; iter != end; ++iter) {
      //string name = iter->path().leaf().string();
      //string dir;
      //if (regex_match(name, pattern)) {
        //name[1] = ((*current_config).pPrefix1)[1];
        //dir = iter->path().parent_path().string();
        //dir += "/";
        //dir += name;
        //(*current_config).pFiles.insert(dir);
      //}
    //}
  //} else {
    //string msg  = "Directory: \"";
    //msg += current_dir.string();
    //msg += "\" does not exist.";
    //ERROR(msg.c_str());
  //}

  return scopeFiles;
}

/// not very effective, but at least we can test it
bool JPetScopeReader::isCorrectScopeFileName(const std::string& filename) const
{
  boost::regex pattern("^[A-Za-z0-9]+_\\d*.txt");
  return regex_match(filename, pattern);
}

void JPetScopeReader::createOutputObjects(const char* outputFileName)
{
  //fIter = fConfigs.begin();
}

std::string JPetScopeReader::createOutputFilename()
{
  string out_fn(fOutFilename.Data());
  int last_dot = out_fn.find_last_of(".");
  string out_fn2  = out_fn.substr(0, last_dot );
  out_fn2 += "_";
  out_fn2 += (*fIter).pName;
  out_fn2 += "_";
  out_fn2 += to_string((*fIter).pCollPosition);
  out_fn2 += ".reco.sig";
  out_fn2 += out_fn.substr(last_dot);

  return out_fn2;
}

void JPetScopeReader::createNewWriter()
{

  if (fConfigs.empty()) {
    ERROR("No files for processing.");
  } else {
    terminate();

    INFO (Form("Creating root file for configuration %s and position %d", ((*fIter).pName).c_str(), (*fIter).pCollPosition));

//wk wyodrebnij to jako metode
    /*
    string out_fn(fOutFilename.Data());
    int last_dot = out_fn.find_last_of(".");
    string out_fn2  = out_fn.substr(0,last_dot );
           out_fn2 += "_";
           out_fn2 += (*fIter).pName;
     out_fn2 += "_";
           out_fn2 += to_string((*fIter).pCollPosition);
     out_fn2 += ".reco.sig";
           out_fn2 += out_fn.substr(last_dot);
           */
    std::string out_fn2 = createOutputFilename();
//wk az do tego miejsca, petoda zwraca stringa

    fWriter = new JPetWriter(out_fn2.c_str());

    auto optionContainer = JPetManager::getManager().getOptions();
    assert(optionContainer.size() == 1);
    auto options = optionContainer.front();
    fHeader = new JPetTreeHeader(options.getRunNumber());
    fHeader->setBaseFileName(options.getInputFile());
    fHeader->addStageInfo(fTask->GetName(), fTask->GetTitle(), 0, CommonTools::getTimeString());
    fHeader->setSourcePosition((*fIter).pCollPosition);
    fWriter->writeHeader(fHeader);
  }
}

void JPetScopeReader::init(const JPetOptions::Options& opts)
{
  INFO( "Starting Scope Reader Module." );
  setOptions(JPetOptions(opts));
  auto inputFilename = fOptions.getInputFile();
  auto outputFilename = fOptions.getOutputFile();
  createInputObjects(inputFilename);
  createOutputObjects(outputFilename);
}

void JPetScopeReader::exec()
{

  assert(fTask);

  fTask->setParamManager(&(getParamManager()));
  JPetTaskInterface::Options emptyOpts;
  fTask->init(emptyOpts);
  createNewWriter();
  fTask->setWriter(fWriter);
  fTask->exec();
  fTask->terminate();
   
  //for (fIter = fConfigs.begin(); fIter != fConfigs.end(); fIter++) {


    //for ((*fIter).pIter = (*fIter).pFiles.begin(); (*fIter).pIter != (*fIter).pFiles.end(); (*fIter).pIter++) {

      //dynamic_cast<JPetScopeTask*>(fTask)->setScopeConfig(&(*fIter));
      //fTask->exec();

    //}

    //fWriter->writeObject((*fIter).pParamBank, "ParamBank");

  //}
}

void JPetScopeReader::terminate()
{

  if (fWriter)
    if (fWriter->isOpen()) {
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



