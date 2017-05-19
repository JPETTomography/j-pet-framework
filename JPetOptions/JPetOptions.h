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
 *  @file JPetOptions.h
 */

#ifndef JPETOPTIONS_H
#define JPETOPTIONS_H

#include <string>
#include <map>
#include <boost/any.hpp>
#include "../JPetCommonTools/JPetCommonTools.h"
#include "../JPetOptionsInterface/JPetOptionsInterface.h"

using boost::any_cast;

class JPetOptions: public JPetOptionsInterface
{

public:
  enum FileType {
    kNoType, kScope, kRaw, kRoot, kHld, kZip, kPhysEve, kPhysHit, kPhysSig, kRawSig, kRecoSig, kTslotCal, kTslotRaw, kUndefinedFileType
  };
  typedef std::map<std::string, boost::any> Options;
  typedef std::vector<std::string> InputFileNames;

  JPetOptions();
  explicit JPetOptions(const Options& opts);

  inline const std::string getInputFile() const {
    return any_cast<std::string>(fOptions.at("inputFile_std::string"));
  }
  inline const std::string getScopeConfigFile() const {
    return any_cast<std::string>(fOptions.at("scopeConfigFile_std::string"));
  }
  inline const std::string getScopeInputDirectory() const {
    return any_cast<std::string>(fOptions.at("scopeInputDirectory_std::string"));
  }
  inline const std::string getOutputFile() const {
    return any_cast<std::string>(fOptions.at("outputFile_std::string"));
  }
  inline const std::string getOutputPath() const {
    return any_cast<std::string>(fOptions.at("outputPath_std::string"));
  }
  inline long long getFirstEvent() const {
    return any_cast<int>(fOptions.at("firstEvent_int"));
  }
  inline long long getLastEvent() const {
    return any_cast<int>(fOptions.at("lastEvent_int"));
  }
  long long getTotalEvents() const;

  inline int getRunNumber() const {
    return any_cast<int>(fOptions.at("runId_int"));
  }
  inline bool isProgressBar() const {
    return any_cast<bool>(fOptions.at("progressBar_bool"));
  }
  inline bool isLocalDB() const {
    return (bool)fOptions.count("localDB_std::string");
  }
  inline std::string getLocalDB() const {
    std::string result("");
    if (isLocalDB()) {
      result = any_cast<std::string>(fOptions.at("localDB_std::string"));
    }
    return result;
  }
  inline bool isLocalDBCreate() const {
    return (bool)fOptions.count("localDBCreate");
  }
  inline std::string getLocalDBCreate() const {
    std::string result("");
    if (isLocalDBCreate()) {
      result = any_cast<std::string>(fOptions.at("localDBCreate_std::string"));
    }
    return result;
  }

  inline const std::string getUnpackerConfigFile() const {
    return any_cast<std::string>(fOptions.at("unpackerConfigFile_std::string"));
  }

  inline const std::string getUnpackerCalibFile() const {
    return any_cast<std::string>(fOptions.at("unpackerCalibFile_std::string"));
  }
  
  FileType getInputFileType() const;
  FileType getOutputFileType() const;

  inline Options getOptions() const {
    return fOptions;
  }

  void resetEventRange();
  static Options resetEventRange(const Options& srcOpts);


protected:

  void handleErrorMessage(const std::string& errorMessage, const std::out_of_range& outOfRangeException) const;
  FileType handleFileType(const std::string& fileType) const;
  void setOptions(const Options& opts) {
    fOptions = opts;
  }
  void setStringToFileTypeConversion();
  Options fOptions;
  std::map<std::string, JPetOptions::FileType> fStringToFileType;

};
#endif /*  !JPETOPTIONS_H */
