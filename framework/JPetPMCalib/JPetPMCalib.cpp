#include "JPetPMCalib.h"


JPetPMCalib::JPetPMCalibAssignment::JPetPMCalibAssignment(int id, int photomultiplier_id) : id(id), 
											       photomultiplier_id(photomultiplier_id)
{
}

JPetPMCalib::JPetPMCalib():
                          id(0),
                          name(""),
                          opthv(0.0),
                          c2e_1(0.0),
                          c2e_2(0.0),
                          gainalpha(0.0),
                          gainbeta(0.0),
                          PMCalibAssignment(0,0)
{
  SetName("JPetPMCalib");
}

JPetPMCalib::JPetPMCalib(int id,
			  std::string name,
			  float opthv,
			  float c2e_1,
			  float c2e_2,
			  float gainalpha,
			  float gainbeta,
			  int PMCalibAssignmentId,
			  int PMCalibAssignmentPhotomultiplierId) :
					  id(id),
					  name(name),
					  opthv(opthv),
					  c2e_1(c2e_1),
					  c2e_2(c2e_2),
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
