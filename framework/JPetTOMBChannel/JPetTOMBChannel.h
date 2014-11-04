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
  JPetTOMBChannel();
  JPetTOMBChannel(unsigned int p_channel);
  virtual ~JPetTOMBChannel(void);
  
  void setFEB(JPetFEB& p_FEB){ fFEB = &p_FEB; }
  void setTRB(JPetTRB& p_TRB){ fTRB = &p_TRB; }
  void setPM(JPetPM& p_PM){ fPM = &p_PM; }
  void setThreshold(float p_threshold){ fThreshold = p_threshold; }
  
  const JPetFEB & getFEB()const{ return (JPetFEB&)*fFEB.GetObject(); }
  const JPetTRB & getTRB()const{ return (JPetTRB&)*fTRB.GetObject(); }
  const JPetPM & getPM()const{ return (JPetPM&)*fPM.GetObject(); }
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
