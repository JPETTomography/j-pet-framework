/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file JPetScopeConfigPOD.h
 */

#ifndef JPETSCOPECONFIGPOD_H
#define JPETSCOPECONFIGPOD_H

#include <vector>
#include <string>

namespace scope_config
{
struct Config {
  Config() {}
  Config(const std::string& name, const std::string& location,
    const std::vector<std::string> positions):
    fName(name), fLocation(location), fCollimatorPositions(positions) {}
  std::string fName;
  std::string fLocation;
  std::vector<std::string> fCollimatorPositions;
};
}

#endif /* !JPETSCOPECONFIGPOD_H */
