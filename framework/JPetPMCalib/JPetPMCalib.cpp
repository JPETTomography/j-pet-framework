#include "JPetPMCalib.h"


JPetPMCalib::JPetPMCalib() :
			    id(0),
			    name(""),
			    opthv(0.f),
			    c2e_1(0.f),
			    c2e_2(0.f),
			    gainalpha(0.f),
			    gainbeta(0.f)
{
  SetName("JPetPMCalib");
}

JPetPMCalib::JPetPMCalib(int id,
			  std::string name,
			  float opthv,
			  float c2e_1,
			  float c2e_2,
			  float gainalpha,
			  float gainbeta) :
					  id(id),
					  name(name),
					  opthv(opthv),
					  c2e_1(c2e_1),
					  c2e_2(c2e_2),
					  gainalpha(gainalpha),
					  gainbeta(gainbeta)
{
  SetName("JPetPMCalib");
}

JPetPMCalib::~JPetPMCalib()
{
}

ClassImp(JPetPMCalib);
