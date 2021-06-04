/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetOptionValidator.cpp
 */

#include "JPetOptionValidator/JPetOptionValidator.h"
#include "JPetCommonTools/JPetCommonTools.h"
#include "JPetLoggerInclude.h"
#include "JPetOptionsTools/JPetOptionsTools.h"

using boost::any_cast;

JPetOptionValidator::JPetOptionValidator() { fValidatorMap = generateValidationMap(); }

bool JPetOptionValidator::areCorrectOptions(const std::map<std::string, boost::any>& optionsMap,
                                            std::vector<std::string>& namesOfOptionsToBeValidated)
{
  auto newOptionsMap = addNonStandardValidators(optionsMap);
  for (auto& checkGroup : fValidatorMap)
  {
    if (std::find(namesOfOptionsToBeValidated.begin(), namesOfOptionsToBeValidated.end(), checkGroup.first) != namesOfOptionsToBeValidated.end())
    {
      for (auto& checkFunc : checkGroup.second)
      {
        if ((!checkFunc(std::make_pair(checkGroup.first, newOptionsMap.at(checkGroup.first)))))
        {
          ERROR("VALIDATION ERROR FOR " + checkGroup.first);
          return false;
        }
      }
    }
  }
  return true;
}

std::map<std::string, boost::any> JPetOptionValidator::addNonStandardValidators(const std::map<std::string, boost::any>& optionsMap)
{
  std::map<std::string, boost::any> newOptionsMap(optionsMap);
  addFileTypeAndNameValidator(newOptionsMap);
  return newOptionsMap;
}

void JPetOptionValidator::addFileTypeAndNameValidator(std::map<std::string, boost::any>& optionsMap)
{
  using namespace jpet_options_tools;
  std::string type_key = "type_std::string";
  std::string filename_key = "file_std::vector<std::string>";
  if (!isOptionSet(optionsMap, type_key) || !isOptionSet(optionsMap, filename_key))
  {
    WARNING("file type or file name option not present! No validator added!");
    return;
  }
  optionsMap["type_std::string, file_std::vector<std::string>"] =
      JPetOptionValidator::ManyOptionsWrapper({getOptionAsString(optionsMap, type_key), getOptionAsVectorOfStrings(optionsMap, filename_key)});
}

std::map<std::string, std::vector<bool (*)(std::pair<std::string, boost::any>)>> JPetOptionValidator::generateValidationMap()
{
  std::map<std::string, std::vector<bool (*)(std::pair<std::string, boost::any>)>> validationMap;
  validationMap["range_std::vector<int>"].push_back(&isNumberBoundsInRangeValid);
  validationMap["range_std::vector<int>"].push_back(&isRangeOfEventsValid);
  validationMap["type_std::string"].push_back(&isCorrectFileType);
  validationMap["file_std::vector<std::string>"].push_back(&areFilesValid);
  validationMap["type_std::string, file_std::vector<std::string>"].push_back(&isFileTypeMatchingExtensions);
  validationMap["runID_int"].push_back(&isRunIDValid);
  validationMap["detectorType_std::string"].push_back(&isDetectorValid);
  validationMap["localDB_std::string"].push_back(&isLocalDBValid);
  validationMap["outputPath_std::string"].push_back(&isOutputDirectoryValid);
  return validationMap;
}

void JPetOptionValidator::addValidatorFunction(const std::string& name, bool (*validatorFunction)(std::pair<std::string, boost::any>))
{
  fValidatorMap[name].push_back(validatorFunction);
}

bool JPetOptionValidator::isNumberBoundsInRangeValid(std::pair<std::string, boost::any> option)
{
  if (any_cast<std::vector<int>>(option.second).size() != 2)
  {
    ERROR("Wrong number of bounds in range: " + std::to_string(any_cast<std::vector<int>>(option.second).size()));
    return false;
  }
  return true;
}

