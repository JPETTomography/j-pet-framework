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
 *  @file JPetFilterRamLak.h
 */

#ifndef _JPetFilterRamLak_H_
#define _JPetFilterRamLak_H_
#include "JPetFilterInterface.h"

/*! \brief Filter F(x) = |x| if x < maxThreshold otherwise 0.;
 * default maxThreshold = 0.9
*/
class JPetFilterRamLak : public JPetFilterInterface
{
public:
  JPetFilterRamLak() {}
  JPetFilterRamLak(double maxThreshold) { threshold = maxThreshold; }
  virtual double operator()(double radius) override
  {
    return radius < threshold ? radius : 0.;
  }

private:
  double threshold = 0.9;
};

#endif /*  !_JPetFilterRamLak_H_ */
