#ifndef _JPETSCIN_H_
#define _JPETSCIN_H_

#include "TNamed.h"
#include <TRef.h>
#include "../JPetPM/JPetPM.h"


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
  JPetScin(int id, float attenLen, float length, float height, float width);
  inline int getID() const { return fID; }
  inline float getAttenLen() const { return fAttenLen; }
  inline ScinDimensions getScinSize() const { return fScinSize; }
  float getScinSize(Dimension dim) const;
  inline void setID(int id) { fID = id; }
  inline void setAttenLen(float attenLen) { fAttenLen = attenLen; }
  inline void setScinSize(ScinDimensions size) { fScinSize = size; }
  void setScinSize(Dimension dim, float value);

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
  
 private:
  int fID;
  float fAttenLen;  /// attenuation length
  ScinDimensions fScinSize; /// @todo check if there is no problem with the ROOT dictionnary
  ClassDef(JPetScin, 1);
  
protected:
  TRef fTRefPMLeft;
  TRef fTRefPMRight;
  
  void clearTRefPMs()
  {
    fTRefPMLeft = NULL;
    fTRefPMRight = NULL;
  }
  
  friend class JPetParamManager;
};

#endif
