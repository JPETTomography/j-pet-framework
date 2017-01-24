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
 *  @file JPetScopeLoader.cpp
 *  @brief Module for oscilloscope data
 *  Reads oscilloscope ASCII data and procudes JPetRecoSignal structures.
 */

#include "./JPetScopeLoader.h"

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
#include "../JPetScopeLoader/JPetScopeLoader.h"
#include "../JPetTreeHeader/JPetTreeHeader.h"
#include "../JPetWriter/JPetWriter.h"
#include "../JPetCommonTools/JPetCommonTools.h"
#include "../JPetScopeConfigParser/JPetScopeConfigParser.h"

#include <iostream>

using namespace std;
using namespace boost::filesystem;
using boost::property_tree::ptree;


JPetScopeLoader::JPetScopeLoader(JPetScopeTask* task): JPetTaskLoader("", "reco.sig", task)
{
  gSystem->Load("libTree");
  /**/
}

JPetScopeLoader::~JPetScopeLoader()
{
  if (fWriter != nullptr) {
    delete fWriter;
    fWriter = nullptr;
  }
}


void JPetScopeLoader::createInputObjects(const char*)
{
  JPetScopeConfigParser confParser;
  auto config = confParser.getConfig(fOptions.getScopeConfigFile());

  auto prefix2PM =  getPMPrefixToPMIdMap(config);
  std::map<std::string, int> inputScopeFiles = createInputScopeFileNames(fOptions.getScopeInputDirectory(), prefix2PM);
  auto task = dynamic_cast<JPetScopeTask*>(fTask);
  task->setInputFiles(inputScopeFiles);


  // create an object for storing histograms and counters during processing
  fStatistics = new JPetStatistics();
  assert(fStatistics);
  fHeader = new JPetTreeHeader(fOptions.getRunNumber());
  assert(fHeader);
  fHeader->setBaseFileName(fOptions.getInputFile());
  fHeader->addStageInfo(task->GetName(), task->GetTitle(), 0, JPetCommonTools::getTimeString());
  //fHeader->setSourcePosition((*fIter).pCollPosition);
}

std::map<std::string, int> JPetScopeLoader::getPMPrefixToPMIdMap(const scope_config::Config& config) const
{
  std::map< std::string, int> prefixToId;
  for (const auto &  pm : config.fPMs) {
    prefixToId[pm.fPrefix] = pm.fId;
  }
  return prefixToId;
}

/// Returns a map of list of scope input files. The key is the corresponding
/// index of the photomultiplier in the param bank.
std::map<std::string, int> JPetScopeLoader::createInputScopeFileNames(
  const std::string& inputPathToScopeFiles,
  std::map<std::string, int> pmPref2Id
) const
{
  for (auto el : pmPref2Id) {
  }
  std::map<std::string, int> scopeFiles;
  path current_dir(inputPathToScopeFiles);
  if (exists(current_dir)) {
    for (recursive_directory_iterator iter(current_dir), end; iter != end; ++iter) {
      std::string filename = iter->path().leaf().string();
      if (isCorrectScopeFileName(filename)) {
        auto prefix = getFilePrefix(filename);
        if ( pmPref2Id.find(prefix) != pmPref2Id.end()) {
          int id = pmPref2Id.find(prefix)->second;
          scopeFiles[iter->path().parent_path().string() + "/" + filename] = id;
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

std::string JPetScopeLoader::getFilePrefix(const std::string& filename) const
{
  auto pos = filename.find("_");
  if (pos != string::npos) {
    return filename.substr(0, pos);
  }
  return "";
}

/// not very effective, but at least we can test it
bool JPetScopeLoader::isCorrectScopeFileName(const std::string& filename) const
{
  boost::regex pattern("^[A-Za-z0-9]+_\\d*.txt");
  return regex_match(filename, pattern);
}

void JPetScopeLoader::init(const JPetOptions::Options& opts)
{
  INFO( "Initialize Scope Loader Module." );
  JPetTaskLoader::init(opts);
}

void JPetScopeLoader::exec()
{
  assert(fTask);
  fTask->setParamManager(fParamManager);
  JPetTaskInterface::Options emptyOpts;
  fTask->init(emptyOpts);
  fTask->exec();
  fTask->terminate();
}

void JPetScopeLoader::terminate()
{
  assert(fWriter);
  assert(fHeader);
  assert(fStatistics);
  fWriter->writeHeader(fHeader);
  fWriter->writeObject(fStatistics->getHistogramsTable(), "Stats");
  //store the parametric objects in the ouptut ROOT file
  getParamManager().saveParametersToFile(fWriter);
  getParamManager().clearParameters();
  fWriter->closeFile();
}
