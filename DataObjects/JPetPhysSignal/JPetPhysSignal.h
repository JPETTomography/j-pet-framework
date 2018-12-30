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
 *  @file JPetPhysSignal.h
 */

#ifndef JPETPHYSSIGNAL_H
#define JPETPHYSSIGNAL_H

#include "./JPetBaseSignal/JPetBaseSignal.h"
#include "./JPetRecoSignal/JPetRecoSignal.h"

/**
 * @brief Data class representing a physical signal reconstructed
 * in a single photomultiplier.
 *
 * This class contains the reconstructed physical quantities that characterize
 * the signal and are needed for further reconstruction of hits. One JPetPhysRignal
 * object should be created based on the information from one JPetRecoSignal object.
 * User can set reconstructed values and qualities of signal time and number of
 * photoelectrons.
 */
class JPetPhysSignal: public JPetBaseSignal
{
public:
  JPetPhysSignal();
  virtual ~JPetPhysSignal();
  bool isNullObject() const;
  explicit JPetPhysSignal(bool isNull);

  /**
   * Returns the reconstructed time of this signal in [ps].
   */
  inline float getTime() const {
    return fTime;
  }

  /**
   * Get the value, that describes the quality of reconstructed signal time
   */
  inline float getQualityOfTime() const {
    return fQualityOfTime;
  }

  /**
   * Sets the reconstructed time of this signal in [ps].
   */
  inline void setTime(float time) {
    fTime = time;
  }

  /**
   * Set the value, that describes the quality of reconstructed signal time
   */
  inline void setQualityOfTime(float qualityOfTime){
    fQualityOfTime = qualityOfTime;
  }

  /**
   * Get the number of photoelectrons
   */
  double getPhe() const {
    return fPhe;
  }

  /**
   * Set the number of photoelectrons
   */
  void setPhe(double phe) {
    fPhe = phe;
  }

  /**
   * Get the value, that describes the quality of reconstruction of number of photoelectrons
   */
  double getQualityOfPhe() const {
    return fQualityOfPhe;
  }

  /**
   * Set the value, that describes the quality of reconstruction of number of photoelectrons
   */
  void setQualityOfPhe(double qualityOfPhe) {
    fQualityOfPhe = qualityOfPhe;
  }

  /**
   * Get the Reconstructed Signal object, that this Physical Signal is based on
   */
  const JPetRecoSignal& getRecoSignal() const {
    return fRecoSignal;
  }

  void setRecoSignal(const JPetRecoSignal& recoSignal);
  void Clear(Option_t * opt = "");

private:
  double fTime;
  double fQualityOfTime;
  double fPhe;
  double fQualityOfPhe;
  JPetRecoSignal fRecoSignal;

protected:
  #ifndef __CINT__
  bool fIsNullObject = false;
  #else
  bool fIsNullObject;
  #endif

  ClassDef(JPetPhysSignal, 2);

};
#endif /* !JPETPHYSSIGNAL_H */
