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
 *  @file JPetTimeWindowMC.h
 */

#ifndef _JPETTIMEWINDOWMC_H_
#define _JPETTIMEWINDOWMC_H_

#include <vector>
#include <map>
#include <TNamed.h>
#include <TClonesArray.h>
#include <iostream>
#include <JPetTimeWindow/JPetTimeWindow.h>

/**
 * @brief Container class representing a time window of the DAQ system
 *
 * A single TimeWindow contains many objects (referred to as "events") representing events which happened during one time window of the DAQ system.
 */
class JPetTimeWindowMC: public JPetTimeWindow
{
public:

  JPetTimeWindowMC() : JPetTimeWindow(), 
		       fMCHits(),
		       fDecayTrees()
  {}
  
  JPetTimeWindowMC(const char * event_type) : JPetTimeWindow(event_type),
					      fMCHits("TObject",1),
					      fDecayTrees("TObject",1)
  {}
  
  JPetTimeWindowMC(const char * event_type, const char * mcHit_type, const char * decayTree_type) :
    JPetTimeWindow(event_type),
    fMCHits(mcHit_type,2000),
    fDecayTrees(decayTree_type,2000)
  {}
  
  template<typename T>
  void addMCHit(const T & evt){
    dynamic_cast<T&>(*(fMCHits.ConstructedAt(fMCHitsCount++))) = evt;
  }
 
  template<typename T>
  void addDecayTree(const T & evt){
    dynamic_cast<T&>(*(fDecayTrees.ConstructedAt(fDecayTreesCount++))) = evt;
  }
 
  inline size_t getNumberOfMCHits() const {
    return fMCHitsCount;
  }

  inline size_t getNumberOfDecayTrees() const {
    return fDecayTreesCount;
  }

  template<typename T>
  inline const T& getMCHit(int i) const {
    return *(dynamic_cast<T*>(fMCHits[i]));
  }

  template<typename T>
  inline const T& getDecayTrees(int i) const {
    return *(dynamic_cast<T*>(fDecayTrees[i]));
  }


  virtual ~JPetTimeWindowMC(){
    fMCHits.Clear("C");
    fDecayTrees.Clear("C");
    fMCHitsCount = 0;
    fDecayTreesCount = 0;
  }

  virtual void Clear() {
    JPetTimeWindow::Clear();
    fMCHits.Clear("C");
    fDecayTrees.Clear("C");
    fMCHitsCount = 0;
    fDecayTreesCount = 0;
  }
  
  ClassDef(JPetTimeWindowMC, 1);

private:
  TClonesArray fMCHits;
  TClonesArray fDecayTrees;
  unsigned int fMCHitsCount = 0;
  unsigned int fDecayTreesCount = 0;
};

#endif
