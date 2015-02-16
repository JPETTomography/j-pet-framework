/**
 *  @copyright Copyright (c) 2014, Aleksander Gajos
 *  @file JPetRecoSignal.h
 *  @author Aleksander Gajos, alek.gajos@gmail.com
 */

#ifndef JPETRECOSIGNAL_H
#define JPETRECOSIGNAL_H

#include "../JPetBaseSignal/JPetBaseSignal.h"
#include "../JPetRawSignal/JPetRawSignal.h"

#include <vector>

///< stores a (time[ps], alplitude[mV]) pair
struct shapePoint
{
  shapePoint() :
      time(0), amplitude(0) {
  }
  ;
  shapePoint(double t, double a) :
      time(t), amplitude(a) {
  }
  ;
  double time;
  double amplitude;
};

/**
 * @brief Data class representing a signal during its physical reconstruction
 *
 * JPetRecoSignal is one level higher than JPetRawSignal. It represents the signal
 * during physical reconstruction of its shape and properties.
 * This class contains fields intended to store the complete shape of the signal
 * as well as properties such as amplitude, charge (from TOT), delay, etc.
 *
 * Processing of data from the Scope should start with this class rather than JPetRawSignal.
 *
 * Reconstructed signal properties stored in this class should be used to produce a JPetPhysSignal.
 */
class JPetRecoSignal: public JPetBaseSignal
{
public:

  enum PointsSortOrder
  {
    ByTime, ByAmplitude
  };

  /**
   * @brief Constructor
   *
   * @param points number of (time, amplitude) points in the representation of signal shape; give only when known (e.g. for scope signals)
   */
  JPetRecoSignal(const int points = 0);

  virtual ~JPetRecoSignal();

  /**
   * @brief Get the shape of the signal as a vector of (time[ps], amplitude[mV]) pairs
   */
  const std::vector<shapePoint> & getShape() const {
    return fShape;
  }
  ;

  /**
   * @brief Set one point (i.e. (time, amplitude) pair) in the signal shape
   *
   * @param time time in [ps]
   * @param ampl aplitude in [mV]
   */
  void setShapePoint(double time, double ampl);

  /**
   * @brief Sort the vector of shapePoint-s by time (default) or amplitude (always ascending)
   *
   * @param order either JPetRecoSignal::ByTime or JPetRecoSignal::ByAmplitude
   */
  void sortShapePoints(PointsSortOrder order = ByTime);

  /**
   * @brief Get calculated amplitude of the signal
   *
   * @return signal amplitude in [mV]
   *
   * Note: the amplitude is not calculated automatically. The user should calculate the amplitude
   * and store it in the RecoSignal with the setAmplitude() method.
   */
  double getAmplitude() const {
    return fAmplitude;
  }

  /**
   * @brief Get calculated amplitude of the signal
   *
   * @param amplitude calculated signal amplitude in [mV]
   *
   * Note: the amplitude is not calculated automatically. The user should calculate the amplitude
   * and store it in the RecoSignal with this method.
   */
  void setAmplitude(double amplitude) {
    fAmplitude = amplitude;
  }

  double getCharge() const {
    return fCharge;
  }

  void setCharge(double charge) {
    fCharge = charge;
  }

  /**
   * @return signal delay in [ps]
   */
  double getDelay() const {
    return fDelay;
  }

  /**
   * @param delay signal delay in [ps]
   */
  void setDelay(double delay) {
    fDelay = delay;
  }

  /**
   * @return signal offset in [mV]
   */
  double getOffset() const {
    return fOffset;
  }

  /**
   * @param offset signal offset in [mV]
   */
  void setOffset(double offset) {
    fOffset = offset;
  }

  /**
   * @brief Get the JPetRawSignal object from which this RecoSignal was created
   */
  const JPetRawSignal& getRawSignal() const {
    /// @todo: return null object if raw signal was not set (e.g. for scope signals)
    return fRawSignal;
  }

  /**
   * @brief Set the JPetRawSignal object from which this RecoSignal was created
   */
  void setRawSignal(const JPetRawSignal& rawSignal);

  /**
   * @brief Get a map of (threshold[mV], time[ps]) pairs for reconstructed times at arbitrary thresholds
   *
   * The times at arbitrary thresholds reconstructed by the user (e.g. by interpolation
   * of the points measured by from FEE boards) are stored in an STL map, with threshold values
   * as keys.
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
  std::map<float, float>& getRecoTimesAtThreshold() {
    return fRecoTimesAtThreshold;
  }

  /**
   * @brief Set the reconstructed time at an arbitrary threshold
   *
   * @param threshold arbitrary threshold for which the time is given; either in mV or without unit if constant-fraction
   * @param time time at which signal crossed the arbitrary threshold
   *
   * The times at arbitrary thresholds reconstructed by the user (e.g. by interpolation
   * of the points measured by from FEE boards) are stored in an STL map, with threshold values
   * as keys.
   *
   * Convention:
   * if threshold < 1, it means a fraction of the signal (in the constant-fraction sense)
   * if threshold > 1, it means an absolute value of the threshold in miliVolts
   */
  void setRecoTimeAtThreshold(float threshold, float time) {
    fRecoTimesAtThreshold[threshold] = time;
  }

  /**
   * @brief Get the reconstructed time at an arbitrary threshold
   *
   * @param threshold arbitrary threshold for which the time is given; either in mV or without unit if constant-fraction
   *
   * Convention for threshold values:
   * if threshold < 1, it means a fraction of the signal (in the constant-fraction sense)
   * if threshold > 1, it means an absolute value of the threshold in miliVolts
   *
   * @return time at threshold in [ps], or 0 if time for the given threshold was not set.
   */
  float getRecoTimeAtThreshold(float threshold) const {
    return const_cast<std::map<float, float> & > (fRecoTimesAtThreshold)[threshold];
  }

private:

  static bool compareShapePointsTime(const shapePoint & A,
                                     const shapePoint & B);
  static bool compareShapePointsAmpl(const shapePoint & A,
                                     const shapePoint & B);

  std::vector<shapePoint> fShape; ///< Signal shape represented as (time, amplitude) pairs
  double fDelay;
  double fAmplitude;
  double fOffset;
  double fCharge;

  JPetRawSignal fRawSignal;

  std::map<float, float> fRecoTimesAtThreshold;

ClassDef(JPetRecoSignal, 1)
  ;
};

#endif /*  !JPETRECOSIGNAL_H */
