// JPet TOMB - JPetTOMB.cpp
#include "JPetTOMB.h"


ClassImp(JPetTOMB);

JPetTOMB::JPetTOMB() :
		      fId(0),
		      fDescription(std::string("")),
		      fSetupId(0)
{}

JPetTOMB::JPetTOMB(int p_id,
		   std::string p_description,
		   int p_setupId) :
							  fId(p_id),
							  fDescription(p_description),
							  fSetupId(p_setupId)
{}
  
JPetTOMB::~JPetTOMB()
{}
