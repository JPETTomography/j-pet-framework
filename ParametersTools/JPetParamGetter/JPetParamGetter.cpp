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
 *  @file JPetParamGetter.cpp
 */

#include <boost/lexical_cast.hpp>
#include "JPetParamGetter.h"
#include <boost/regex.hpp>

/**
 * Parsing the string description of a TOMB channel to extract the channel number
 * convention: tast 4 characters of the description represent the number
 * @todo Handle parsing error somehow
 */
int JPetParamGetter::getTOMBChannelFromDescription(std::string p_desc)
{

  const char * l_pattern = ".*\\s(\\d{1,4}).*";
  boost::regex l_regex(l_pattern);
  boost::smatch l_matches;
  int l_TOMB_no = -1;
  if (boost::regex_match(p_desc, l_matches, l_regex)) {
    l_TOMB_no = boost::lexical_cast<int>(l_matches[1]);
  } else {
    ERROR("Unable to parse TOMBInput description to get channel number.");
  }
  return l_TOMB_no;
}
