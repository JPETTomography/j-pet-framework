/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetShapedSignal.h
 */

#ifndef JPETSHAPEDSIGNAL_H
#define JPETSHAPEDSIGNAL_H

#include "Signals/JPetPMSignal/JPetPMSignal.h"
#include "Signals/JPetRecoSignal/JPetRecoSignal.h"
#include <map>
#include <vector>

struct shapePoint
{
  shapePoint() : time(0), amplitude(0){};
  shapePoint(double t, double a) : time(t), amplitude(a){};
  double time;
  double amplitude;
};

/**
 * @brief Data class representing a signal during its physical reconstruction
 *
 * JPetShapedSignal is one level higher than JPetPMSignal. It represents the signal
 * during physical reconstruction of its shape and properties.
 * This class contains fields intended to store the complete shape of the signal
 * as well as properties such as amplitude, charge (from TOT), delay, etc.
 * Note that the amplitude and other parameters are not calculated automatically.
 * Processing of data from the Scope should start with this class rather than JPetPMSignal.
 * Reconstructed signal properties stored in this class should be used to produce a JPetPhysSignal.
 */
class JPetShapedSignal : public JPetRecoSignal
{
public:
  enum PointsSortOrder
  {
    ByTime,
    ByAmplitude
  };
  JPetShapedSignal(const int points = 0);
  virtual ~JPetShapedSignal();

  /**
   * Get the shape of the signal as a vector of (time[ps], amplitude[mV]) pairs
   */
  const std::vector<shapePoint>& getShape() const { return fShape; };

  void setShapePoint(double time, double ampl);
  void sortShapePoints(PointsSortOrder order = ByTime);

  /**
   * @brief Get calculated amplitude of the signal
   *
   * @return signal amplitude in [mV]
   */
  double getAmplitude() const { return fAmplitude; }

  /**
   * @brief Get calculated amplitude of the signal
   *
   * @param amplitude calculated signal amplitude in [mV]
   *

   */
  void setAmplitude(double amplitude) { fAmplitude = amplitude; }

  /**
   * Get the calculated charge of the singal
   */
  double getCharge() const { return fCharge; }

  /**
   * Set the calculated charge of the singal
   */
  void setCharge(double charge) { fCharge = charge; }

  /**
   * Get the signal delay in [ps]
   */
  double getDelay() const { return fDelay; }

  /**
   * Set the signal delay in [ps]
   */
  void setDelay(double delay) { fDelay = delay; }

  /**
   * Get the signal offset in [mV]
   */
  double getOffset() const { return fOffset; }

  /**
   * Set the signal offset in [mV]
   */
  void setOffset(double offset) { fOffset = offset; }

  const JPetPM& getPM() const;
  void setPM(const JPetPM& pm);

  /**
   * @brief Get a map of (threshold[mV], time[ps]) pairs for reconstructed times at arbitrary thresholds
   *
   * The times at arbitrary thresholds reconstructed by the user
   * (e.g. by interpolation of the points measured by from FEE boards)
   * are stored in an STL map, with threshold values as keys.
   *
   * Convention:
   * if threshold < 1, it means a fraction of the signal (in the constant-fraction sense)
   * if threshold > 1, it means an absolute value of the threshold in miliVolts
   *
   * User can set times at thresholds either by the setRecoTimeAtThreshold method or by using
   * direclty the map returned by this metho (not that the retirned reference to the map
   * is not constant).
   *
   * @return map of (threshold[mV], time[ps]) pairs for reconstructed times at arbitrary thresholds
   */
  std::map<double, double>& getRecoTimesAtThreshold() { return fRecoTimesAtThreshold; }

  /**
   * @brief Set the reconstructed time at an arbitrary threshold
   *
   * @param threshold arbitrary threshold for which the time is given;
   * either in mV or without unit if constant-fraction
   * @param time time at which signal crossed the arbitrary threshold
   *
   * The times at arbitrary thresholds reconstructed by the user (e.g. by interpolation
   * of the points measured by from FEE boards) are stored in an STL map,
   * with threshold values as keys.
   *
   * Convention:
   * if threshold < 1, it means a fraction of the signal (in the constant-fraction sense)
   * if threshold > 1, it means an absolute value of the threshold in miliVolts
   */
  void setRecoTimeAtThreshold(double threshold, double time) { fRecoTimesAtThreshold[threshold] = time; }

  /**
   * @brief Get the reconstructed time at an arbitrary threshold
   *
   * @param threshold arbitrary threshold for which the time is given;
   * either in mV or without unit if constant-fraction
   *
   * Convention for threshold values:
   * if threshold < 1, it means a fraction of the signal (in the constant-fraction sense)
   * if threshold > 1, it means an absolute value of the threshold in miliVolts
   *
   * @return time at threshold in [ps], or 0 if time for the given threshold was not set.
   */
  double getRecoTimeAtThreshold(double threshold) const { return const_cast<std::map<double, double>&>(fRecoTimesAtThreshold)[threshold]; }

  void Clear(Option_t*) override;

private:
  static bool compareShapePointsTime(const shapePoint& a, const shapePoint& b);
  static bool compareShapePointsAmpl(const shapePoint& a, const shapePoint& b);
  std::map<double, double> fRecoTimesAtThreshold;
  std::vector<shapePoint> fShape;
  TRef fPM = nullptr;
  double fDelay;
  double fAmplitude;
  double fOffset;
  double fCharge;

  ClassDef(JPetShapedSignal, 1);
};

#endif /* !JPETSHAPEDSIGNAL_H */