bool JPetOptionValidator::isRangeOfEventsValid(std::pair<std::string, boost::any> option)
{
  if (any_cast<std::vector<int>>(option.second).at(0) > any_cast<std::vector<int>>(option.second).at(1))
  {
    ERROR("Wrong number of bounds in range: " + std::to_string(any_cast<std::vector<int>>(option.second).size()));
    return false;
  }
  return true;
}

bool JPetOptionValidator::isCorrectFileType(std::pair<std::string, boost::any> option)
{
  std::string type = any_cast<std::string>(option.second);
  if (type == "hld" || type == "root" || type == "scope" || type == "zip" || type == "mcGeant")
  {
    return true;
  }
  else
  {
    ERROR("Wrong type of file:" + type);
    return false;
  }
}

bool JPetOptionValidator::isFileTypeMatchingExtensions(std::pair<std::string, boost::any> option)
{
  ManyOptionsWrapper optionsWrapper = any_cast<ManyOptionsWrapper>(option.second);
  std::vector<boost::any> optionsVector = any_cast<std::vector<boost::any>>(optionsWrapper.getOptionsVector());
  std::string fileType = any_cast<std::string>(optionsVector[0]);
  std::vector<std::string> fileNames = any_cast<std::vector<std::string>>(optionsVector[1]);
  std::vector<std::string> correctFileExtensions = getCorrectExtensionsForTheType(fileType);
  for (const std::string& fileName : fileNames)
  {
    if (std::find(correctFileExtensions.begin(), correctFileExtensions.end(), JPetCommonTools::exctractFileNameSuffix(fileName)) ==
        correctFileExtensions.end())
    {
      ERROR("Wrong extension of file: " + fileName);
      return false;
    }
  }
  return true;
}

std::vector<std::string> JPetOptionValidator::getCorrectExtensionsForTheType(std::string fileType)
{
  if (fileType == "scope")
  {
    return {".json"};
  }
  else if (fileType == "zip")
  {
    return {".gz", ".xz", ".bz2", ".zip"};
  }
  else if (fileType == "mcGeant")
  {
    return {".root"};
  }
  else
  {
    return {"." + fileType};
  }
}

bool JPetOptionValidator::isRunIDValid(std::pair<std::string, boost::any> option)
{
  if (any_cast<int>(option.second) <= 0)
  {
    ERROR("Run id must be a number larger than 0.");
    return false;
  }
  return true;
}

bool JPetOptionValidator::isDetectorValid(std::pair<std::string, boost::any> option)
{
  if (any_cast<std::string>(option.second) == "bar" || any_cast<std::string>(option.second) == "barrel" ||
      any_cast<std::string>(option.second) == "mod" || any_cast<std::string>(option.second) == "modular")
  {
    return true;
  }
  else
  {
    ERROR("Provided detector type not found. Use '-k barrel' or '-k modular'");
    return false;
  }
}

bool JPetOptionValidator::isLocalDBValid(std::pair<std::string, boost::any> option)
{
  if (!JPetCommonTools::ifFileExisting(any_cast<std::string>(option.second)))
  {
    ERROR("File doed not exist.");
    return false;
  }
  return true;
}

bool JPetOptionValidator::areFilesValid(std::pair<std::string, boost::any> option)
{
  std::vector<std::string> fileNames = any_cast<std::vector<std::string>>(option.second);
  for (unsigned int i = 0; i < fileNames.size(); i++)
  {
    if (!JPetCommonTools::ifFileExisting(fileNames[i]))
    {
      ERROR("File : " + fileNames[i] + " does not exist.");
      return false;
    }
  }
  return true;
}

bool JPetOptionValidator::isOutputDirectoryValid(std::pair<std::string, boost::any> option)
{
  if (!JPetCommonTools::isDirectory(any_cast<std::string>(option.second)))
  {
    ERROR("Output directory does not exist.");
    return false;
  }
  return true;
}

JPetOptionValidator::ManyOptionsWrapper::ManyOptionsWrapper(std::initializer_list<boost::any> options) { optionsVector = options; }

std::vector<boost::any> JPetOptionValidator::ManyOptionsWrapper::getOptionsVector() { return optionsVector; }
