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
 *  @file JPetRecoHit.h
 */

#ifndef JPETRECOHIT_H
#define JPETRECOHIT_H

#include "JPetBaseHit/JPetBaseHit.h"

class JPetBaseHit;

/**
 * @brief Representation of a hit expanded from basic hit class with reconstruciton
 * flags.
 *
 * Reconstruction flag is indicative of the result of either low-level data selection in case
 * of experimental mesurement (good/corrupted) or smearing/efficiency procedures on raw
 * Monte Carlo hit (MC).
 */
class JPetRecoHit : public JPetBaseHit
{
public:
  enum RecoFlag
  {
    Good,
    Corrupted,
    MC,
    Unknown
  };
  JPetRecoHit();
  explicit JPetRecoHit(JPetRecoHit::RecoFlag flag);
  virtual ~JPetRecoHit();
  JPetRecoHit::RecoFlag getRecoFlag() const;
  void setRecoFlag(JPetRecoHit::RecoFlag flag);
  void Clear(Option_t*) override;

private:
  RecoFlag fFlag = JPetRecoHit::Unknown;

  ClassDef(JPetRecoHit, 1);
};

#endif /* !JPETRECOHIT_H */
