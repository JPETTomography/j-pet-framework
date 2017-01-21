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

  JPetPM();
  JPetPM(int id);
  JPetPM(Side side,
	 int id,
	 int HVset,
	 int HVopt,
	 std::pair<float, float> HVgainNumber);
  JPetPM(bool isNull);
  ~JPetPM();

  inline Side getSide() const { return fSide; }
  inline int getID() const { return fID; }
  inline int getHVset() const { return fHVset; }
  inline int getHVopt() const { return fHVopt; }
  inline float getHVgain(GainNumber nr) { return (nr == kFirst) ? fHVgain.first : fHVgain.second; }
  inline std::pair<float, float> getHVgain() { return fHVgain; }
  inline void setSide(Side side) { fSide = side; }
  inline void setHVset(int set) { fHVset = set; }
  inline void setHVopt(int opt) { fHVopt= opt; }
  inline void setHVgain(float g1, float g2) { fHVgain.first = g1; fHVgain.second = g2; }
  inline void setHVgain(const std::pair<float,float>& gain) { fHVgain = gain; }

  void setFEB(JPetFEB &p_FEB) { fTRefFEB = &p_FEB; }
  const JPetFEB &getFEB() const
  {
    if (fTRefFEB.GetObject()) return (JPetFEB &)*(fTRefFEB.GetObject());
    else {
      ERROR("No JPetFEB slot set, Null object will be returned");
      return JPetFEB::getDummyResult();
    }
  }

  void setScin(JPetScin &p_scin) { fTRefScin = &p_scin; }
  JPetScin &getScin() const
  {
    if (fTRefScin.GetObject()) return (JPetScin &)*(fTRefScin.GetObject());
    else {
      ERROR("No JPetScin slot set, Null object will be returned");
      return JPetScin::getDummyResult();
    }
  }

  void setBarrelSlot(JPetBarrelSlot &p_barrelSlot) { fTRefBarrelSlot = &p_barrelSlot; }
  JPetBarrelSlot &getBarrelSlot() const 
  {
    if(fTRefBarrelSlot.GetObject()) return (JPetBarrelSlot &)*(fTRefBarrelSlot.GetObject());
    else {
      ERROR("No JPetBarrelSlot slot set, Null object will be returned");
      return JPetBarrelSlot::getDummyResult();
    } 
  }

  inline bool isNullObject() const { return fIsNullObject; }

  static inline JPetPM& getDummyResult() {
    static JPetPM DummyResult(true);
    return DummyResult;
  }
  
  bool operator==(const JPetPM& pm) const;
  bool operator!=(const JPetPM& pm) const;
  
  /*std::vector<TRef> getTRefKBs() const { return fTRefKBs; }

  JPetFEB* getTRefKB(int p_index)
  {
    if(p_index < fTRefKBs.size())
    {
      return (JPetFEB*)fTRefKBs[p_index].GetObject();
    }
    return NULL;
  }
  
  void setTRefKBs(std::vector<TRef> &p_TRefKBs)
  {
    fTRefKBs = p_TRefKBs;
  }
  
  void addTRefKB(JPetFEB &p_KB)
  {
    fTRefKBs.push_back(&p_KB);
  }*/
  
 private:
  Side fSide = SideA;
  int fID = 0;
  int fHVset = 0;
  int fHVopt = 0;
  std::pair<float, float> fHVgain;

  ClassDef(JPetPM, 5);
  
protected:
  TRef fTRefFEB;
  TRef fTRefScin;
  TRef fTRefBarrelSlot;
  bool fIsNullObject = false;

  void clearTRefFEBs() { fTRefFEB = NULL; }
  void clearTRefScin() { fTRefScin = NULL; }
  void clearTRefBarrelSlot() { fTRefBarrelSlot = NULL; }
  
  /*std::vector<TRef> fTRefKBs;
  
  void clearTRefKBs()
  {
    fTRefKBs.clear();
  }*/
  
  friend class JPetParamManager;
};

#endif
