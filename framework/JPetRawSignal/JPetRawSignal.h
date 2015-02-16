/**
 *  @copyright Copyright (c) 2014, Aleksander Gajos
 *  @file JPetRawSignal.h
 *  @author Aleksander Gajos, alek.gajos@gmail.com
 */

#ifndef JPETRAWSIGNAL_H
#define JPETRAWSIGNAL_H

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetBaseSignal/JPetBaseSignal.h"
#include <vector>
#include <map>
#include <algorithm>

/**
 * @brief Data class representing a raw signal from a single photomultiplier as acquired by Front-End Electronics
 *
 * The signal consists of two arrays of time values (JPetSigCh objects) - points probed on the leading and trailing edge.
 */
class JPetRawSignal: public JPetBaseSignal
{
public:

  enum PointsSortOrder
  {
    ByThrValue, ///< Sort by threshold value
    ByThrNum ///< Sort by threshold number
  };

  /**
   * @brief Constructor
   *
   * @param points maximal number of points probed at one edge of the signal (defalult = 4)
   */
  JPetRawSignal(const int points = 4);
  virtual ~JPetRawSignal();

  /**
   * @brief Returns the number of points recorded on a leading or trailing edge of this signal.
   *
   * The number of points should be between 0 and the number set in the class constructor (default=4)
   * depending on whether time signals from all threshold were recorded or not.
   *
   * @param edge Either JPetSigCh::Leading or JPetSigCh::Trailing
   */
  int getNPoints(JPetSigCh::EdgeType edge) const;

  /**
   * @brief Add a JPetSigCh object to the signal.
   *
   * The JPetSigCh object is automatically added to the array
   * of trailing-edge or leading-edge points depending
   * on the type which was set in it. If its type is Charge,
   * it will be set as the TOT point.
   */
  void addPoint(const JPetSigCh& sigch);

  /**
   * @brief Returns a sorted vector of trailing-edge or leading-edge points of this signal.
   *
   * @param edge Either JPetSigCh::Leading or JPetSigCh::Trailing
   * @param sort_by JPetRawSignal::byThrValue or JPetRawSignal::byThrNum
   *
   * The vector of points will be sorted according to the specified order - by threshold values  (default) or by threshold numbers
   *
   */
  std::vector<JPetSigCh> getPoints(JPetSigCh::EdgeType edge,
                                   JPetRawSignal::PointsSortOrder order =
                                       JPetRawSignal::ByThrValue) const;

  /**
   * @brief Get a map with (threshold number, time [ps]) pairs.
   */
  std::map<int, double> getTimesVsThresholdNumber(JPetSigCh::EdgeType edge) const;

  /**
   * @brief Get a map with (threshold value [mV], time [ps]) pairs.
   */
  std::map<int, double> getTimesVsThresholdValue(JPetSigCh::EdgeType edge) const;

  inline int getNumberOfLeadingEdgePoints(void) const {
    return fLeadingPoints.size();
  }
  inline int getNumberOfTrailingEdgePoints(void) const {
    return fTrailingPoints.size();
  }

  const JPetSigCh & getTOTPoint() const;
  void setTOTPoint(const JPetSigCh & totSigCh);

  /**
   * @brief Get the Time Over Threshold value in [ps]
   *
   * @return Time Over Threshold value in [ps] or JpetSigCh::kUnset if TOT was not registered for this signal.
   */
  double getTOT() const;

private:
  std::vector<JPetSigCh> fLeadingPoints; ///< vector of JPetSigCh objects from leading edge of the signal
  std::vector<JPetSigCh> fTrailingPoints; ///< vector of JPetSigCh objects from trailing edge of the signal
  JPetSigCh fTOTPoint;

ClassDef(JPetRawSignal, 1)
  ;
};
#endif /*  !JPETRAWSIGNAL_H */
