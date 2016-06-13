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
 *  @file JPetPMCalibFactory.h
 */

#ifndef JPET_PM_CALIB_FACTORY_H
#define JPET_PM_CALIB_FACTORY_H

#include "../JPetParamGetter/JPetParamGetter.h"
#include "JPetPMCalib.h"

#include <map>

/**
 * @brief A factory of JPetPMCalib objects.
 *
 * This class is able to create those objects using data from the database.
 */
class JPetPMCalibFactory
{
  public:
    JPetPMCalibFactory(JPetParamGetter & paramGetter, int runId) :
      paramGetter(paramGetter),
      runId(runId),
      fInitialized(false) {}

    std::map<int, JPetPMCalib *> & getPMCalibs();
  private:
    JPetParamGetter & paramGetter;
    const int runId;

    bool fInitialized;
    std::map<int, JPetPMCalib *> fPMCalibs;

    void initialize();
    JPetPMCalib * build(ParamObjectDescription data);
};

#endif // JPET_PM_CALIB_FACTORY_H
