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
 *  @file JPetCommonTools.h
 */

#include "JPetCommonTools.h"
#include <iostream>

/**
 * Function extracts from the input file name string
 * a substring that corresponds to the file data type
 * according to the J-PET convention. E.g. for input filename
 * "file.data.type.can.have.several.dots.root"
 * the returned data type should be
 * "data.type.can.have.several.dots"
 * The ".root" suffix is obligatory.
 */
std::string JPetCommonTools::extractDataTypeFromFileName(const std::string& filename)
{
  auto file = extractFileNameFromFullPath(filename);

  auto pos = file.find(".");
  if ( pos != std::string::npos ) {
    auto suffix = file.substr(pos + 1);
    auto pos2 = suffix.find(".root");
    if ( pos2 != std::string::npos ) {
      return suffix.erase(pos2);
    }
  }

  return "";
}

/**
 * Creates a pair int and const char* arguments to emulate int arc,
 * const char** argv parameters in commandLine="./programName.x -p test"
 * will be transformed to a array of const char c-strings
 * "./programName.x", "-p", "test"
 * The returned vector contains the dynamically allocated c-strings of
 * const char* that should be deallocated by delete to avoid the memory leak.
 */
std::vector<const char*> JPetCommonTools::createArgs(const std::string& commandLine)
{
  std::istringstream iss(commandLine);
  std::vector<std::string> args {std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>{}
                                };
  std::vector<const char*> args_char;
  std::transform(args.begin(), args.end(), std::back_inserter(args_char), [](const std::string & s) {
    char* pc = new char[s.size() + 1];
    std::strcpy(pc, s.c_str());
    return pc;
  });
  return args_char;
}

/**
 * Get std::string with current date and time
 */
const std::string JPetCommonTools::currentDateTime()
{
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
  return buf;
}

/**
 * Convert double to std::string
 */
std::string JPetCommonTools::doubleToString(double x)
{
  std::ostringstream out;
  out << x;
  return out.str();
}

/**
 * Converting std::string to int
 */
int JPetCommonTools::stringToInt(const std::string& str)
{
  std::istringstream in(str);
  int num;
  in >> num;
  return num;
}

/**
 * Function generates new file name by replacing the existing data type string
 * by the new newType string. There are two different cases:
 * 1) the original filename contains ".hld" suffix.
 * Then the suffix is replaced by newType + ".root"
 * 2) the original filename contains ".root" suffix.
 * Then the oldType +".root" is replaced by newType + ".root"
 */
std::string JPetCommonTools::replaceDataTypeInFileName(const std::string& filename, const std::string& newType)
{
  auto file = extractFileNameFromFullPath(filename);
  auto path = extractPathFromFile(filename);

  auto pos = file.find(".");
  if ( pos != std::string::npos ) {
    auto suffix = file.substr(pos + 1);
    auto prefix = file.erase(pos + 1);

    // handle HLD files as a special case
    if ( suffix == "hld" ) {
      auto result = prefix.append(newType).append(".root");
      if ( !path.empty() ) result = path.append("/").append(result);
      return result;
    }

    auto pos2 = suffix.find(".root");
    if ( pos2 != std::string::npos ) {
      auto root_extension = suffix.substr(pos2);
      auto result = prefix.append(newType).append(root_extension);
      if ( !path.empty() ) result = path.append("/").append(result);
      return result;
    }
  }

  return "";
}
