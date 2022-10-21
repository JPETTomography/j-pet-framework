/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetUnzipTask.cpp
 */

#include "JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "JPetOptionsTools/JPetOptionsTools.h"
#include "JPetCommonTools/JPetCommonTools.h"
#include "JPetUnzipTask/JPetUnzipTask.h"
#include "JPetParams/JPetParams.h"

using namespace jpet_options_generator_tools;
using namespace jpet_options_tools;
using namespace std;

JPetUnzipTask::JPetUnzipTask(const char* name): JPetTask(name) {}

bool JPetUnzipTask::init(const JPetParams& inParams)
{
  INFO("UnzipTask started.");
  fOptions = inParams.getOptions();
  return true;
}

bool JPetUnzipTask::run(const JPetDataInterface&)
{
  auto inputFileWithPath = getInputFile(fOptions);
  auto outputPath = getOutputPath(fOptions);
  if(outputPath == "") { outputPath = "./"; }
  INFO(Form("Unzipping file: %s into %s", inputFileWithPath.c_str(), outputPath.c_str()));
  if (!unzipFile(inputFileWithPath, outputPath)) {
    ERROR(Form("Problem with unzipping file: %s", inputFileWithPath.c_str()));
    return false;
  }
  return true;
}

bool JPetUnzipTask::terminate(JPetParams& outParams)
{
  OptsStrAny new_opts;
  setOutputFileType(new_opts, "hld");
  auto outputFile =
    getOutputPath(fOptions)
    + JPetCommonTools::stripFileNameSuffix(getInputFile(fOptions));
  setOutputFile(new_opts, outputFile);

  if (isOptionSet(fOptions, "firstEvent_int") && isOptionSet(fOptions, "lastEvent_int")) {
    if (getOptionAsInt(fOptions, "firstEvent_int") != -1 && getOptionAsInt(fOptions, "lastEvent_int") != -1) {
      setResetEventRangeOption(new_opts, true);
    }
  }

  outParams = JPetParams(new_opts, outParams.getParamManagerAsShared());
  INFO(Form(
    "UnzipTask finished, unzipped file name: %s", outputFile.c_str()
  ));
  return true;
}

bool JPetUnzipTask::unzipFile(string fileNameWithPath, string outputPath)
{
  auto inputPath = JPetCommonTools::extractPathFromFile(fileNameWithPath);
  auto fimeName = JPetCommonTools::extractFileNameFromFullPath(fileNameWithPath);

  int unzip = 1;
  int move = 1;

  if (JPetCommonTools::exctractFileNameSuffix(fimeName) == ".gz") {

    unzip = system((string("gzip -dk ") + fileNameWithPath).c_str());

    if(inputPath+string("/") != outputPath && outputPath != "./") {
      move = system((
        string("mv ")+fileNameWithPath.substr(0, fileNameWithPath.size()-3)
        +string(" ")+outputPath
      ).c_str());
    } else {
      move = 0;
    }

  } else if (JPetCommonTools::exctractFileNameSuffix(fimeName) == ".xz") {

    unzip = system((string("xz -dk ") + string(fileNameWithPath)).c_str());

    if(inputPath+string("/") != outputPath && outputPath != "./") {
      move = system((
        string("mv ")+fileNameWithPath.substr(0, fileNameWithPath.size()-3)
        +string(" ")+outputPath
      ).c_str());
    } else {
      move = 0;
    }

  } else if (JPetCommonTools::exctractFileNameSuffix(fimeName) == ".bz2") {

    unzip = system((string("bzip2 -dk ") + fileNameWithPath).c_str());

    if(inputPath+string("/") != outputPath && outputPath != "./") {
      move = system((
        string("mv ")+fileNameWithPath.substr(0, fileNameWithPath.size()-4)
        +string(" ")+outputPath
      ).c_str());
    } else {
      move = 0;
    }

  } else if (JPetCommonTools::exctractFileNameSuffix(fimeName) == ".zip") {

    unzip = system(( string("unzip ") + fileNameWithPath ).c_str());

    if(inputPath+string("/") != outputPath && outputPath != "./") {
      move = system((
        string("cd ")+JPetCommonTools::currentFullPath()
        +string(" && ")
        +string("mv ")+fimeName.substr(0, fimeName.size()-4)
        +string(" ")+outputPath
      ).c_str());
    } else {
      move = 0;
    }
  }

  return !(unzip+move);
}
