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
 *  @file JPetPM.h
 */

#ifndef _JPET_PM_
#define _JPET_PM_

#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include "./JPetScin/JPetScin.h"
#include "./JPetLoggerInclude.h"
#include "./JPetFEB/JPetFEB.h"
#include "TNamed.h"
#include <utility>
#include <TRef.h>

class JPetScin;

/**
 * @brief Representation of a photomultiplier.
 *
 * Parametric class representing database information of a single photomultiplier.
 */
class JPetPM: public TNamed
{
public:
  enum Side {SideA, SideB};
  enum GainNumber {kFirst, kSecond};
  JPetPM();
  explicit JPetPM(bool isNull);
  explicit JPetPM(int id, std::string description);
  JPetPM(Side side, int id, int HVset, int HVopt,
    std::pair<float, float> HVgainNumber, std::string description);
  JPetPM(JPetPM const&);
  ~JPetPM();
  static JPetPM& getDummyResult();
  bool operator==(const JPetPM& pm) const;
  bool operator!=(const JPetPM& pm) const;
  void setSide(Side side);
  void setHVset(int set);
  void setHVopt(int opt);
  void setHVgain(float g1, float g2);
  void setHVgain(const std::pair<float, float>& gain);
  void setFEB(JPetFEB& p_FEB);
  void setScin(JPetScin& p_scin);
  void setBarrelSlot(JPetBarrelSlot& p_barrelSlot);
  int getID() const;
  Side getSide() const;
  int getHVset() const;
  int getHVopt() const;
  float getHVgain(GainNumber nr);
  std::pair<float, float> getHVgain();
  const JPetFEB& getFEB() const;
  bool hasFEB() const;
  JPetScin& getScin() const;
  JPetBarrelSlot& getBarrelSlot() const;
  std::string getDescription() const;
  bool isNullObject() const;

protected:
  void clearTRefFEBs();
  void clearTRefScin();
  void clearTRefBarrelSlot();

#ifndef __CINT__
  Side fSide = SideA;
  int fID = 0;
  int fHVset = 0;
  int fHVopt = 0;
  std::pair<float, float> fHVgain;
  std::string fDescription = "";
  bool fIsNullObject = false;
#else
  Side fSide;
  int fID;
  int fHVset;
  int fHVopt;
  std::pair<float, float> fHVgain;
  std::string fDescription;
  bool fIsNullObject;
#endif
  TRef fTRefFEB;
  TRef fTRefScin;
  TRef fTRefBarrelSlot;

  friend class JPetParamManager;

  ClassDef(JPetPM, 5);
};

#endif
