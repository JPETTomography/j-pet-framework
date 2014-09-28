/**
 *  @copyright Copyright (c) 2013, Wojciech Krzemien
 *  @file JPetSignal.h
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 */

#ifndef JPETSIGNAL_H
#define JPETSIGNAL_H

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include <TNamed.h>
#include <TClonesArray.h>
#include <TRef.h>
#include <cassert>
#include <vector>

/**
 * @brief Data class representing a signal from a single photomultiplier
 *
 * The signal consists of two arrays of time values (JPetSigCh objects) - points probed on the leading and trailing edge. It  also contains characteristic values reconstructed for this signal using the points, such as reconstructed time and energy and quality of their reconstruction.
 */
class JPetSignal: public TNamed
{
 public:

  JPetSignal();

  virtual ~JPetSignal();


  /**
   * @brief Returns the time reconstructed for this signal using its leading-edge and trailing-edge points.
   *
   * The time is in picoseconds and is the ABSOLUTE time w.r.t. beginning of measurement.
   */
  inline float GetTime() const {
    assert(fTime >= 0);
    return fTime;
  }

  /**
   * @brief Sets the reconstructed time of this signal [ps].
   *
   * Intended to be used after a procedure which reconstructs the time using leading and trailing edge points of the signal. The time should be in picoseconds and should be the ABSLOUTE time w.r.t. beginning of measurement (it can be counted using the index of the TSlot * width of the time window).
   */
  inline void SetTime(float time){ fTime=time; }

  /**
   * @brief Sets the reconstructed energy of this signal [keV].
   *
   * Intended to be used after a procedure which reconstructs energy using leading and trailing edge points of the signal or using the charge from frontend electronics.
   */
  inline void SetEnergy(float energy){ fEnergy=energy; }

  /// Returns the energy reconstructed for this signal [keV].
  inline float GetEnergy() const {
    assert(fEnergy >= 0);
    return fEnergy;
  }
  
  /// Returns a quantitative measure of the time reconstruction quality (scale is yet to be decided)
  inline float GetQualityOfTime() const {
    assert(fQualityOfTime >= 0);
    return fQualityOfTime;
  }

  /// Returns a quantitative measure of the energy reconstruction quality (scale is yet to be decided)
  inline float GetQualityOfEnergy() const {
    assert(fQualityOfEnergy >= 0);
    return fQualityOfEnergy;
  }
  
  inline bool IsLeft() const {
    return fLeft;
  }

  /**
   * @brief Returns the number of points recorded on a leading or trailing edge of this signal.
   *
   * The number of points should be between 0 and 4 (ideal case) depending on whether time signals from all threshold were recorded or not.
   *
   * @param edge Either JPetSigCh::Leading or JPetSigCh::Trailing
   */
  int GetNPoints(JPetSigCh::EdgeType edge) const;

  /**
   * @brief Add a JPetSigCh object to the signal.
   *
   * The JPetSigCh object is automatically added to the array of trailing-edge or leading-edge points depending on the type which was set in it. The array is sorted afterwards so that the JPetSigCh objects are sorted by ascending value of their threshold.
   */  
  void AddPoint(const JPetSigCh& sigch);

  /**
   * @brief Returns a reference to an array of trailing-edge or leading-edge points of this signal.
   *
   * @param edge Either JPetSigCh::Leading or JPetSigCh::Trailing
   */
  const TClonesArray & GetPoints(JPetSigCh::EdgeType edge) const;

  /**
   * @brief Returns a reference to a single point from a trailing of leading edge of the signal
   *
   * Note that the points are sorted by their threshold values, so that i=0 and edge=JPetSigCh::Leading should return the first point of the leading edge.
   *
   * @param edge Either JPetSigCh::Leading or JPetSigCh::Trailing
   * @param i index of the point, should be between 0 and the value returned by GetNPoints(edge)-1
   */
  const JPetSigCh & GetPoint(int i, JPetSigCh::EdgeType edge) const;
  
  

  inline void SetPMID( Int_t pmid ) { fPMID = pmid; }
  inline Int_t GetPMID() const { return fPMID; }
  inline void SetPM(JPetPM * pm) { fPM = pm; }
  inline void SetBarrelSlot(JPetBarrelSlot * bs) { fBarrelSlot = bs; }
  inline JPetPM * GetPM() const { return (JPetPM*) fPM.GetObject(); }
  inline JPetBarrelSlot * GetBarrelSlot() const { return (JPetBarrelSlot*) fBarrelSlot.GetObject(); }
    
 private:
  double fTime; ///< absolute time reconstructed for the whole signal [ps]
  double fQualityOfTime; ///< quantitative measure of the time reconstruction quality (scale is yet to be decided)
  double fEnergy; ///< energy reconstructed for the whole signal [keV]
  double fQualityOfEnergy; ///< quantitative measure of the energy reconstruction quality (scale is yet to be decided)
  bool fLeft;
  TClonesArray fLeadingPoints; ///< array of JPetSigCh objects from leading edge of the signal
  TClonesArray fTrailingPoints; ///< array of JPetSigCh objects from trailing edge of the signal
  int fNLeading; ///< number of set leading edge points; needed for TClonesArray usage
  int fNTrailing;  ///< number of set trailing edge points; needed for TClonesArray usage

  // these members can be used for simple analysis
  // if no parametric objects are available
  Int_t fPMID; ///< ID of Photomultiplier

  // references to parametric objects
  TRef fPM; ///< Photomultiplier which recorded this signal
  TRef fBarrelSlot; ///< BarrelSlot containing the PM which recorded this signal

  ClassDef(JPetSignal, 1);
};
#endif /*  !JPETSIGNAL_H */
