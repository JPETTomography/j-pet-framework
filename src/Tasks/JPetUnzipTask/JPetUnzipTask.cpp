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
  using namespace jpet_options_tools;
  auto inputFile = getInputFile(fOptions);
  INFO(Form("Unzipping file: %s", inputFile.c_str()));
  if (!unzipFile(inputFile)) {
    ERROR(Form("Problem with unzipping file: %s", inputFile.c_str()));
    return false;
  }
  return true;
}

bool JPetUnzipTask::terminate(JPetParams& outParams)
{
  OptsStrAny new_opts;
  jpet_options_generator_tools::setOutputFileType(new_opts, "hld");
  jpet_options_generator_tools::setOutputFile(
    new_opts,
    JPetCommonTools::stripFileNameSuffix(getInputFile(fOptions))
  );
  outParams = JPetParams(new_opts, outParams.getParamManagerAsShared());
  INFO(Form(
    "UnzipTask finished, unzipped file name: %s",
    (JPetCommonTools::stripFileNameSuffix(getInputFile(fOptions))).c_str()
  ));
  return true;
}

bool JPetUnzipTask::unzipFile(const string& filename)
{
  string suffix = JPetCommonTools::exctractFileNameSuffix(filename);
  if (suffix == ".gz") {
    return !(system((string("gzip -dk ") + string(filename)).c_str()));
  } else if (suffix == ".xz") {
    return !(system((string("xz -dk ") + string(filename)).c_str()));
  } else if (suffix == ".bz2") {
    return !(system((string("bzip2 -dk ") + string(filename)).c_str()));
  } else if (suffix == ".zip") {
    return !(system((string("unzip ") + string(filename)).c_str()));
  } else {
    return false;
  }
}
