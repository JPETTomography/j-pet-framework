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
 *  @file JPetOptions2.h
 */

#ifndef JPETOPTIONS2_H 
#define JPETOPTIONS2_H 

#include <map>
#include <string>
#include <boost/any.hpp>

#include "../JPetOptionsInterface/JPetOptionsInterface.h"

class JPetOptions2: public JPetOptionsInterface
{
  public:
  typedef std::map<std::string, boost::any> Options;

  explicit JPetOptions2(const Options& opts);
  inline Options getOptions() const {
    return fOptions;
  }
  
  protected:
  Options fOptions;

};
#endif /*  !JPETOPTIONS2_H */
