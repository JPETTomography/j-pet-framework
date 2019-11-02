/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetPM.h
 */

#ifndef JPET_PM
#define JPET_PM

#include "JPetScin/JPetScin.h"
#include <TNamed.h>
#include <TRef.h>

class JPetScin;

/**
 * @brief Representation of a photomultiplier.
 *
 * Parametric class representing database information of a single photomultiplier.
 */
class JPetPM: public TNamed
{
public:
  enum Side {SideA, SideB};

  JPetPM();
  JPetPM(int id, Side side, std::string desc, int matrixPosition);
  JPetPM(const JPetPM &pm);
  explicit JPetPM(bool isNull);
  virtual ~JPetPM();
  void setID(int id);
  void setSide(Side side);
  void setDesc(std::string desc);
  void setMatrixPosition(int position);
  void setScin(JPetScin& scin);
  int getID() const;
  Side getSide() const;
  std::string getDesc() const;
  int getMatrixPosition() const;
  JPetScin& getScin() const;
  bool operator==(const JPetPM& pm) const;
  bool operator!=(const JPetPM& pm) const;
  bool isNullObject() const;
  static JPetPM& getDummyResult();

protected:
  void clearTRefScin();

#ifndef __CINT__
  int fID = -1;
  Side fSide = SideA;
  std::string fDesc = "";
  int fMatrixPosition = -1;
  bool fIsNullObject = false;
#else
  int fID;
  Side fSide;
  std::string fDesc;
  int fMatrixPosition;
  bool fIsNullObject;
#endif
  TRef fTRefScin;

  friend class JPetParamManager;

  ClassDef(JPetPM, 7);
};

#endif /* !JPET_PM */
