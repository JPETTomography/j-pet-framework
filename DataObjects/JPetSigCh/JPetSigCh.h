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
 *  @file JPetSigCh.h
 */

#ifndef _JPETSIGCH_H_
#define _JPETSIGCH_H_

#include "./JPetTOMBChannel/JPetTOMBChannel.h"
#include "./JPetLoggerInclude.h"
#include "./JPetFEB/JPetFEB.h"
#include "./JPetTRB/JPetTRB.h"
#include "./JPetPM/JPetPM.h"
#include <TClass.h>
#include <cassert>
#include <vector>
#include <TRef.h>

/**
 * @brief Data class representing a SIGnal from a single tdc Channel.
 *
 * Represents time of signal from one PMT crossing a certain voltage threshold
 * at either leading or trailing edge of the signal.
 * @todo Tests are outdated
 */
class JPetSigCh: public TObject
{
public:
  enum EdgeType
  {
    Trailing, Leading
  };
  const static float kUnset;
  JPetSigCh() {
    init();
  }
  JPetSigCh(EdgeType Edge, float EdgeTime);
  ~JPetSigCh() {}

  /**
   * @brief Used to obtain the time value carried by the TDC signal.
   *
   * @return time with respect to the end of the time window [ps]
   */
  inline float getValue() const {
    return fValue;
  }

  /**
   * @brief Used to obtain the type of the signal information
   *
   * Time at either trailing edge or leading edge of the signal
   */
  inline EdgeType getType() const {
    return fType;
  }

  inline const JPetPM & getPM() const {
    if(fPM.GetObject()) return (JPetPM&) *fPM.GetObject();
    else {
      ERROR("No JPetPM slot set, Null object will be returned");
      return JPetPM::getDummyResult();
    }
  }

  inline const JPetTRB & getTRB() const {
    if(fTRB.GetObject()) return (JPetTRB&) *fTRB.GetObject();
    else {
      ERROR("No JPetTRB slot set, Null object will be returned");
      return JPetTRB::getDummyResult();
    }
  }

  inline const JPetFEB & getFEB() const {
    if(fFEB.GetObject()) return (JPetFEB&) *fFEB.GetObject();
    else {
      ERROR("No JPetFEB slot set, Null object will be returned");
      return JPetFEB::getDummyResult();
    }
  }

  inline const JPetTOMBChannel & getTOMBChannel() const {
    if(fTOMBChannel.GetObject()) return (JPetTOMBChannel&) *fTOMBChannel.GetObject();
    else {
      ERROR("No JPetTOMBChannel slot set, Null object will be returned");
      return JPetTOMBChannel::getDummyResult();
    }
}

  /**
   * A proxy method for quick access to DAQ channel number ignorantly of what a TOMBCHannel is
   */
  inline int getChannel() const {
    return getTOMBChannel().getChannel();
  }

  inline void setPM(const JPetPM & pm) {
    fPM = const_cast<JPetPM*>(&pm);
  }

  inline void setTRB(const JPetTRB & trb) {
    fTRB = const_cast<JPetTRB*>(&trb);
  }

  inline void setFEB(const JPetFEB & feb) {
    fFEB = const_cast<JPetFEB*>(&feb);
  }

  inline void setTOMBChannel(const JPetTOMBChannel & channel) {
    fTOMBChannel = const_cast<JPetTOMBChannel*>(&channel);
  }

  // Set time [ps]
  inline void setValue(float val) {
    fValue = val;
  }

  inline void setType(EdgeType type) {
    fType = type;
  }

  inline void setThreshold(float thr) {
    fThreshold = thr;
  }

  inline void setDAQch(Int_t daqch) {
    fDAQch = daqch;
  }

  inline float getThreshold() const {
    return fThreshold;
  }

  inline Int_t getDAQch() const {
    return fDAQch;
  }

  /**
   * @brief Get the number of this threshold on a certain edge.
   *
   * The thresholds are numbered starting from 1 according to ascending order of their corresponding DAQ channels.
   */
  inline unsigned int getThresholdNumber() const {
    return fThresholdNumber;
  }

  /**
   * @brief Set the number of this threshold on a certain edge.
   *
   * The thresholds are numbered starting from 1 according to ascending order of their corresponding DAQ channels.
   */
  inline void setThresholdNumber(unsigned int threshold_number) {
    fThresholdNumber = threshold_number;
  }

  /**
   * @brief Compares this SigCh with another by their threshold value
   *
   * This is a static function for use as Compare function with STL containers
   *
   * @return true if first argument should go before the second one.
   */
  static bool compareByThresholdValue(const JPetSigCh & A, const JPetSigCh & B);

  /**
   * @brief Compares this SigCh with another by their threshold numbers
   *
   * This is a static function for use as Compare function with STL containers
   *
   * @return true if first argument should go before the second one.
   */
  static bool compareByThresholdNumber(const JPetSigCh & A, const JPetSigCh & B);

  void Clear(Option_t * = "");

  ClassDef(JPetSigCh, 7);

protected:
  EdgeType fType; ///< type of the SigCh: Leading or Trailing
  float fValue; ///< value of time [ps]
  unsigned int fThresholdNumber;
  float fThreshold; ///< value of threshold [mV]
  int fDAQch; ///< Number of DAQ channel from the raw HLD file
  TRef fPM;
  TRef fFEB;
  TRef fTRB;
  TRef fTOMBChannel;

  void init();
};

#endif
