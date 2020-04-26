/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetChannel.h
 */

#ifndef JPETCHANNEL_H
#define JPETCHANNEL_H

#include "JPetPM/JPetPM.h"
#include <TNamed.h>
#include <TRef.h>

/**
 * @brief Representation of a acquisition channel.
 */
class JPetChannel : public TNamed
{
public:
  JPetChannel();
  JPetChannel(int id, int thrNum, float thrVal);
  JPetChannel(const JPetChannel &channel);
  explicit JPetChannel(bool isNull);
  virtual ~JPetChannel();
  void setID(int id);
  void setThresholdNumber(int thrNum);
  void setThresholdValue(float trhVal);
  void setPM(JPetPM& pm);
  const int getID() const;
  int getThresholdNumber() const;
  float getThresholdValue() const;
  const JPetPM& getPM() const;
  bool operator==(const JPetChannel& channel);
  bool operator!=(const JPetChannel& channel);
  bool isNullObject() const;
  static JPetChannel& getDummyResult();

protected:
#ifndef __CINT__
  int fID = -1;
  int fThresholdNumber = 0;
  float fThresholdValue = 0.0;
  bool fIsNullObject = false;
#else
  int fID;
  int fThresholdNumber;
  float fThresholdValue;
  bool fIsNullObject;
#endif
  TRef fTRefPM;

  friend class JPetParamManager;

  ClassDef(JPetChannel, 1);
};

#endif /* JPETCHANNEL_H */