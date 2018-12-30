/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetTOMBChannel.h
 */

#ifndef JPET_TOMB_CHANNEL_H
#define JPET_TOMB_CHANNEL_H

#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include "./JPetScin/JPetScin.h"
#include "./JPetLoggerInclude.h"
#include "./JPetFEB/JPetFEB.h"
#include "./JPetTRB/JPetTRB.h"
#include "./JPetPM/JPetPM.h"
#include "TNamed.h"

/**
 * @brief Representation of a abstract global channel number.
 *
 * Parametric class representing database information of a TOMBChannel -
 * abstract of the hardware channels of certain TRB and fron-end boards (FEB).
 */
class JPetTOMBChannel: public TNamed
{
public:
  JPetTOMBChannel();
  explicit JPetTOMBChannel(unsigned int p_channel);
  explicit JPetTOMBChannel(int p_channel);
  explicit JPetTOMBChannel(bool isNull);
  virtual ~JPetTOMBChannel(void);
  void setFEB(JPetFEB& p_FEB);
  void setTRB(JPetTRB& p_TRB);
  void setPM(JPetPM& p_PM);
  void setThreshold(float p_threshold);
  const JPetFEB& getFEB() const;
  const JPetTRB& getTRB() const;
  const JPetPM& getPM() const;
  float getThreshold() const;
  int getChannel() const;
  std::string getDescription() const;
  unsigned int getLocalChannelNumber() const;
  unsigned int getFEBInputNumber() const;
  void setLocalChannelNumber(unsigned int lcn);
  void setFEBInputNumber(unsigned int fin);
  bool isNullObject() const;
  static  JPetTOMBChannel& getDummyResult();
  bool operator==(const JPetTOMBChannel& channel);
  bool operator!=(const JPetTOMBChannel& channel);

protected:
  int m_id;
  std::string m_description;
#ifndef __CINT__
  unsigned int fChannel = 0;
  TRef fFEB = NULL;
  TRef fTRB = NULL;
  TRef fPM = NULL;
  TRef fScin;
  TRef fBarrelSlot;
  float fThreshold = -1;
  unsigned int fLocalChannelNumber = 0;
  unsigned int fFEBInputNumber = 0;
  bool fIsNullObject = false;
#else
  unsigned int fChannel;
  TRef fFEB;
  TRef fTRB;
  TRef fPM;
  TRef fScin;
  TRef fBarrelSlot;
  float fThreshold;
  unsigned int fLocalChannelNumber;
  unsigned int fFEBInputNumber;
  bool fIsNullObject;
#endif

  ClassDef(JPetTOMBChannel, 4);
};

#endif /* JPET_TOMB_CHANNEL_H */
