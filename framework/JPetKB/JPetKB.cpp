// JPet Konrad Board - JPetKB.cpp
#include "JPetKB.h"


ClassImp(JPetKB);


JPetKB::JPetKBChannel::JPetKBChannel(int p_id, 
				      bool p_isActive, 
				      std::string p_status, 
				      int p_portNumber, 
				      std::string p_description) :
								  fId(p_id),
								  fIsActive(p_isActive),
								  fStatus(p_status),
								  fPortNumber(p_portNumber),
								  fDescription(p_description)
{}

JPetKB::JPetKBInput::JPetKBInput(int p_id,
				  bool p_isActive, 
				  std::string p_status, 
				  int p_portNumber, 
				  std::string p_description,
				  int p_KBId) :
					      JPetKBChannel(p_id, 
							    p_isActive, 
							    p_status, 
							    p_portNumber, 
							    p_description), 
					      fKBId(p_KBId)
{}

JPetKB::JPetKBOutput::JPetKBOutput(int p_id,
				    bool p_isActive, 
				    std::string p_status, 
				    int p_portNumber, 
				    std::string p_description,
				    bool p_passedInformationIsTime,
				    std::string p_passedInformation, 
				    int p_KBId, 
				    int p_inputId, 
				    int p_KBInputId) : 
						      JPetKBChannel(p_id, 
								    p_isActive, 
								    p_status, 
								    p_portNumber, 
								    p_description),
						      fPassedInformationIsTime(p_passedInformationIsTime),
						      fPassedInformation(p_passedInformation),
						      fKBId(p_KBId),
						      fInputId(p_inputId),
						      fKBInputId(p_KBInputId)
{}

JPetKB::JPetKB() :
		  fId(0),
		  fIsActive(false),
		  fStatus(""),
		  fDescription(""),
		  fVersion(0)
{}

JPetKB::JPetKB(int p_id, 
	       bool p_isActive, 
	       std::string p_status, 
	       std::string p_description, 
	       int p_version,
	       const JPetUser &p_user) :
			      fId(p_id),
			      fIsActive(p_isActive),
			      fStatus(p_status),
			      fDescription(p_description),
			      fVersion(p_version),
			      fUser(p_user)
{}

JPetKB::~JPetKB()
{}
