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
