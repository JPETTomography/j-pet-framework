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

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

#include <TSystem.h>

#include "JPetCommonTools/JPetCommonTools.h"
#include "JPetScopeConfigParser/JPetScopeConfigParser.h"
#include "JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "JPetScopeData/JPetScopeData.h"

using namespace std;
using namespace boost::filesystem;
using boost::property_tree::ptree;

JPetScopeLoader::JPetScopeLoader(std::unique_ptr<JPetScopeTask> task): JPetTaskIO("ScopeTask", "", "reco.sig")
{
  addSubTask(std::move(task));
  gSystem->Load("libTree");
}

JPetScopeLoader::~JPetScopeLoader()
{
  if (fWriter != nullptr) {
    delete fWriter;
    fWriter = nullptr;
  }
}

void JPetScopeLoader::addSubTask(std::unique_ptr<JPetTaskInterface> subTask)
{
  if (dynamic_cast<JPetScopeTask*>(subTask.get()) == nullptr)
    ERROR("JPetScopeLoader currently allows only JPetScopeTask as subtask");
  if (fSubTasks.size() > 0)
    ERROR("JPetScopeLoader currently allows only one subtask");
  fSubTasks.push_back(std::move(subTask));
}

bool JPetScopeLoader::createInputObjects(const char*)
{
  using namespace jpet_options_tools;
  auto opts = fParams.getOptions();
  for (auto fSubTask = fSubTasks.begin(); fSubTask != fSubTasks.end(); fSubTask++) {
    auto task = dynamic_cast<JPetScopeTask*>((*fSubTask).get());
    std::unique_ptr<JPetStatistics> tmp(new JPetStatistics());
    fStatistics = std::move(tmp);
    assert(fStatistics);
    fHeader = new JPetTreeHeader(getRunNumber(opts));
    assert(fHeader);
    fHeader->setBaseFileName(getInputFile(opts).c_str());
    fHeader->addStageInfo(task->getName(), "", 0, JPetCommonTools::getTimeString());
  }
  return true;
}

std::map<std::string, int> JPetScopeLoader::getPMPrefixToPMIdMap()
{
  std::map< std::string, int> prefixToId;
  for (const auto&   pm : getParamBank().getPMs()) {
    prefixToId[pm.second->getDescription()] = pm.first;
  }
  return prefixToId;
}

