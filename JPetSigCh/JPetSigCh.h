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
 *  @file JPetSigCh.h
 *  @brief description
 */

#ifndef _JPETSIGCH_H_
#define _JPETSIGCH_H_

#include <cassert>
#include <vector>
#include <TClass.h>
#include <TRef.h>

#include "../JPetPM/JPetPM.h"
#include "../JPetTRB/JPetTRB.h"
#include "../JPetFEB/JPetFEB.h"
#include "../JPetTOMBChannel/JPetTOMBChannel.h"
#include "../JPetLoggerInclude.h"

/**
 * @brief Data class representing a SIGnal from a single tdc CHannel.
 *
 * Contains either time corresponding to a single threshold and slope type of a front-end board or charge from a single PM (if available in a given setup).
 */
class JPetSigCh: public TNamed
{
public:
  enum EdgeType
  {
    Trailing, Leading, Charge
  };
  const static float kUnset;

  JPetSigCh() {
    Init();
  }
  JPetSigCh(EdgeType Edge, float EdgeTime);
  ~JPetSigCh() {
  }

  /**
   * @brief Used to obtain the time or charge carried by the TDC signal.
   *
   * @return either time with respect to beginning of the time window [ps] (TSlot) or charge (if getType()==Charge)
   */
  inline float getValue() const {
    return fValue;
  }

  /**
   * @brief Used to obtain the type of the signal information
   *
   * Trailing edge, leading edge or charge (Charge)
   */
  inline EdgeType getType() const {
    return fType;
  }

  inline const JPetPM & getPM() const {
    static JPetPM DummyResult(true);
    if(fPM.GetObject()) return (JPetPM&) *fPM.GetObject();
    else return DummyResult;
    
  }
  inline const JPetTRB & getTRB() const {
    static JPetTRB DummyResult(true);
    if(fTRB.GetObject()) return (JPetTRB&) *fTRB.GetObject();
    else return DummyResult;
  }
  inline const JPetFEB & getFEB() const {
    static JPetFEB DummyResult(true);
    if(fFEB.GetObject()) return (JPetFEB&) *fFEB.GetObject();
    else return DummyResult;
  }
  inline const JPetTOMBChannel & getTOMBChannel() const {
    static JPetTOMBChannel DummyResult(true);
    if(fTOMBChannel.GetObject()) return (JPetTOMBChannel&) *fTOMBChannel.GetObject();
    else return DummyResult;
}

  /**
   * A proxy method for quick access to DAQ channel number ignorantly of what a TOMBCHannel is
   */
  inline int getChannel() const {
    return getTOMBChannel().getChannel();
  }
  
  /**
   * Returns true if the value of the signal represents charge information (integral of the signal calculated by front-end board)
   */
  bool isCharge() const;

  /**
   * Returns true if the value of the signal represents time information from the TDC
   */
  bool isTime() const;

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

  // Set time wrt beginning of TSlot [ps] or charge
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
  static bool compareByThresholdNumber(const JPetSigCh & A,
                                       const JPetSigCh & B);
  
  ClassDef(JPetSigCh, 4);
  
protected:
  EdgeType fType; ///< type of the SigCh: Leading, Trailing (time) or Charge (charge)
  float fValue; ///< main value of the SigCh; either time [ps] (if fType is kRiging or Leading) or charge (if fType is Charge)

  unsigned int fThresholdNumber;
  float fThreshold; ///< value of threshold [mV]
  int fDAQch; ///< Number of DAQ channel from the raw HLD file

  TRef fPM;
  TRef fFEB;
  TRef fTRB;
  TRef fTOMBChannel;
  
  void Init();
};

#endif
