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
 *  @file JPetMatrixSignal.cpp
 */

#include "Signals/JPetMatrixSignal/JPetMatrixSignal.h"
#include "JPetLoggerInclude.h"

using namespace std;

ClassImp(JPetMatrixSignal);

JPetMatrixSignal::JPetMatrixSignal() {}

JPetMatrixSignal::~JPetMatrixSignal() {}

bool JPetMatrixSignal::addPMSignal(const JPetPMSignal& pmSignal)
{
  // Setting JPetMatrix object, if not yet set
  if (this->getMatrix().isNullObject())
  {
    this->setMatrix(pmSignal.getPM().getMatrix());
  }

  // Checking it new PM signal is from PM in the same Matrix as others
  if (!fPMSignalsMap.empty())
  {
    for (auto pmS : fPMSignalsMap)
    {
      if (pmSignal.getPM().getMatrix() != pmS.second.getPM().getMatrix())
      {
        ERROR("Cannot add PM sigals from PMs in different Matrices");
        return false;
      }
    }
  }

  int mtxPos = pmSignal.getPM().getMatrixPosition();
  auto search = fPMSignalsMap.find(mtxPos);
  if (search == fPMSignalsMap.end())
  {
    fPMSignalsMap[mtxPos] = pmSignal;
    return true;
  }
  else
  {
    ERROR("Cannot add PM signal with same matrix position as an existing one.");
    return false;
  }
}

map<int, JPetPMSignal> JPetMatrixSignal::getPMSignals() const { return fPMSignalsMap; }

void JPetMatrixSignal::setMatrix(const JPetMatrix& mtx) { fMatrix = const_cast<JPetMatrix*>(&mtx); }

const JPetMatrix& JPetMatrixSignal::getMatrix() const
{
  if (fMatrix.GetObject())
  {
    return static_cast<JPetMatrix&>(*(fMatrix.GetObject()));
  }
  else
  {
    ERROR("No JPetMatrix set, null object will be returned");
    return JPetMatrix::getDummyResult();
  }
}

float JPetMatrixSignal::getToT() const
{
  float tot = 0.0;
  for (auto pS : fPMSignalsMap)
  {
    tot += pS.second.getToT();
  }
  if (fPMSignalsMap.size() == 0)
  {
    return 0.0;
  }
  else
  {
    return tot / ((float)fPMSignalsMap.size());
  }
}

void JPetMatrixSignal::Clear(Option_t*)
{
  JPetRecoSignal::Clear("");
  fPMSignalsMap.clear();
}
