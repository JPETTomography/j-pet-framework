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
 *  @file JPetOption.h
 */

#ifndef JPETOPTION_H
#define JPETOPTION_H

#include <functional>
#include <string>
#include <boost/any.hpp>

/**
 * @brief Helper class representing general option provided by the user e.g. loaded from a configuration file or command line.
 *
 */
class JPetOption
{
public:
  using OptNameValPair = std::pair<std::string, boost::any>;
  using Validator = std::function<bool(const OptNameValPair& pair)>;
  using Transformer = std::function<OptNameValPair(const OptNameValPair& pair)>;

  static bool dummyValidator(const OptNameValPair&) {
    return true;
  }
  static OptNameValPair dummyTransform(const OptNameValPair& pair) {
    return pair;
  }

  JPetOption(const std::string& name, const boost::any value, Validator valid = dummyValidator, Transformer transform = dummyTransform);
  JPetOption();
  virtual bool isValid() const;
  virtual OptNameValPair getNameVal() const;

protected:
  std::pair<std::string, boost::any> fNameValue;
  Transformer fTransformer;
  Validator fValidator;
};
#endif /*  !JPETOPTION_H */
