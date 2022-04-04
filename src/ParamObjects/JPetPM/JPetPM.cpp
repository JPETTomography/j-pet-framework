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
 *  @file JPetPM.cpp
 */

#include "JPetPM/JPetPM.h"
#include "JPetLoggerInclude.h"

ClassImp(JPetPM);

JPetPM::JPetPM() { SetName("JPetPM"); }

JPetPM::JPetPM(int id, std::string desc, int matrixPosition) : fID(id), fDesc(desc), fMatrixPosition(matrixPosition) { SetName("JPetPM"); }

JPetPM::JPetPM(const JPetPM& pm) : fID(pm.getID()), fDesc(pm.getDesc()), fMatrixPosition(pm.getMatrixPosition()) { SetName("JPetPM"); }

JPetPM::JPetPM(bool isNull) : fIsNullObject(isNull) { SetName("JPetPM"); }

JPetPM::~JPetPM() {}

void JPetPM::setID(int id) { fID = id; }

void JPetPM::setDesc(std::string desc) { fDesc = desc; }

void JPetPM::setMatrixPosition(int position) { fMatrixPosition = position; }

void JPetPM::setMatrix(JPetMatrix& matrix) { fTRefMatrix = &matrix; }

int JPetPM::getID() const { return fID; }

std::string JPetPM::getDesc() const { return fDesc; }

int JPetPM::getMatrixPosition() const { return fMatrixPosition; }

JPetMatrix& JPetPM::getMatrix() const
{
  if (fTRefMatrix.GetObject())
  {
    return static_cast<JPetMatrix&>(*(fTRefMatrix.GetObject()));
  }
  else
  {
    ERROR("No JPetMatrix set, Null object will be returned");
    return JPetMatrix::getDummyResult();
  }
}

bool JPetPM::operator==(const JPetPM& pm) const
{
  return this->getID() == pm.getID() && this->getMatrixPosition() == pm.getMatrixPosition() && this->getMatrix() == pm.getMatrix();
}

bool JPetPM::operator!=(const JPetPM& pm) const { return !(*this == pm); }

bool JPetPM::isNullObject() const { return fIsNullObject; }

JPetPM& JPetPM::getDummyResult()
{
  static JPetPM dummyResult(true);
  return dummyResult;
}

void JPetPM::clearTRefMatrix() { fTRefMatrix = nullptr; }
