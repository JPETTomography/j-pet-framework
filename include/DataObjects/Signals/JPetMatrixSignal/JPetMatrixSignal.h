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
 *  @file JPetMatrixSignal.h
 */

#ifndef JPETMATRIXSIGNAL_H
#define JPETMATRIXSIGNAL_H

#include "JPetMatrix/JPetMatrix.h"
#include "Signals/JPetPMSignal/JPetPMSignal.h"
#include "Signals/JPetRecoSignal/JPetRecoSignal.h"
#include <TRef.h>
#include <map>

/**
 * @brief Data class representing a signal reconstructed
 * in a matrix of SiPMs on a one side of a scintillator in a modular layer
 */
class JPetMatrixSignal : public JPetRecoSignal
{
public:
  JPetMatrixSignal();
  virtual ~JPetMatrixSignal();
  bool addPMSignal(const JPetPMSignal& pmSignal);
  std::map<int, JPetPMSignal> getPMSignals() const;
  double getToT() const;
  void setMatrix(const JPetMatrix& mtx);
  const JPetMatrix& getMatrix() const;
  void Clear(Option_t*) override;

private:
  std::map<int, JPetPMSignal> fPMSignalsMap;
  TRef fMatrix = nullptr;

  ClassDef(JPetMatrixSignal, 1);
};
#endif /* !JPETMATRIXSIGNAL_H */