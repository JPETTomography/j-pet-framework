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
 *  @file JPetPhysSignal.h
 */

#ifndef JPETPHYSSIGNAL_H
#define JPETPHYSSIGNAL_H

#include "./JPetBaseSignal/JPetBaseSignal.h"
#include "./JPetRecoSignal/JPetRecoSignal.h"

/**
 * @brief Data class representing a physical, reconstructed signal from a single photomultiplier
 *
 * This class contains the reconstructed physical quantities which characterize the signal
 * and which are needed for further reconstruction of hits.
 *
 * One JPetPhysRignal object should be created based on the information from one JPetRecoSignal object.
 */
class JPetPhysSignal: public JPetBaseSignal
{
public:

  JPetPhysSignal();
  virtual ~JPetPhysSignal();
  bool isNullObject() const;
  explicit JPetPhysSignal(bool isNull);
  /**
   * @brief Returns the time reconstructed for this signal using its leading-edge and trailing-edge points.
   *
   * The time is in picoseconds and is the time w.r.t. beginning of a time slot.
   */
  inline float getTime() const {
    return fTime;
  }

  /**
   * @brief Sets the reconstructed time of this signal [ps].
   *
   * Intended to be used after a procedure which reconstructs the time using leading and trailing edge points of the signal. The time should be in picoseconds.
   */
  inline void setTime(float time) {
    fTime = time;
  }

  inline void setQualityOfTime(float qualityOfTime){
    fQualityOfTime = qualityOfTime;
  }

  /// Returns a quantitative measure of the time reconstruction quality (scale is yet to be decided)
  inline float getQualityOfTime() const {
    return fQualityOfTime;
  }

  double getPhe() const {
    return fPhe;
  }

  void setPhe(double phe) {
    fPhe = phe;
  }

  /// Returns a quantitative measure of the Number of photoelectrons reconstruction quality (scale is yet to be decided)
  double getQualityOfPhe() const {
    return fQualityOfPhe;
  }

  void setQualityOfPhe(double qualityOfPhe) {
    fQualityOfPhe = qualityOfPhe;
  }

  const JPetRecoSignal& getRecoSignal() const {
    return fRecoSignal;
  }

  void setRecoSignal(const JPetRecoSignal& recoSignal);

  void Clear(Option_t * opt = "");
  
private:
  double fTime; ///< one time reconstructed for the whole signal [ps]
  double fQualityOfTime; ///< quantitative measure of the time reconstruction quality (scale is yet to be decided)
  double fPhe; ///< Number of Photoelectrons corresponding to the whole signal []
  double fQualityOfPhe; ///< quantitative measure of the Phe reconstruction quality (scale is yet to be decided)

  JPetRecoSignal fRecoSignal;
protected:
  #ifndef __CINT__
  bool fIsNullObject = false;
  #else
  bool fIsNullObject;
  #endif

ClassDef(JPetPhysSignal, 2);
};
#endif /*  !JPETPHYSSIGNAL_H */
