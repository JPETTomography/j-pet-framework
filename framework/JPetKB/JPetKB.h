// JPet Konrad board - JPetKB.h
#ifndef JPET_KB_H
#define JPET_KB_H

#include "TNamed.h"
#include <TRef.h>
#include <vector>
#include "../JPetUser/JPetUser.h"
#include "../JPetTRB/JPetTRB.h"
//#include "../JPetParamManager/JPetParamManager.h"


class JPetKB: public TNamed
{
protected:
  struct JPetKBChannel
  {
    JPetKBChannel(int p_id, 
		  bool p_isActive, 
		  std::string p_status, 
		  int p_portNumber, 
		  std::string p_description);
    
    int fId;
    bool fIsActive;
    std::string fStatus;
    int fPortNumber;
    std::string fDescription;
  };
  
  struct JPetKBInput : public JPetKBChannel
  {
    JPetKBInput(int p_id, 
		bool p_isActive, 
		std::string p_status, 
		int p_portNumber, 
		std::string p_description, 
		int p_KBId);
    
    int fKBId;
  };

  struct JPetKBOutput : public JPetKBChannel
  {
    JPetKBOutput(int p_id, 
		 bool p_isActive, 
		 std::string p_status, 
		 int p_portNumber, 
		 std::string p_description, 
		 bool p_passedInformationIsTime, 
		 std::string p_passedInformation, 
		 int p_KBId, 
		 int p_inputId, 
		 int p_KBInputId);
    
    bool fPassedInformationIsTime;
    std::string fPassedInformation;
    int fKBId;
    int fInputId;
    int fKBInputId;
  };
  
public:
  JPetKB(void);
  JPetKB(int p_id, 
	 bool p_isActive, 
	 std::string p_status, 
	 std::string p_description, 
	 int p_version, 
	 const JPetUser &p_user);
  ~JPetKB(void);
  
  int getId() const { return fId; }
  bool getIsActive() const { return fIsActive; }
  std::string getStatus() const { return fStatus; }
  std::string getDescription() const { return fDescription; }
  int getVersion() const { return fVersion; }
  JPetUser getUser() const { return fUser; }
  
  std::vector<TRef> getTRefTRBs() const { return fTRefTRBs; }
  void setTRefTRBs(std::vector<TRef> &p_TRefTRBs)
  {
    fTRefTRBs = p_TRefTRBs;
  }
  void addTRefTRB(JPetTRB &p_TRB)
  {
    fTRefTRBs.push_back(&p_TRB);
  }
  
  friend class JPetParamManager;
  
protected:
  int fId;
  bool fIsActive;
  std::string fStatus;
  std::string fDescription;
  int fVersion;
  JPetUser fUser;

  std::vector<TRef> fTRefTRBs;
  
  void clearTRefTRBs()
  {
    fTRefTRBs.clear();
  }
  
  ClassDef(JPetKB, 1);
};

#endif // JPET_KB_H
