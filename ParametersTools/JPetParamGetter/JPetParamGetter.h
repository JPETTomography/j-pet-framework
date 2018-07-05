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
 *  @file JPetParamGetter.h
 */

#ifndef JPET_PARAM_GETTER_H
#define JPET_PARAM_GETTER_H

#include "./JPetLoggerInclude.h"
#include "JPetParamConstants.h"
#include <string>
#include <map>

typedef std::map<std::string, std::string> ParamObjectDescription;
typedef std::map<int, ParamObjectDescription> ParamObjectsDescriptions;
typedef std::map<int, int> ParamRelationalData;

/**
 * @brief An interface classes can implement to return JPetParamBank objects.
 * @todo Typedefs are ugly, if you are reading this and we upgraded
 * to ROOT 6 please change to using...
 */
class JPetParamGetter
{
public:
  virtual ParamObjectsDescriptions getAllBasicData(ParamObjectType type, const int runId) = 0;
  virtual ParamRelationalData getAllRelationalData(ParamObjectType type1, ParamObjectType type2, const int runId) = 0;
  virtual ~JPetParamGetter() {};
  static int getTOMBChannelFromDescription(std::string p_desc);
};

#endif /* !JPET_PARAM_GETTER_H */
