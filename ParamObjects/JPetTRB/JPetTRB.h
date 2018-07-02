/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 */
class JPetTRB: public TNamed
{
public:
  JPetTRB();
  JPetTRB(int id, int type, int channel);
  static  JPetTRB& getDummyResult();
  explicit JPetTRB(bool isNull);
  explicit JPetTRB(int id);
  ~JPetTRB();
  bool operator==(const JPetTRB& trb) const;
  bool operator!=(const JPetTRB& trb) const;
  int getID() const;
  int getType() const;
  int getChannel() const;
  void setType(int type);
  void setChannel(int ch);
  bool isNullObject() const;

protected:
#ifndef __CINT__
  int fID = 0;
  int fType = 0;
  int fChannel = 0;
  bool fIsNullObject = false;
#else
  int fID;
  int fType;
  int fChannel;
  bool fIsNullObject;
#endif

  friend class JPetParamManager;
  ClassDef(JPetTRB, 3);
};

#endif
