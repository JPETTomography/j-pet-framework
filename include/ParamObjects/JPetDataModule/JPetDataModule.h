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
 *  @file JPetDataModule.h
 */

#ifndef JPET_DATA_MODULE_H
#define JPET_DATA_MODULE_H

#include "JPetDataSource/JPetDataSource.h"
#include <TNamed.h>
#include <TRef.h>

/**
 * @brief Representation of a data module, as encoded in xml files used with Unpacker2
 */
class JPetDataModule : public TNamed
{
public:
  JPetDataModule();
  explicit JPetDataModule(bool isNull);
  JPetDataModule(int id, std::string type, unsigned long trb, int number, int offset);
  bool operator==(const JPetDataModule& dataModule) const;
  bool operator!=(const JPetDataModule& dataModule) const;
  void setDataSource(JPetDataSource& dataSource);
  int getID() const;
  std::string getType() const;
  unsigned long getTBRNetAddress() const;
  int getChannelsNumber() const;
  int getChannelsOffset() const;
  bool isNullObject() const;
  JPetDataSource& getDataSource() const;
  static JPetDataModule& getDummyResult();
  void clearTRefDataSource();

  int fID = -1;
  std::string fType = "";
  unsigned long fTRBNetAddress = 0;
  int fChannelsNumber = -1;
  int fChannelsOffset = -1;
  bool fIsNullObject = true;
  TRef fTRefDataSource = nullptr;

  friend class JPetParamManager;

  ClassDef(JPetDataModule, 1);
};

#endif /* JPET_DATA_MODULE_H */
