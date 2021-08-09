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
 *  @file JPetBaseSignal.h
 */

#ifndef JPETBASESIGNAL_H
#define JPETBASESIGNAL_H

#include <TObject.h>

/**
 * @brief Base class for all signal data classes
 *
 * Class provides basic construction and methods for more specific Signal classes.
 */
class JPetBaseSignal : public TObject
{
public:
  JPetBaseSignal();
  explicit JPetBaseSignal(bool isNull);
  explicit JPetBaseSignal(double time);
  virtual ~JPetBaseSignal();
  void setTime(double time);
  const double getTime() const;
  bool isNullObject() const;
  static JPetBaseSignal& getDummyResult();
  void Clear(Option_t*) override;

protected:
  bool fIsNullObject = false;
  double fTime = 0.0;

  ClassDef(JPetBaseSignal, 6);
};
#endif /* !JPETBASESIGNAL_H */
