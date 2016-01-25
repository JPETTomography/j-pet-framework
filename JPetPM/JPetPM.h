#ifndef _JPET_PM_
#define _JPET_PM_

#include "TNamed.h"
#include <utility>
#include <TRef.h>
#include "../JPetFEB/JPetFEB.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetBarrelSlot/JPetBarrelSlot.h"

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
  JPetPM(Side side,
	 int id,
	 int HVset,
	 int HVopt,
	 std::pair<float, float> HVgainNumber);
  ~JPetPM();

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

  void setFEB(JPetFEB &p_FEB) { fTRefFEB = &p_FEB; }
  const JPetFEB& getFEB() const { return (JPetFEB&)*(fTRefFEB.GetObject()); }
  
  void setScin(JPetScin &p_scin) { fTRefScin = &p_scin; }
  JPetScin & getScin() const { return (JPetScin&)*(fTRefScin.GetObject()); }

  void setBarrelSlot(JPetBarrelSlot &p_barrelSlot){ fTRefBarrelSlot = &p_barrelSlot; }
  JPetBarrelSlot& getBarrelSlot() const { return (JPetBarrelSlot&)*(fTRefBarrelSlot.GetObject()); }	
  
  inline bool operator==(const JPetPM& pm) { return getID() == pm.getID(); }
  inline bool operator!=(const JPetPM& pm) { return getID() != pm.getID(); }
  
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
  Side fSide;
  int fID;
  int fHVset;
  int fHVopt;
  std::pair<float, float> fHVgain;

  ClassDef(JPetPM, 3);
  
protected:
  TRef fTRefFEB;
  TRef fTRefScin;
  TRef fTRefBarrelSlot;

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
