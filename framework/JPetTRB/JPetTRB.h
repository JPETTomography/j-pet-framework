// JPetTRB.h - TRB
#ifndef _JPETTRB_H_
#define _JPETTRB_H_

#include "TNamed.h"
#include <TRef.h>
#include "../JPetUser/JPetUser.h"
#include "../JPetTOMB/JPetTOMB.h"


class JPetTRB: public TNamed
{
protected:
  struct JPetTRBChannel
  {
    JPetTRBChannel(int p_id, 
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
  
  struct JPetTRBInput : public JPetTRBChannel
  {
    JPetTRBInput(int p_id, 
		 bool p_isActive, 
		 std::string p_status, 
		 int p_portNumber, 
		 std::string p_description, 
		 int p_TRBId);
    
    int fTRBId;
  };

  struct JPetTRBOutput : public JPetTRBChannel
  {
    JPetTRBOutput(int p_id, 
		  bool p_isActive, 
		  std::string p_status, 
		  int p_portNumber, 
		  std::string p_description, 
		  int p_TRBId,
		  int p_TRBInputId);
    
    int fTRBId;
    int fTRBInputId;
  };
  
public:
  JPetTRB(void);
  JPetTRB(int p_id, bool p_isActive, std::string p_status, int p_maxch, std::string p_name, std::string p_description, int p_version, const JPetUser &p_user);
  ~JPetTRB(void);
  
  int getId() const { return fId; }
  bool getIsActive() const { return fIsActive; }
  std::string getStatus() const { return fStatus; }
  int getMaxch() const { return fMaxch; }
  std::string getName() const { return fName; }
  std::string getDescription() const { return fDescription; }
  int getVersion() const { return fVersion; }
  JPetUser getUser() const { return fUser; }
  
  TRef getTRefTOMB() const { return fTRefTOMB; }
  void setTRefTOMB(JPetTOMB &p_TOMB)
  {
    fTRefTOMB = &p_TOMB;
  }
  
  friend class JPetParamManager;
  
protected:
  int fId;
  bool fIsActive;
  std::string fStatus;
  int fMaxch;
  std::string fName;
  std::string fDescription;
  int fVersion;
  JPetUser fUser;
  
  TRef fTRefTOMB;
  
  void clearTRefTOMB()
  {
    fTRefTOMB = NULL;
  }
  
  ClassDef(JPetTRB, 1);
};

#endif	// _JPETTRB_H_
