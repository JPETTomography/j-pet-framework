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
 *  @file JPetTimeWindow.h
 */

#ifndef _JPETTIMEWINDOW_H_
#define _JPETTIMEWINDOW_H_

#include <vector>
#include <map>
#include <TNamed.h>
#include "../JPetSigCh/JPetSigCh.h"
#include <TClonesArray.h>

/**
 * @brief Data class representing a time window of the TRB board.
 *
 * A single TSlot contains many SigCh objects representing TDC hits recorded during a time window of the TRB board.
 */
class JPetTimeWindow: public TNamed
{
public:
/// @todo think about changing TClonesArray to something else ? what about cleaning
  JPetTimeWindow() {
    SetName("JPetTimeWindow");
  }

  void addCh(JPetSigCh& new_ch);

  inline size_t getNumberOfSigCh() const {
    return fSigChannels.size();
  }
  inline const std::vector<JPetSigCh>& getSigChVect() const {
    return fSigChannels;
  }
  /**
   * @brief Get i-th SigCh object from this time window as if from an array
   *
   * @param i number of SigCh object to be returned; i should be between 0 and getNumberOfSigCh-1
   */
  inline const JPetSigCh& operator[](int i) const {
    return fSigChannels[i];
  }


  virtual ~JPetTimeWindow() {
    fSigChannels.clear();
  }

  /**
   * @brief Get the index number of this TSlot
   *
   * Each TSlot (time window) in a HLD file is assigned an index number, counting from first TSlot in the file. This number may be useful if empty TSlots are skipped during analysis.
   * @oaram index a squential number of this TSlot counting from sirst TSlot in a HLD file
   */
  inline unsigned int getIndex() const {
    return fIndex;
  }

  inline void setIndex(unsigned int index) {
    fIndex = index;
  }

  ClassDef(JPetTimeWindow, 2);

private:
  std::vector<JPetSigCh> fSigChannels;
  unsigned int fIndex = 0; ///< sequential number of this TSlot in the HLD file
};

#endif
