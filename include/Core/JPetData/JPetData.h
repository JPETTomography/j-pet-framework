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
 *  @file JPetData.h
 */

#ifndef JPETDATA_H
#define JPETDATA_H
#include "./JPetDataInterface/JPetDataInterface.h"
#include <TObject.h>

/**
 * @brief Wrapper class that contains data send to JPetUserTask.
 */
class JPetData: public JPetDataInterface
{
public:
  explicit JPetData(TObject& event);
  TObject& getEvent() const;
protected:
  TObject& fEvent;
};
#endif /* !JPETDATA_H */
