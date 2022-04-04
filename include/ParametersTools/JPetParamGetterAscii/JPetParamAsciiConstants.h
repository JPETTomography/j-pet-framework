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
 *  @file JPetParamAsciiConstants.h
 */

#ifndef JPETPARAMASCIICONSTANTS_H
#define JPETPARAMASCIICONSTANTS_H

#include "JPetParamGetter/JPetParamConstants.h"
#include <map>

/**
 * @brief Constants for names in the json file format
 */
const std::map<ParamObjectType, std::string> objectsNames{{ParamObjectType::kSetup, "setup"},
                                                          {ParamObjectType::kLayer, "layer"},
                                                          {ParamObjectType::kSlot, "slot"},
                                                          {ParamObjectType::kScin, "scin"},
                                                          {ParamObjectType::kMatrix, "matrix"},
                                                          {ParamObjectType::kPM, "pm"},
                                                          {ParamObjectType::kChannel, "channel"},
                                                          {ParamObjectType::kDataSource, "data_source"},
                                                          {ParamObjectType::kDataModule, "data_module"}};

#endif /* !JPETPARAMASCIICONSTANTS_H */
