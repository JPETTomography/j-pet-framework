/**
 * @file JPetLOR.cpp
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2013, Damian Trybek
 */

#include "./JPetLOR.h"

ClassImp(JPetLOR);

JPetLOR::JPetLOR() :
    TNamed("JPetLOR", "Event Structure"), fTime(0.0f), fQualityOfTime(0.0f),
    fTimeDiff(0.0f), fQualityOfTimeDiff(0.0f)
{
  fIsHitSet[0] = false;
  fIsHitSet[1] = false;
}

JPetLOR::JPetLOR(float Time, float QualityOfTime, JPetHit& firstHit,
                 JPetHit& secondHit) :
    TNamed("JPetLOR", "Event Structure"), fTime(Time),
    fQualityOfTime(QualityOfTime), fFirstHit(firstHit), fSecondHit(secondHit),
    fTimeDiff(0.0f), fQualityOfTimeDiff(0.0f)
{
  fIsHitSet[0] = true;
  fIsHitSet[1] = true;

  checkConsistency();
}

JPetLOR::~JPetLOR()
{
}

/** @brief Checks whether both Hit objects set in this LOR object
 *  come from different barrel slots and are properly time-ordered
 *  and logs an error message if not.
 *
 *  Pairing two hits from the same Barrel Slot (i.e. from the same scintillator)
 *  into a LOR would make no physical sense. This method ensures that it is not the case.
 *  Moreover, by convention the First Hit should have and earlier time that Second Hit.
 *  This method also ensures
 * 
 *  If the signals come from the same barrel slot and opposite-side PMTs, 
 *  this method only returns true.
 *  Otherwise, false is returned and an appropriate error message is logged.
 *
 *  @return true if both signals are consistently from the same barrel slot.
 */
bool JPetLOR::checkConsistency() const {
  
  if( !fIsHitSet[0] || !fIsHitSet[1] ){
    return true; // do not claim incosistency if signals are not set yet
  }

  int slot_a = getFirstHit().getBarrelSlot().getID();
  int slot_b = getSecondHit().getBarrelSlot().getID();
  
  if( slot_a == slot_b ){
    ERROR( Form("Hits added to LOR come from the same barrel slots: %d." ,
		slot_a) );
    return false; 
  }
  
  if( getFirstHit().getTime() > getSecondHit().getTime() ){
    ERROR( "Hits added to LOR are not in chronological order." );
    return false; 
  }
  
  return true;
}
