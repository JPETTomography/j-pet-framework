/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetOptionValidator.h
 */

#ifndef JPETOPTIONVALIDATOR_H
#define JPETOPTIONVALIDATOR_H

#include <boost/any.hpp>
#include <string>
#include <vector>
#include <map>

/**
 * @brief Class to validate the user defined options.
 */
class JPetOptionValidator
{
public:
  JPetOptionValidator();
  static std::vector<std::string> getCorrectExtensionsForTheType(std::string fileType);
  bool areCorrectOptions(const std::map<std::string, boost::any>& optionsMap, std::vector<std::string>& namesOfOptionsToBeValidated);
  static std::map<std::string, std::vector<bool(*)(std::pair <std::string, boost::any>)>> generateValidationMap();
  void addValidatorFunction(const std::string& name, bool(*validatorFunction)(std::pair <std::string, boost::any>));
  static bool isNumberBoundsInRangeValid(std::pair <std::string, boost::any> option);
  static bool isRangeOfEventsValid(std::pair <std::string, boost::any> option);
  static bool isCorrectFileType(std::pair <std::string, boost::any> option);
  static bool isFileTypeMatchingExtensions(std::pair<std::string, boost::any> option);
  static bool isRunIdValid(std::pair <std::string, boost::any> option);
  static bool isLocalDBValid(std::pair <std::string, boost::any> option);
  static bool areFilesValid(std::pair <std::string, boost::any> option);
  static bool isOutputDirectoryValid(std::pair <std::string, boost::any> option);
  static std::map<std::string, boost::any> addNonStandardValidators(const std::map<std::string, boost::any>& optionsMap);

  class ManyOptionsWrapper
  {
  public:
    ManyOptionsWrapper(std::initializer_list<boost::any>);
    std::vector<boost::any> getOptionsVector();
  private:
    std::vector<boost::any> optionsVector;
  };

private:
  std::map<std::string, std::vector<bool(*)(std::pair <std::string, boost::any>)> > fValidatorMap;
  static void addFileTypeAndNameValidator(std::map<std::string, boost::any>&);
};
#endif /* !JPETOPTIONVALIDATOR_H */
