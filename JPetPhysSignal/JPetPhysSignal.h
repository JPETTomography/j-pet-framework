/**
 *  @copyright Copyright (c) 2014, Aleksander Gajos
 *  @file JPetPhysSignal.h
 *  @author Aleksander Gajos, alek.gajos@gmail.com
 */

#ifndef JPETPHYSSIGNAL_H
#define JPETPHYSSIGNAL_H

#include "../JPetBaseSignal/JPetBaseSignal.h"
#include "../JPetRecoSignal/JPetRecoSignal.h"

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

private:
  double fTime; ///< one time reconstructed for the whole signal [ps]
  double fQualityOfTime; ///< quantitative measure of the time reconstruction quality (scale is yet to be decided)
  double fPhe; ///< Number of Photoelectrons corresponding to the whole signal []
  double fQualityOfPhe; ///< quantitative measure of the Phe reconstruction quality (scale is yet to be decided)

  JPetRecoSignal fRecoSignal;

ClassDef(JPetPhysSignal, 1);
};
#endif /*  !JPETPHYSSIGNAL_H */
