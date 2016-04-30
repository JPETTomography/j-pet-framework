/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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
struct BSlot {
  BSlot(int id = -1, bool active = false, const std::string& name = "", float theta = -1.0, int frame = -1):
    fId(id),
    fActive(active),
    fName(name),
    fTheta(theta),
    fFrame(frame) {
    /**/
  }
  int fId;
  bool fActive;
  std::string fName;
  float fTheta;
  int fFrame;
};

struct PM {
  PM(int id = -1, const std::string& prefix = ""):
    fId(id),
    fPrefix(prefix) {
  }
  int fId;
  std::string fPrefix;
};
struct Scin {
  Scin(int id = -1):
    fId(id) {
    /**/
  }
  int fId;
};

struct Config {
  Config() {
    /* */
  }
  Config(const std::string& name, const std::vector<BSlot>& bslots,
         const std::vector<PM>& pms, const std::vector<Scin>& scins,
         const std::string& location, const std::vector<std::string> positions):
    fName(name),
    fBSlots(bslots),
    fPMs(pms),
    fScins(scins),
    fLocation(location),
    fCollimatorPositions(positions) {
    /* */
  }
  std::string fName;
  std::vector<BSlot> fBSlots;
  std::vector<PM> fPMs;
  std::vector<Scin> fScins;
  std::string fLocation;
  std::vector<std::string> fCollimatorPositions;
};
}
#endif
