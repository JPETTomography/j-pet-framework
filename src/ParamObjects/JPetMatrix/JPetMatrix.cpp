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
 *  @file JPetMatrix.cpp
 */

#include "JPetMatrix/JPetMatrix.h"
#include "JPetLoggerInclude.h"

ClassImp(JPetMatrix);

JPetMatrix::JPetMatrix() { SetName("JPetMatrix"); }

JPetMatrix::JPetMatrix(int id, Side side) : fID(id), fSide(side) { SetName("JPetMatrix"); }

JPetMatrix::JPetMatrix(const JPetMatrix& mtx) : fID(mtx.getID()), fSide(mtx.getSide()) { SetName("JPetMatrix"); }

JPetMatrix::JPetMatrix(bool isNull) : fIsNullObject(isNull) { SetName("JPetMatrix"); }

JPetMatrix::~JPetMatrix() {}

void JPetMatrix::setID(int id) { fID = id; }

void JPetMatrix::setSide(Side side) { fSide = side; }

void JPetMatrix::setScin(JPetScin& scin) { fTRefScin = &scin; }

int JPetMatrix::getID() const { return fID; }

JPetMatrix::Side JPetMatrix::getSide() const { return fSide; }

JPetScin& JPetMatrix::getScin() const
{
  if (fTRefScin.GetObject())
  {
    return static_cast<JPetScin&>(*(fTRefScin.GetObject()));
  }
  else
  {
    ERROR("No JPetScin set, Null object will be returned");
    return JPetScin::getDummyResult();
  }
}

bool JPetMatrix::operator==(const JPetMatrix& mtx) const
{
  return this->getID() == mtx.getID() && this->getSide() == mtx.getSide() && this->getScin() == mtx.getScin();
}

bool JPetMatrix::operator!=(const JPetMatrix& mtx) const { return !(*this == mtx); }

bool JPetMatrix::isNullObject() const { return fIsNullObject; }

JPetMatrix& JPetMatrix::getDummyResult()
{
  static JPetMatrix dummyResult(true);
  return dummyResult;
}

void JPetMatrix::clearTRefScin() { fTRefScin = nullptr; }
