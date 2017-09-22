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
 *  @file JPetFilterRidgelet.h
 */

#ifndef _JPetFilterRidgelet_H_
#define _JPetFilterRidgelet_H_
#include "./JPetFilterInterface.h"
#include <cmath>

/*! \brief Filter F(x) = sqrt(x)
*/
class JPetFilterRidgelet : public JPetFilterInterface
{
public:
  JPetFilterRidgelet() {}
  virtual double operator()(double radius) override
  {
    return std::sqrt(radius);
  }

private:
  JPetFilterRidgelet(const JPetFilterRidgelet &) = delete;
  JPetFilterRidgelet &operator=(const JPetFilterRidgelet &) = delete;
};

#endif /*  !_JPetFilterRidgelet_H_ */
