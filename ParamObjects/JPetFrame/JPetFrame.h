/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetFrame.h
 */

#ifndef JPET_FRAME_H
#define JPET_FRAME_H

#include "TNamed.h"

/**
 * @brief Representation of a frame in the J-PET setup
 *
 * Parametric class representing database information on a whole mechanical
 * structure frame of the J-PET setup. The frame consists of one or more layers
 * represented by JPetLayer objects.
 */
class JPetFrame: public TNamed
{
public:
  JPetFrame();
  JPetFrame(int id, bool isActive, std::string status, std::string description,
    int version, int creator_id);
  explicit JPetFrame(bool isNull);
  bool operator==(const JPetFrame& frame);
  bool operator!=(const JPetFrame& frame);
  int getID() const;
  bool getIsActive() const;
  std::string getStatus() const;
  std::string getDescription() const;
  int getVersion() const;
  int getCreator() const;
  bool isNullObject() const;
  static JPetFrame& getDummyResult();

protected:
#ifndef __CINT__
  const int fId = -1;
  bool fIsActive = false;
  std::string fStatus = "";
  std::string fDescription = "";
  const int fVersion = -1;
  const int fCreator_id = -1;
  bool fIsNullObject = false;
#else
  const int fId;
  bool fIsActive;
  std::string fStatus;
  std::string fDescription;
  const int fVersion;
  const int fCreator_id;
  bool fIsNullObject;
#endif

  ClassDef(JPetFrame, 2);
};
#endif /* !JPET_FRAME_H */
