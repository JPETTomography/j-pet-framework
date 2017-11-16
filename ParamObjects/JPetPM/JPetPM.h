/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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

#include "TNamed.h"
#include <utility>
#include <TRef.h>
#include "../JPetFEB/JPetFEB.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetLoggerInclude.h"

class JPetScin;

/**
 * @brief Parametric class representing database information on parameters of a photomultiplier.
 *
 */
class JPetPM: public TNamed
{
public:
  enum Side {SideA, SideB};
  enum GainNumber {kFirst, kSecond};

  static  JPetPM& getDummyResult();

  JPetPM();
  explicit JPetPM(int id, std::string description);
  explicit JPetPM(bool isNull);
  JPetPM(Side side,
         int id,
         int HVset,
         int HVopt,
         std::pair<float, float> HVgainNumber,
         std::string description);
  JPetPM(JPetPM const&);
  ~JPetPM();

  bool operator==(const JPetPM& pm) const;
  bool operator!=(const JPetPM& pm) const;

  Side getSide() const;
  int getID() const;
  int getHVset() const;
  int getHVopt() const;
  float getHVgain(GainNumber nr);
  std::pair<float, float> getHVgain();
  std::string getDescription() const;
  void setSide(Side side);
  void setHVset(int set);
  void setHVopt(int opt);
  void setHVgain(float g1, float g2);
  void setHVgain(const std::pair<float, float>& gain);
  void setFEB(JPetFEB& p_FEB);
  bool hasFEB() const;
  const JPetFEB& getFEB() const;
  void setScin(JPetScin& p_scin);
  JPetScin& getScin() const;
  void setBarrelSlot(JPetBarrelSlot& p_barrelSlot);
  JPetBarrelSlot& getBarrelSlot() const;
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
