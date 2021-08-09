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
 *  @file JPetRecoSignal.h
 */

#ifndef JPETRECOSIGNAL_H
#define JPETRECOSIGNAL_H

#include "Signals/JPetBaseSignal/JPetBaseSignal.h"

/**
 * @brief Data class representing a signal expanded from basic signal class
 * with reconstruciton flag.
 */
class JPetRecoSignal : public JPetBaseSignal
{
public:
  enum RecoFlag
  {
    Good,
    Corrupted,
    Unknown
  };

  JPetRecoSignal();
  explicit JPetRecoSignal(JPetRecoSignal::RecoFlag flag);
  explicit JPetRecoSignal(double time);
  JPetRecoSignal(JPetRecoSignal::RecoFlag flag, double time);
  virtual ~JPetRecoSignal();
  void setRecoFlag(JPetRecoSignal::RecoFlag flag);
  JPetRecoSignal::RecoFlag getRecoFlag() const;
  void Clear(Option_t*) override;

private:
  RecoFlag fFlag = JPetRecoSignal::Unknown;

  ClassDef(JPetRecoSignal, 4);
};

#endif /* !JPETRECOSIGNAL_H */
