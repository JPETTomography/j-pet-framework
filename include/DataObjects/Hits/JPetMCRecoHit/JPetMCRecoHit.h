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
 *  @file JPetMCRecoHit.h
 */

#ifndef JPETMCRECOHIT_H
#define JPETMCRECOHIT_H

#include "Hits/JPetRecoHit/JPetRecoHit.h"

class JPetRecoHit;

/**
 * @brief JPetMCRecoHit is a hit class representing reconstructed raw Monte Carlo
 * hit with index, that links original JPetRawMCHit and JPetMCRecoHit
 */
class JPetMCRecoHit : public JPetRecoHit
{
public:
  JPetMCRecoHit();
  explicit JPetMCRecoHit(int mcIndex);
  virtual ~JPetMCRecoHit();
  virtual JPetMCRecoHit* clone() const override;
  unsigned int getMCindex() const;
  void setMCindex(unsigned int i);
  void Clear(Option_t*) override;
  static const unsigned int kMCindexError = 888888;

private:
  unsigned int fMCindex = kMCindexError;

  ClassDef(JPetMCRecoHit, 1);
};

#endif /* !JPETMCRECOHIT_H */
