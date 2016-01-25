/**
 *  @copyright Copyright (c) 2015, J-PET collaboration
 *  @file JPetSimplePhysSignalReco.h
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief Class implements the simple physical signal reconstruction 
 */

#ifndef _JPETSIMPLEPHYSSIGNALRECO_H_
#define _JPETSIMPLEPHYSSIGNALRECO_H_

#include "../JPetTask/JPetTask.h"
#include "../JPetPhysSignal/JPetPhysSignal.h"
#include "../JPetRecoSignal/JPetRecoSignal.h"

class JPetWriter;

class JPetSimplePhysSignalReco : public JPetTask
{
public:
  JPetSimplePhysSignalReco();
  virtual ~JPetSimplePhysSignalReco();

  virtual void exec();
  virtual void terminate();
  virtual void setWriter(JPetWriter* writer) {fWriter =writer;}
  inline int getAlpha() const { return fAlpha; }
  inline float getThresholdSel() const { return fThresholdSel; }
  inline void setAlpha(int val) { fAlpha = val; }
  inline void setThresholdSel(float val) { fThresholdSel = val; }
  void readConfigFileAndSetAlphaAndThreshParams(const char* filename);

private:
  JPetPhysSignal createPhysSignal(JPetRecoSignal& signals);
  void savePhysSignal( JPetPhysSignal signal);
  int fAlpha;
  float fThresholdSel;
  JPetWriter* fWriter;

};
#endif

