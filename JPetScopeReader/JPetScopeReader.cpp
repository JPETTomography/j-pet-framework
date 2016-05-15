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
#include "../JPetCommonTools/JPetCommonTools.h"
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

  assert(configs.size() == 1); ///wk for a moment
  std::map<int, std::vector<std::string>> inputScopeFiles;
  for (const auto & config : configs) {
    if (!getParamManager().getParametersFromScopeConfig(config)) {
      ERROR("Unable to generate Param Bank from Scope Config");
    }
    auto prefix2PM =  getPMPrefixToPMIndicesMap(config);
    inputScopeFiles = createInputScopeFileNames(fOptions.getInputFile(), prefix2PM);
  }
  /// inputFile is in this context the directory with oscilloscope files
  /// It is not a nice solution, I know
  (static_cast<JPetScopeTask*>(fTask))->setInputFiles(inputScopeFiles);
}

std::map<std::string, int> JPetScopeReader::getPMPrefixToPMIndicesMap(const scope_config::Config& config) const
{
  std::map< std::string, int> prefixToIndex;
  int i = 0;
  for (const auto &  pm : config.fPMs) {
    prefixToIndex[pm.fPrefix] = i;
    i++;
  }
  return prefixToIndex;
}

/// Returns a map of list of scope input files. The key is the corresponding
/// index of the photomultiplier in the param bank.
std::map<int, std::vector<std::string>> JPetScopeReader::createInputScopeFileNames(
                                            const std::string& inputPathToScopeFiles, 
                                            std::map<std::string, int> pmPref2Index
                                                                   ) const
{
  std::map<int, std::vector<std::string>> scopeFiles;
  /// adding accepted keys that corresponds to PM indices
  for (const auto& el: pmPref2Index) {
    scopeFiles[el.second];
  }
  path current_dir(inputPathToScopeFiles);
  if (exists(current_dir)) {
    for (recursive_directory_iterator iter(current_dir), end; iter != end; ++iter) {
      std::string filename = iter->path().leaf().string();
      if (isCorrectScopeFileName(filename)) {
        auto prefix = getFilePrefix(filename);
        if ( pmPref2Index.find(prefix) != pmPref2Index.end()) { 
          int index = pmPref2Index.find(prefix)->second;
          scopeFiles.at(index).push_back(iter->path().parent_path().string() + "/" + filename);
        } else {
          WARNING("The filename does not contain the accepted prefix:" + filename);
        }
      }
    }
  } else {
    string msg  = "Directory: \"";
    msg += current_dir.string();
    msg += "\" does not exist.";
    ERROR(msg.c_str());
  }
  return scopeFiles;
}

std::string JPetScopeReader::getFilePrefix(const std::string& filename) const
{
  auto pos = filename.find("_");
  if (pos != string::npos) {
    return filename.substr(0, pos);
  }
  return "";
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
    fHeader->addStageInfo(fTask->GetName(), fTask->GetTitle(), 0, JPetCommonTools::getTimeString());
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



