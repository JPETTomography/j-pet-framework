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
 *  @file JPetOptionsTypeHandler.h
 */

#ifndef JPETOPTIONSTYPEHANDLER_H
#define JPETOPTIONSTYPEHANDLER_H

#include <boost/any.hpp>
#include <vector>
#include <string>
#include <map>

/**
 * @brief Class handling the type of option provided by the user.
 */
class JPetOptionsTypeHandler
{
public:
  static std::map<std::string, std::string> anyMapToStringMap(
    const std::map<std::string, boost::any>& optionsMap);
  static std::vector<std::string> getAllowedTypes();
  static std::string getTypeOfOption(const std::string& option);
  static std::string getNameOfOption(const std::string& option);

private:
  static const std::vector<std::string> kAllowedTypes;
};
#endif /* !JPETOPTIONSTYPEHANDLER_H */
