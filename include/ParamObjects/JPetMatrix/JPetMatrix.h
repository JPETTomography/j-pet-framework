/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetMatrix.h
 */

#ifndef JPET_MATRIX
#define JPET_MATRIX

#include "JPetScin/JPetScin.h"
#include <TNamed.h>
#include <TRef.h>

class JPetScin;

/**
 * @brief Representation of a matrix of photomupltipliers.
 *
 * Parametric class representing database information of a matrix of photomultipliers,
 * it can include several SiPMs or one PMT, every photomultiplier in the array is
 * indentified by position index. Such matrices are attached to scintillating strips
 * to one of the edges, as indicated by SideA or SideB.
 */
class JPetMatrix : public TNamed
{
public:
  enum Side
  {
    SideA,
    SideB
  };

  JPetMatrix();
  JPetMatrix(int id, Side side);
  JPetMatrix(const JPetMatrix& mtx);
  explicit JPetMatrix(bool isNull);
  virtual ~JPetMatrix();
  void setID(int id);
  void setSide(Side side);
  void setScin(JPetScin& scin);
  int getID() const;
  Side getSide() const;
  JPetScin& getScin() const;
  bool operator==(const JPetMatrix& scin) const;
  bool operator!=(const JPetMatrix& scin) const;
  bool isNullObject() const;
  static JPetMatrix& getDummyResult();

protected:
  int fID = -1;
  Side fSide = SideA;
  bool fIsNullObject = false;
  TRef fTRefScin = nullptr;
  void clearTRefScin();

  friend class JPetParamManager;

  ClassDef(JPetMatrix, 1);
};

#endif /* !JPET_MATRIX */
