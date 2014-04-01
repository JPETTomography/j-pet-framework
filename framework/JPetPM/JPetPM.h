#ifndef _JPET_PM_
#define _JPET_PM_

#include "TNamed.h"
#include <utility>

class JPetPM: public TNamed 
{
 public:
  enum Side {kLeft, kRight};
  enum GainNumber {kFirst, kSecond};

  JPetPM();
  inline Side getSide() const { return fSide; }
  inline int getID() const { return fID; }
  inline int getHVset() const { return fHVset; }
  inline int getHVopt() const { return fHVopt; }
  inline float getHVgain(GainNumber nr) { return (nr == kFirst) ? fHVgain.first : fHVgain.second; }
  inline std::pair<float, float> getHVgain() { return fHVgain; }
  inline void setSide(Side side) { fSide = side; }
  inline void setID(int id) { fID = id; }
  inline void setHVset(int set) { fHVset = set; }
  inline void setHVopt(int opt) { fHVopt= opt; }
  inline void setHVgain(float g1, float g2) { fHVgain.first = g1; fHVgain.second = g2; }
  inline void setHVgain(const std::pair<float,float>& gain) { fHVgain = gain; }

 private:
  Side fSide;
  int fID;
  int fHVset;
  int fHVopt;
  std::pair<float, float> fHVgain;

  ClassDef(JPetPM, 1);
};

#endif
