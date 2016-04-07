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
 *  @file JPetTOMBChannel.h
 */

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
  int getChannel()const{ return fChannel; }
  std::string getDescription()const{ return m_description; }

  inline bool operator==(const JPetTOMBChannel& channel) { return getChannel() == channel.getChannel(); }
  inline bool operator!=(const JPetTOMBChannel& channel) { return getChannel() != channel.getChannel(); }

  /**
   * @brief Get a local number of the channel corresponding to this TOMBChannel, w.r.t. a single PM.
   *
   * All thresholds (together on leading and trailing edge) applied to a single PM signal can be ordered starting from 1, with an order corresponding to ascending order of DAQ channels assigned to the thresholds.
   * Therefore, if there are 4 thresholds applied to each signal edge, the local channel number should be between 1 and 8.
   */
  unsigned int getLocalChannelNumber() const { return fLocalChannelNumber; }
  void setLocalChannelNumber(unsigned int lcn) { fLocalChannelNumber = lcn; }

  /**
   * @brief Get the number of input channel (Numbering starts from 1) of the FEB which corresponds to this TOMB channel
   */
  unsigned int getFEBInputNumber() const { return fFEBInputNumber; }

  /**
   * @brief Set the number of input channel (Numbering starts from 1) of the FEB which corresponds to this TOMB channel
   */
  void setFEBInputNumber(unsigned int fin) { fFEBInputNumber = fin; }

  
private:
  unsigned int fChannel;
  TRef fFEB;
  TRef fTRB;
  TRef fPM;
  TRef fScin; // @todo: add setters && getters for scin and slot
  TRef fBarrelSlot;
  float fThreshold;
  unsigned int fLocalChannelNumber; ///< number of the threshold
  unsigned int fFEBInputNumber; ///< number of input of the FEB from which this channel comes
  
  ClassDef(JPetTOMBChannel, 3);
};

#endif // JPET_TOMB_CHANNEL_H
