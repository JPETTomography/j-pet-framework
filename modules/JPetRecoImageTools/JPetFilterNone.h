/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetFilterNone.h
 */

#ifndef _JPetFilterNone_H_
#define _JPetFilterNone_H_
#include "./JPetFilterInterface.h"

/*! \brief Dummy filter not filtering data.
 *
*/
class JPetFilterNone : public JPetFilterInterface
{
public:
  JPetFilterNone() {}
  virtual double operator()(double) override { return 1.; }

private:
  JPetFilterNone(const JPetFilterNone &) = delete;
  JPetFilterNone &operator=(const JPetFilterNone &) = delete;
};

#endif /*  !_JPetFilterNone_H_ */
