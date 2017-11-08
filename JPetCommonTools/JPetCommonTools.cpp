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
 *  @file JPetCommonTools.h
 */

#include "JPetCommonTools.h"
#include <iostream>


const std::string JPetCommonTools::currentDateTime()
{
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);

  strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

  return buf;
}

std::size_t JPetCommonTools::findSubstring(const std::string& p_string, const std::string& p_substring)
{
  // TODO check extension of the file. If necessary change it to another.
  return p_string.find(p_substring);
}

std::string JPetCommonTools::doubleToString(double x)
{
  std::ostringstream out;
  out << x;
  return out.str();
}

int JPetCommonTools::stringToInt(const std::string& str)
{
  std::istringstream in(str);
  int num;
  in >> num;
  return num;
}


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

 std::string JPetCommonTools::extractDataTypeFromFile(const std::string& filename)
{
  auto file = extractFileNameFromFullPath(filename);

  auto pos = file.find(".");
  if ( pos != std::string::npos ) {
    auto suffix = file.substr(pos+1);
    auto pos2 = suffix.find(".root");
    if( pos2 != std::string::npos ){
      return suffix.erase(pos2);
    }
  }
  
  return "";
}

std::string JPetCommonTools::replaceDataTypeInFile(const std::string& filename, const std::string& newType)
{
  auto file = extractFileNameFromFullPath(filename);
  auto path = extractPathFromFile(filename);
  
  auto pos = file.find(".");
  if ( pos != std::string::npos ) {
    auto suffix = file.substr(pos+1);
    auto prefix = file.erase(pos+1);
    auto pos2 = suffix.find(".root");
    if( pos2 != std::string::npos ){
      auto root_extension = suffix.substr(pos2);
      auto result = prefix.append(newType).append(root_extension);
      if( !path.empty() ) result = path.append("/").append(result);
      return result;
    }
  }
  
  return "";
}




