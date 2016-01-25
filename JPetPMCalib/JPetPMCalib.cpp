#include "JPetPMCalib.h"


JPetPMCalib::JPetPMCalibAssignment::JPetPMCalibAssignment(int id, int photomultiplier_id) : id(id), 
											       photomultiplier_id(photomultiplier_id)
{
}

JPetPMCalib::JPetPMCalib():
                          id(0),
                          name(""),
                          opthv(0.0),
                          ECalConst1(0.0),
                          ECalConst2(0.0),
                          gainalpha(0.0),
                          gainbeta(0.0),
                          PMCalibAssignment(0,0)
{
  SetName("JPetPMCalib");
}

JPetPMCalib::JPetPMCalib(int id,
			  std::string name,
			  float opthv,
			  float ECalConst1,
			  float ECalConst2,
			  float gainalpha,
			  float gainbeta,
			  int PMCalibAssignmentId,
			  int PMCalibAssignmentPhotomultiplierId) :
					  id(id),
					  name(name),
					  opthv(opthv),
					  ECalConst1(ECalConst1),
					  ECalConst2(ECalConst2),
					  gainalpha(gainalpha),
					  gainbeta(gainbeta),
					  PMCalibAssignment(PMCalibAssignmentId, 
							    PMCalibAssignmentPhotomultiplierId)
{
  SetName("JPetPMCalib");
}

JPetPMCalib::~JPetPMCalib()
{
}

ClassImp(JPetPMCalib);
