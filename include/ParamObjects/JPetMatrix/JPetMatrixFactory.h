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
 *  @file JPetMatrixFactory.h
 */

#ifndef JPET_MATRIX_FACTORY_H
#define JPET_MATRIX_FACTORY_H

// #include "JPetPM/JPetPM.h"
#include "JPetParamGetter/JPetParamGetter.h"
#include "JPetScin/JPetScinFactory.h"
#include <map>

/**
 * @brief A factory of JPetMatrix objects.
 *
 * This class is able to create those objects using data from the database.
 */
class JPetMatrixFactory
{
public:
  JPetMatrixFactory(JPetParamGetter& paramGetter, int runID, JPetScinFactory& scinFactory)
      : fParamGetter(paramGetter), fRunID(runID), fScinFactory(scinFactory), fInitialized(false)
  {
  }
  std::map<int, JPetMartix*>& getMatrices();

private:
  JPetParamGetter& fParamGetter;
  const int fRunID;
  JPetScinFactory& fScinFactory;
  bool fInitialized;
  std::map<int, JPetMartix*> fMatrices;
  void initialize();
  JPetMartix* build(ParamObjectDescription data);
};

#endif /* !JPET_PM_FACTORY_H */
