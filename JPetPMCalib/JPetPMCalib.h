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
 *  @file JPetPMCalib.h
 */

#ifndef _JPET_PM_CALIB_
#define _JPET_PM_CALIB_

#include "TNamed.h"

/**
 * @brief Parametric class representing database information on parameters of a photomultiplier calibration.
 *
 */
class JPetPMCalib: public TNamed
{
protected:
  struct JPetPMCalibAssignment {
    JPetPMCalibAssignment(int id, int photomultiplier_id);

    int id;
    int photomultiplier_id;
  };

public:
  JPetPMCalib();
  JPetPMCalib(int id,
              std::string name,
              float opthv,
              float ECalConst1,
              float ECalConst2,
              float gainalpha,
              float gainbeta,
              int PMCalibAssignmentId,
              int PMCalibAssignmentPhotomultiplierId);

  virtual ~JPetPMCalib(void);

  virtual int getID(void) const {
    return id;
  };
  virtual std::string GetNamePM(void) const {
    return name;
  };
  virtual float GetOpthv(void) const {
    return opthv;
  };
  virtual float GetECalConst1(void) const {
    return ECalConst1;
  };
  virtual float GetECalConst2(void) const {
    return ECalConst2;
  };
  virtual float GetGainalpha(void) const {
    return gainalpha;
  };
  virtual float GetGainbeta(void) const {
    return gainbeta;
  };
  virtual JPetPMCalibAssignment GetPMCalibAssignment(void) const {
    return PMCalibAssignment;
  }

  inline bool operator==(const JPetPMCalib& calib) {
    return getID() == calib.getID();
  }
  inline bool operator!=(const JPetPMCalib& calib) {
    return getID() != calib.getID();
  }

protected:
  const int id;
  std::string name;
  float opthv;
  float ECalConst1;
  float ECalConst2;
  float gainalpha;
  float gainbeta;

  JPetPMCalibAssignment PMCalibAssignment;

  friend class JPetParamManager;

private:
  ClassDef(JPetPMCalib, 1);
};

#endif // _JPET_PM_CALIB_
