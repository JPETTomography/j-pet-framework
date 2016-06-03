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
#include "../JPetCommonTools/JPetCommonTools.h"

class JPetOptions
{

public:
  enum FileType
  {
    kNoType, kScope, kRaw, kRoot, kHld, kPhysEve, kPhysHit, kPhysSig, kRawSig, kRecoSig, kTslotCal, kTslotRaw, kUndefinedFileType
  };
  typedef std::map<std::string, std::string> Options;
  typedef std::vector<std::string> InputFileNames;

  JPetOptions();
  explicit JPetOptions(const Options& opts);

  bool areCorrect(const Options&) const;
  const char* getInputFile() const {
    return fOptions.at("inputFile").c_str();
  }
  const char* getScopeConfigFile() const {
    return fOptions.at("scopeConfigFile").c_str();
  }
  const char* getScopeInputDirectory() const {
    return fOptions.at("scopeInputDirectory").c_str();
  }
  const char* getOutputFile() const {
    return fOptions.at("outputFile").c_str();
  }
  long long getFirstEvent() const {
    return std::stoll(fOptions.at("firstEvent"));
  }
  long long getLastEvent() const {
    return std::stoll(fOptions.at("lastEvent"));
  }
  int getRunNumber() const {
    return std::stoi(fOptions.at("runId"));
  }
  bool isProgressBar() const {
    return JPetCommonTools::to_bool(fOptions.at("progressBar"));
  }
		bool isLocalDB() const {
				return fOptions.count("localDB") > 0;
		}
		std::string getLocalDB() const {
				std::string result("");
				if (isLocalDB()) {
						result = fOptions.at("localDB");
				}
				return result;
		}
		bool isLocalDBCreate() const {
				return fOptions.count("localDBCreate") > 0;
		}
		std::string getLocalDBCreate() const {
				std::string result("");
				if (isLocalDBCreate()) {
						result = fOptions.at("localDBCreate");
				}
				return result;
		}
  
  FileType getInputFileType() const;
  FileType getOutputFileType() const;
  
  inline Options getOptions() const {
    return fOptions;
  }

  void resetEventRange();

  static  Options getDefaultOptions() {
    return kDefaultOptions;
  }

protected:
  static Options kDefaultOptions;

  void handleErrorMessage(const std::string &errorMessage, const std::out_of_range &outOfRangeException) const;
  FileType handleFileType(const std::string &fileType) const;
  void setOptions(const Options& opts) {
    fOptions = opts;
  }
  void setStringToFileTypeConversion();
  Options fOptions;
  std::map<std::string, JPetOptions::FileType> fStringToFileType;

};
#endif /*  !JPETOPTIONS_H */