/// Returns a map of list of scope input files. The value is the corresponding
/// index of the photomultiplier in the param bank.
std::map<std::string, int> JPetScopeLoader::createInputScopeFileNames(
  const std::string& inputPathToScopeFiles,
  std::map<std::string, int> pmPref2Id
) const
{
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

bool JPetScopeLoader::init(const JPetParamsInterface& paramsI)
{
  using namespace jpet_options_tools;
  INFO( "Initialize Scope Loader Module." );
  JPetTaskIO::init(paramsI);
  DEBUG( "After initialization  of the JPetTaskIO in Scope Loader init." );
  return true;
}

bool JPetScopeLoader::run(const JPetDataInterface&)
{
  assert(!fSubTasks.empty());
  if (fSubTasks.size() != 1) {
    ERROR("number of subtasks !=1");
    return false;
  }
  auto subTask = fSubTasks.begin()->get();
  subTask->init(fParams);

  using namespace jpet_options_tools;
  JPetScopeConfigParser confParser;
  auto opts = fParams.getOptions();
  auto config = confParser.getConfig(getScopeConfigFile(opts));
  auto prefix2PM =  getPMPrefixToPMIdMap();
  auto inputScopeFiles = createInputScopeFileNames(getScopeInputDirectory(opts), prefix2PM);
  auto events = JPetScopeLoader::groupScopeFileNamesByTimeWindowIndex(inputScopeFiles);

  for (auto& ev : events) {
    auto pOutputEvent = (dynamic_cast<JPetUserTask*>(subTask))->getOutputEvents();
    if (pOutputEvent != nullptr) {
      pOutputEvent->Clear();
    } else {
      WARNING("No proper timeWindow object returned to clear events");
    }
    JPetScopeData data(ev);
    subTask->run(data);
    pOutputEvent = (dynamic_cast<JPetUserTask*>(subTask))->getOutputEvents();
    if (pOutputEvent != nullptr) {
      fWriter->write(*pOutputEvent);
    } else {
      ERROR("No proper timeWindow object returned to save to file, returning from subtask " + subTask->getName());
      return false;
    }
  }
  subTask->terminate(fParams);
  return true;
}


bool JPetScopeLoader::terminate(JPetParamsInterface& output_params)
{
  auto& params = dynamic_cast<JPetParams&>(output_params);
  OptsStrAny new_opts;
  jpet_options_generator_tools::setOutputFile(new_opts, fOutFileFullPath);
  params = JPetParams(new_opts, params.getParamManagerAsShared());

  assert(fWriter);
  assert(fHeader);
  assert(fStatistics);
  fWriter->writeHeader(fHeader);
  fWriter->writeCollection(fStatistics->getStatsTable(), "Stats");
  //store the parametric objects in the ouptut ROOT file
  getParamManager().saveParametersToFile(fWriter);
  getParamManager().clearParameters();
  fWriter->closeFile();
  return true;
}

bool JPetScopeLoader::createOutputObjects(const char* outputFilename)
{

  fWriter = new JPetWriter( outputFilename );
  assert(fWriter);
  if (!fSubTasks.empty()) {
    for (auto fSubTask = fSubTasks.begin(); fSubTask != fSubTasks.end(); fSubTask++) {
      auto task = dynamic_cast<JPetScopeTask*>((*fSubTask).get());
      task->setStatistics(fStatistics.get());
    }
  } else {
    WARNING("the subTask does not exist, so JPetWriter and JPetStatistics not passed to it");
    return false;
  }
  return true;
}

std::tuple<bool, std::string, std::string, bool> JPetScopeLoader::setInputAndOutputFile(const jpet_options_tools::OptsStrAny opts) const
{
  using namespace jpet_options_tools;
  bool resetOutputPath = fResetOutputPath;
  std::string inputFilename = getInputFile(opts);

  /// this argument is not really used by the ScopeLoader  since inputFiles are generated
  /// based on json content
  inputFilename =  inputFilename + "." + fOutFileType + ".root";
  auto outFileFullPath = inputFilename;
  if (isOptionSet(opts, "outputPath_std::string")) {
    std::string outputPath(getOutputPath(opts));
    if (!outputPath.empty()) {
      outFileFullPath = outputPath + JPetCommonTools::extractFileNameFromFullPath(inputFilename);
      resetOutputPath = true;
    }
  }
  return std::make_tuple(true, inputFilename, outFileFullPath, resetOutputPath);
}


int JPetScopeLoader::getTimeWindowIndex(const std::string&  pathAndFileName)
{
  int time_window_index = -1;
  if (!boost::filesystem::exists(pathAndFileName)) {
    ERROR("File does not exist ");
  }
  int res = sscanf(JPetCommonTools::extractFileNameFromFullPath(pathAndFileName).c_str(), "%*3s %d", &time_window_index);
  if (res <= 0) {
    ERROR("scanf failed");
    return -1;
  } else {
    return time_window_index;
  }
}

std::map<int, std::map<std::string, int>> JPetScopeLoader::groupScopeFileNamesByTimeWindowIndex(const std::map<std::string, int>& scopeFileNames)
{
  std::map<int, std::map<std::string, int>> res;
  for (auto& el : scopeFileNames) {
    auto index = JPetScopeLoader::getTimeWindowIndex(el.first);
    auto it = res.find(index);
    if (it == res.end() ) {
      res[index] = {{el.first, el.second}};
    } else {
      it->second.insert(el);
    }
  }
  return res;
}
