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
 *  @file JPetTRB.h
 */

#ifndef _JPETTRB_H_
#define _JPETTRB_H_

#include "TNamed.h"

/**
 * @brief Parametric class representing database information on parameters of a TRB board.
 *
 */
class JPetTRB: public TNamed
{
 public:
  JPetTRB();
  JPetTRB(int id);
  JPetTRB(int id, int type, int channel);
  JPetTRB(bool isNull);
  ~JPetTRB();

  inline int getID() const { return fID; }
  inline int getType() const { return fType; }
  inline int getChannel() const { return fChannel; }
  inline void setType(int type) { fType = type; }
  inline void setChannel(int ch) { fChannel = ch; }

  inline bool operator==(const JPetTRB& trb) const { return getID() == trb.getID(); }
  inline bool operator!=(const JPetTRB& trb) const { return getID() != trb.getID(); }
  
  inline bool isNullObject() const { return fIsNullObject; }

  static inline JPetTRB& getDummyResult() {
    static JPetTRB DummyResult(true);
    return DummyResult;
  }

 private:
  int fID = 0;
  int fType = 0;
  int fChannel = 0;
  bool fIsNullObject = false;
  /// @todo do implementacji
  //JPetFEB* KBId;
  //KBType;
  //KBChan;
  //
  ClassDef(JPetTRB, 3);
  
protected:
  
  friend class JPetParamManager;
};

#endif
