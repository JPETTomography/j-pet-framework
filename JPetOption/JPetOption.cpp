/**
 *  @copyright Copyright 2017 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetOption.cpp
 */

#include <iostream>
#include "./JPetOption.h"

JPetOption::JPetOption():
  fNameValue("_std::string", std::string("")),
  fTransformer(dummyTransform),
  fValidator(dummyValidator)
{ }

JPetOption::JPetOption(const std::string& name, const boost::any value, JPetOption::Validator valid, JPetOption::Transformer transform):
  fTransformer(transform),
  fValidator(valid)
{
  fNameValue = fTransformer(std::make_pair(name, value));
}

bool JPetOption::isValid() const
{
  return fValidator(fNameValue);
}

JPetOption::OptNameValPair JPetOption::getNameVal() const
{
  return fNameValue;
}
