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
 * @brief Class representing a signal from a single photomultiplier
 *
 * The signal consists of two arrays of time values (JPetSigCh objects) - points probed on the falling and rising edge. It  also contains characteristic values reconstructed for this signal using the points, such as reconstructed time and energy and quality of their reconstruction.
 */
class JPetSignal: public TNamed
{
 public:

  JPetSignal();

  virtual ~JPetSignal();


  /// Returns the time reconstructed for this signal using its falling-edge and rising-edge points.
  inline float GetTime() const {
    assert(fTime >= 0);
    return fTime;
  }

  /**
   * @brief Sets the reconstructed time of this signal.
   *
   * Intended to be used after a procedure which reconstructs the time using falling and rising edge points of the signal.
   */
  inline void SetTime(float time){ fTime=time; }

  /**
   * @brief Sets the reconstructed time of this signal.
   *
   * Intended to be used after a procedure which reconstructs energy using falling and rising edge points of the signal or using the charge from frontend electronics.
   */
  inline void SetEnergy(float energy){ fEnergy=energy; }

  /// Returns the time reconstructed for this signal.
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
   * @brief Returns the number of points recorded on a falling or rising edge of this signal.
   *
   * The number of points should be between 0 and 4 (ideal case) depending on whether time signals from all threshold were recorded or not.
   *
   * @param edge Either JPetSigCh::kFalling or JPetSigCh::kRising
   */
  int GetNPoints(JPetSigCh::EdgeType edge) const;

  /**
   * @brief Add a JPetSigCh object to the signal.
   *
   * The JPetSigCh object is automatically added to the array of rising-edge or falling-edge points depending on the type ehich was set in it.
   */  
  void AddPoint(const JPetSigCh& sigch);

  /**
   * @brief Returns a reference to an array of rising-edge or falling-edge points of this signal.
   *
   * @param edge Either JPetSigCh::kFalling or JPetSigCh::kRising
   */
  const TClonesArray & GetPoints(JPetSigCh::EdgeType edge) const;

  inline void SetPMID( Int_t pmid ) { fPMID = pmid; }
  inline Int_t GetPMID() const { return fPMID; }
  inline void SetPM(JPetPM * pm) { fPM.SetObject( pm ); }
  inline void SetBarrelSlot(JPetBarrelSlot * bs) { fBarrelSlot.SetObject( bs ); }
  inline JPetPM * GetPM() const { return (JPetPM*) fPM.GetObject(); }
  inline JPetBarrelSlot * GetBarrelSlot() const { return (JPetBarrelSlot*) fBarrelSlot.GetObject(); }
    
 private:
  double fTime; ///< time reconstructed for the whole signal
  double fQualityOfTime; ///< quantitative measure of the time reconstruction quality (scale is yet to be decided)
  double fEnergy; ///< energy reconstructed for the whole signal
  double fQualityOfEnergy; ///< quantitative measure of the energy reconstruction quality (scale is yet to be decided)
  bool fLeft;
  TClonesArray fFallingPoints; ///< array of JPetSigCh objects from falling edge of the signal
  TClonesArray fRisingPoints; ///< array of JPetSigCh objects from rising edge of the signal
  int fNFalling; ///< number of set falling edge points; needed for TClonesArray usage
  int fNRising;  ///< number of set rising edge points; needed for TClonesArray usage

  // these members can be used for simple analysis
  // if no parametric objects are available
  Int_t fPMID; ///< ID of Photomultiplier

  // references to parametric objects
  TRef fPM; ///< Photomultiplier which recorded this signal
  TRef fBarrelSlot; ///< BarrelSlot containing the PM which recorded this signal

  ClassDef(JPetSignal, 1);
};
#endif /*  !JPETSIGNAL_H */
