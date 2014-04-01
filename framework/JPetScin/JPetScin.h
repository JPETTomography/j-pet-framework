#ifndef _JPETSCIN_H_
#define _JPETSCIN_H_

#include "TNamed.h"


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

 private:
  int fID;
  float fAttenLen;  /// attenuation length
  ScinDimensions fScinSize; /// @todo check if there is no problem with the ROOT dictionnary
  ClassDef(JPetScin, 1);
};

#endif
