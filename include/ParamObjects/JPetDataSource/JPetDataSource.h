/**
 *  @copyright Copyright 2020 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetDataSource.h
 */

#ifndef JPET_DATA_SOURCE_H
#define JPET_DATA_SOURCE_H

#include <TNamed.h>

/**
 * @brief Representation of a data source, as encoded in xml files used with Unpacker2
 *
 */
class JPetDataSource: public TNamed
{
public:
  JPetDataSource();
  explicit JPetDataSource(bool isNull);
  JPetDataSource(int id, std::string type, std::string trb, std::string hub);
  bool operator==(const JPetDataSource& dataSource);
  bool operator!=(const JPetDataSource& dataSource);
  int getID() const;
  std::string getType() const;
  std::string getTBRNetAddress() const;
  std::string getHubAddress() const;
  bool isNullObject() const;
  static JPetDataSource& getDummyResult();

  #ifndef __CINT__
    int fID = -1;
    std::string fType = "";
    std::string fTRBNetAddress = "";
    std::string fHubAddress = "";
    bool fIsNullObject = true;
  #else
    int fID;
    std::string fType;
    std::string fTRBNetAddress;
    std::string fHubAddress;
    bool fIsNullObject;
  #endif

  friend class JPetParamManager;

  ClassDef(JPetDataSource, 1);
};

#endif /* JPET_DATA_SOURCE_H */
