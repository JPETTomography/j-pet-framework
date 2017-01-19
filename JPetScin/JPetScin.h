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
 *  @file JPetScin.h
 */

#ifndef _JPETSCIN_H_
#define _JPETSCIN_H_

#include "TNamed.h"
#include <TRef.h>
#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetLoggerInclude.h"
//#include "../JPetPM/JPetPM.h"


/**
 * @brief Parametric class representing database information on parameters of a scintillator.
 *
 */
class JPetScin: public TNamed
{
 public:
  enum Dimension {kLength, kHeight, kWidth};
  struct ScinDimensions
  {
    ScinDimensions():fLength(0), fHeight(0), fWidth(0) { }
    ScinDimensions(float len, float h, float w):fLength(len), fHeight(h), fWidth(w) { }
    float fLength;
    float fHeight;
    float fWidth;
  };

  JPetScin();
  JPetScin(int id);
  JPetScin(int id, float attenLen, float length, float height, float width);
  JPetScin(bool isNull);
  ~JPetScin();

  inline int getID() const { return fID; }
  inline float getAttenLen() const { return fAttenLen; }
  inline ScinDimensions getScinSize() const { return fScinSize; }
  float getScinSize(Dimension dim) const;
  inline void setAttenLen(float attenLen) { fAttenLen = attenLen; }
  inline void setScinSize(ScinDimensions size) { fScinSize = size; }
  void setScinSize(Dimension dim, float value);

  void setBarrelSlot(JPetBarrelSlot &p_barrelSlot){ fTRefBarrelSlot = &p_barrelSlot; }
  JPetBarrelSlot& getBarrelSlot() const { 
    static JPetBarrelSlot DummyResult(true);
    if(fTRefBarrelSlot.GetObject()) return (JPetBarrelSlot&)*(fTRefBarrelSlot.GetObject());
    else {
      ERROR("No JPetBarrelSlot slot set, Null object will be returned");
      return DummyResult;
    }
  }

  inline bool isNullObject() const { return fIsNullObject; }
  
  inline bool operator==(const JPetScin& scin) const { return getID() == scin.getID(); }
  inline bool operator!=(const JPetScin& scin) const { return getID() != scin.getID(); }

  /*
  JPetPM* getTRefPMLeft() { return (JPetPM*)fTRefPMLeft.GetObject(); }
  JPetPM* getTRefPMRight(){ return (JPetPM*)fTRefPMRight.GetObject(); }
  
  void setTRefPMs(JPetPM &p_leftPM, JPetPM &p_rightPM)
  {    
    fTRefPMLeft = &p_leftPM;
    fTRefPMRight = &p_rightPM;
  }
  void setLeftTRefPM(JPetPM &p_PM)
  {
    fTRefPMLeft = &p_PM;
  }
  void setRightTRefPM(JPetPM &p_PM)
  {
    fTRefPMRight = &p_PM;
  }
  */
 private:
  int fID;
  float fAttenLen;  /// attenuation length
  ScinDimensions fScinSize; /// @todo check if there is no problem with the ROOT dictionnary
  bool fIsNullObject = false;
  ClassDef(JPetScin, 3);
  
protected:
  TRef fTRefBarrelSlot;
  
  void clearTRefBarrelSlot() { fTRefBarrelSlot = NULL; }
  /*
  TRef fTRefPMLeft;
  TRef fTRefPMRight;
  
  void clearTRefPMs()
  {
    fTRefPMLeft = NULL;
    fTRefPMRight = NULL;
  }
  */

  friend class JPetParamManager;
};

#endif
