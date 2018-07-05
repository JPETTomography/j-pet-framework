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
 *  @file JPetAdditionalValiators.h
 */
#ifndef J_PET_ADDITIONAL_VALIDATORS_H
#define J_PET_ADDITIONAL_VALIDATORS_H

#include <boost/any.hpp>

bool additionalCheckIfRunIdIsOk(std::pair <std::string, boost::any> option);

#endif /* J_PET_ADDITIONAL_VALIDATORS_H */
