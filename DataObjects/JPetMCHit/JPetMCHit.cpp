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
 *  @file JPetMCHit.cpp
 */

#include "./JPetMCHit.h"
#include "./JPetLoggerInclude.h"

#include "TString.h"

ClassImp(JPetMCHit);

JPetMCHit::JPetMCHit() 
{
}

Float_t JPetMCHit::getScinPos() const  
{
  return fScin;
}

void JPetMCHit::setScinPos(Float_t scin)
{
  fScin = scin;
}
         
Int_t JPetMCHit::getPDGEncoding() const  
{
  return fPDGEncoding;
}

void JPetMCHit::setPDGEncoding(Int_t pdge) 
{
  fPDGEncoding = pdge;
}

Int_t JPetMCHit::getTrackID() const
{
  return fTrackID;
}

void JPetMCHit::setTrackID(Int_t tid)
{
  fTrackID = tid;
}

Int_t JPetMCHit::getParentID() const
{
  return fParentID;
}

void JPetMCHit::setParentID(Int_t pid)
{
  fParentID = pid;
}

Float_t JPetMCHit::getLocalPosX() const
{
  return fLocalPosX;
}

void JPetMCHit::setLocalPosX(Float_t lpx)
{
  fLocalPosX = lpx;     
}

Float_t JPetMCHit::getLocalPosY() const
{
  return fLocalPosY;
}

void JPetMCHit::setLocalPosY(Float_t lpy)
{
  fLocalPosY = lpy;
}

Float_t JPetMCHit::getLocalPosZ() const
{
  return fLocalPosZ;
}

void JPetMCHit::setLocalPosZ(Float_t lpz)
{
  fLocalPosZ= lpz;
}

Int_t JPetMCHit::getNumPhantomCompton() const
{
  return fNumPhantomCompton;
}

void  JPetMCHit::setNumPhantomCompton(Int_t npc)
{
  fNumPhantomCompton = npc;
}

Int_t JPetMCHit::getNumCrystalCompton() const
{
  return fNumCrystalCompton;
}

void JPetMCHit::setNumCrystalCompton(Int_t ncc)
{
   fNumCrystalCompton = ncc;
}

Int_t JPetMCHit::getNumPhantomRayleigh() const
{
  return fNumPhantomRayleigh;
}

void JPetMCHit::setNumPhantomRayleigh(Int_t npr)
{
  fNumPhantomRayleigh = npr;                        
}

Int_t JPetMCHit::getNumCrystalRayleigh() const									
{
  return fNumCrystalRayleigh;
}

void JPetMCHit::setNumCrystalRayleigh(Int_t ncr)
{
  fNumCrystalRayleigh = ncr;
}

Float_t JPetMCHit::getSourcePosX() const
{
  return fSourcePosX;
}

void JPetMCHit::setSourcePosX(Float_t spx)
{
  fSourcePosX = spx;
}

Float_t JPetMCHit::getSourcePosY() const
{
  return fSourcePosY;
}

void JPetMCHit::setSourcePosY(Float_t spy)
{
  fSourcePosY = spy;
}

Float_t JPetMCHit::getSourcePosZ() const
{
  return fSourcePosZ;
}

void JPetMCHit::setSourcePosZ(Float_t spz)
{
  fSourcePosZ = spz;
}

Int_t JPetMCHit::getSourceID() const
{
  return fSourceID;
}

void JPetMCHit::setSourceID(Int_t sid)
{
  fSourceID = sid;
}

Int_t JPetMCHit::getEventID() const
{
  return fEventID;
}

void JPetMCHit::setEventID(Int_t eid)
{
  fEventID = eid;
}

Int_t JPetMCHit::getRunID() const
{
  return fRunID;
}                                     

void JPetMCHit::setRunID(Int_t rid)
{
  fRunID = rid;
}

Char_t JPetMCHit::getProcessName() const  //spr czy zwraca TSring czy Char_t, gdy Char_t blad
{
  return fProcessName;
}

void JPetMCHit::setProcessName(Char_t prn)       
{
  fProcessName = prn;                
}















































































  
  
  
  
  
  
  
  
  
  
  
