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
 *  @file JPetSetup.h
 */

#ifndef JPET_SETUP_H
#define JPET_SETUP_H

#include <TNamed.h>

/**
 * @brief Representation of a frame in the J-PET setup
 *
 * Parametric class representing database information on a whole mechanical
 * structure frame of the J-PET setup. The frame consists of one or more layers
 * represented by JPetLayer objects.
 */
class JPetSetup : public TNamed
{
public:
  JPetSetup();
  JPetSetup(int id, std::string description);
  JPetSetup(const JPetSetup& setup);
  explicit JPetSetup(bool isNull);
  virtual ~JPetSetup();
  void setID(int id);
  void setDescription(std::string desc);
  int getID() const;
  std::string getDescription() const;
  bool operator==(const JPetSetup& setup) const;
  bool operator!=(const JPetSetup& setup) const;
  bool isNullObject() const;
  static JPetSetup& getDummyResult();

protected:
  int fID = -1;
  std::string fDescription = "";
  bool fIsNullObject = false;

  ClassDef(JPetSetup, 1);
};
#endif /* !JPET_SETUP_H */
