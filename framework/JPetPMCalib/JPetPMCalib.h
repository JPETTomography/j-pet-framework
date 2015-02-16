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
  struct JPetPMCalibAssignment
  {
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
  
  virtual int GetId(void) const { return id; };
  virtual std::string GetNamePM(void) const { return name; };
  virtual float GetOpthv(void) const { return opthv; };
  virtual float GetECalConst1(void) const { return ECalConst1; };
  virtual float GetECalConst2(void) const { return ECalConst2; };
  virtual float GetGainalpha(void) const {return gainalpha; };
  virtual float GetGainbeta(void) const { return gainbeta; };
  virtual JPetPMCalibAssignment GetPMCalibAssignment(void) { return PMCalibAssignment; }

  inline bool operator==(const JPetPMCalib& calib) { return GetId() == calib.GetId(); }
  inline bool operator!=(const JPetPMCalib& calib) { return GetId() != calib.GetId(); }
  
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
