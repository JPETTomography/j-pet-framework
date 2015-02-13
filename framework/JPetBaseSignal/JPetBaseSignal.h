/**
 *  @copyright Copyright (c) 2014, Wojciech Krzemien
 *  @file JPetBaseSignal.h
 *  @author Aleksander Gajos, alek.gajos@gmail.com
 */

#ifndef JPETBASESIGNAL_H
#define JPETBASESIGNAL_H

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include <TNamed.h>
#include <TRef.h>

/**
 * @brief Base class for all signal data classes
 */
class JPetBaseSignal: public TNamed
{
public:

  JPetBaseSignal();
  virtual ~JPetBaseSignal();

  /**
   * @brief Set number of the Time Slot this signal belongs to.
   *
   * Should be set to the value returned by JPetTSlot::getIndex() for the respective TSlot
   */
  inline void setTSlotIndex(int index) {
    fTSlotIndex = index;
  }

  /**
   * @brief Get the number of the Time Slot this signal belongs to.
   */
  inline int getTSlotIndex() const {
    return fTSlotIndex;
  }

  inline void setPM(const JPetPM & pm) {
    fPM = const_cast<JPetPM*>(&pm);
  }

  inline void setBarrelSlot(const JPetBarrelSlot & bs) {
    fBarrelSlot = const_cast<JPetBarrelSlot*>(&bs);
  }

  /**
   * @brief Obtain a reference to the PhotoMultiplier parametric object related to this signal
   *
   */
  inline const JPetPM & getPM() const {
    return (JPetPM&) *fPM.GetObject();
  }

  /**
   * @brief Obtain a reference to the BarrelSlot parametric object related to this signal
   *
   */
  inline const JPetBarrelSlot & getBarrelSlot() const {
    return (JPetBarrelSlot&) *fBarrelSlot.GetObject();
  }

private:
  // references to parametric objects
  TRef fPM; ///< Photomultiplier which recorded this signal
  TRef fBarrelSlot; ///< BarrelSlot containing the PM which recorded this signal

  int fTSlotIndex; // index of original TSlot

ClassDef(JPetBaseSignal, 1)
  ;
};
#endif /*  !JPETBASESIGNAL_H */
