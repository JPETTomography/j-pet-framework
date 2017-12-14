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
 *  @file JPetHit.h
 */

#ifndef _JPETMCHIT_H_
#define _JPETMCHIT_H_

#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include "./JPetScin/JPetScin.h"
#include "./JPetPhysSignal/JPetPhysSignal.h"
#include "./JPetTimeWindow/JPetTimeWindow.h"
#include "./JPetHit/JPetHit.h"

#include "TNamed.h"
#include "TVector3.h"
#include <TRef.h>

#include <cstddef>
#include <utility>

class JPetBarrelSlot;
class JPetScin;
class JPetPhysSignal;
class JPetTimeWindow;

/**
 * @brief Data class representing a reconstructed hit of a photon in the scintillator strip.
 *
 * It contains two objects of type JPetPhysSignal (from "Side A" and "Side B" of the Barrel) which represent signals at two ends of a scintillator strip, from which the hit was reconstructed.
 */
class JPetMCHit : public JPetHit
{

public:

  JPetMCHit();
  
  Float_t getScinPos() const;
  void setScinPos(Float_t scin);    
  Int_t getPDGEncoding() const;  
  void setPDGEncoding(Int_t pdge);
  Int_t getTrackID() const;
  void setTrackID(Int_t tid);
  Int_t getParentID() const;
  void setParentID(Int_t pid);
  Float_t getLocalPosX() const;
  void setLocalPosX(Float_t lpx);  
  Float_t getLocalPosY() const;
  void setLocalPosY(Float_t lpy);
  Float_t getLocalPosZ() const;
  void setLocalPosZ(Float_t lpz);
  Int_t getNumPhantomCompton() const;
  void setNumPhantomCompton(Int_t npc);
  Int_t getNumCrystalCompton() const;
  void setNumCrystalCompton(Int_t ncc);
  Int_t getNumPhantomRayleigh() const;
  void setNumPhantomRayleigh(Int_t npr);    
  Int_t getNumCrystalRayleigh() const;
  void setNumCrystalRayleigh(Int_t ncr);
  Float_t getSourcePosX() const;
  void setSourcePosX(Float_t spx);
  Float_t getSourcePosY() const;
  void setSourcePosY(Float_t spy);
  Float_t getSourcePosZ() const;
  void setSourcePosZ(Float_t spz);
  Int_t getSourceID() const;
  void setSourceID(Int_t sid);
  Int_t getEventID() const;
  void setEventID(Int_t eid);
  Int_t getRunID() const;
  void setRunID(Int_t rid);
  Char_t getProcessName() const;  
  void setProcessName(Char_t prn);  
  
  
  
private:
  Float_t fScin = 0.0f; ///< reconstructed energy of the hit [keV]   
  
  Int_t fPDGEncoding = 0;         
  Int_t fTrackID = 0;          
  Int_t fParentID = 0;
  Float_t fLocalPosX = 0.0;
  Float_t fLocalPosY = 0.0;
  Float_t fLocalPosZ = 0.0;
  Int_t fNumPhantomCompton = 0;
  Int_t fNumCrystalCompton = 0;
  Int_t fNumPhantomRayleigh = 0;  
  Int_t fNumCrystalRayleigh = 0;
  Float_t fSourcePosX = 0.0;
  Float_t fSourcePosY = 0.0;
  Float_t fSourcePosZ = 0.0;
  Int_t fSourceID = 0;
  Int_t fEventID = 0;
  Int_t fRunID = 0;
  Char_t fProcessName;    
  
  
  ClassDef(JPetMCHit, 1);
};

#endif
