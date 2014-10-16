#ifndef JPET_TOMB_CHANNEL_H
#define JPET_TOMB_CHANNEL_H

#include "TNamed.h"
#include "../JPetFEB/JPetFEB.h"
#include "../JPetTRB/JPetTRB.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetBarrelSlot/JPetBarrelSlot.h"


/**
 * @brief Parametric class representing the abstract global channel number from the database.
 *
 * The TOMBChannel abstracts over the hardware channels of certain TRB and fron-end boards (FEB).
 */
class JPetTOMBChannel: public TNamed
{
protected:
  
  int m_id;
  std::string m_description;
  
public:
  JPetTOMBChannel(unsigned int p_channel);
  virtual ~JPetTOMBChannel(void);
  
  void setTRefFEB(JPetFEB& p_FEB){ fFEB = &p_FEB; }
  void setTRefTRB(JPetTRB& p_TRB){ fTRB = &p_TRB; }
  void setTRefPM(JPetPM& p_PM){ fPM = &p_PM; }
  void setThreshold(float p_threshold){ fThreshold = p_threshold; }
  
  JPetFEB * getTRefFEB()const{ return (JPetFEB*)fFEB.GetObject(); }
  JPetTRB * getTRefTRB()const{ return (JPetTRB*)fTRB.GetObject(); }
  JPetPM * getTRefPM()const{ return (JPetPM*)fPM.GetObject(); }
  float getThreshold()const{ return fThreshold; }
  unsigned int getChannel()const{ return fChannel; }

private:
  unsigned int fChannel;
  TRef fFEB;
  TRef fTRB;
  TRef fPM;
  TRef fScin; // @todo: add setters && getters for scin and slot
  TRef fBarrelSlot;
  float fThreshold;

  ClassDef(JPetTOMBChannel, 1);
};

#endif // JPET_TOMB_CHANNEL_H
