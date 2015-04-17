// JPet Front-end board - JPetFEB.h
#ifndef JPET_FEB_H
#define JPET_FEB_H

#include "TNamed.h"
#include <TRef.h>
#include "../JPetTRB/JPetTRB.h"

/**
 * @brief Parametric class representing database information on parameters of a front-end board (FEB).
 *
 * The board represented by this class can be: KonradBoard(KB), Majewski Board or MP board.
 */
class JPetFEB: public TNamed
{
protected:
  struct JPetFEBChannel
  {
    int m_id;
    bool m_isActive;
    std::string m_status;
    int m_portNumber;
    std::string m_description;
  };
  
  struct JPetFEBInput : public JPetFEBChannel
  {
    JPetFEBInput(int p_FEBId);
    
    int m_FEBId;
  };

  struct JPetFEBOutput : public JPetFEBChannel
  {
    JPetFEBOutput(bool p_passedInformationIsTime, std::string p_passedInformation, int p_FEBId, int p_inputId, int p_FEBInputId);
    
    bool m_passedInformationIsTime;
    std::string m_passedInformation;
    int m_FEBId;
    int m_inputId;
    int m_FEBInputId;
  };
  
  int m_id;
  bool m_isActive;
  std::string m_status;
  std::string m_description;
  const int m_version;
  //JPetUser &m_JPetUser;		//creatorId
  const int m_userId;		// creatorId 
  /// @todo userId is inaccesible!!!
  int m_n_time_outputs_per_input;
  int m_n_notime_outputs_per_input;
  
  
public:
  JPetFEB();
  JPetFEB(int p_id, bool p_isActive, std::string p_status, std::string p_description,
	  int p_version, int p_userId, int p_n_time_outputs_per_input,
	  int p_n_notime_outputs_per_input);
  virtual ~JPetFEB(void);
  
  virtual int getID(void) const;
  virtual void setID(int p_id);
  virtual bool isActive(void) const;
  virtual std::string status(void) const;
  virtual std::string description(void) const;
  virtual int version(void) const;
  virtual int getNtimeOutsPerInput(void) const;
  virtual int getNnotimeOutsPerInput(void) const;
  
  const JPetTRB & getTRB() const 
  { 
    return (JPetTRB&)*fTRefTRBs.GetObject(); 
  }
  
  void setTRB(JPetTRB &p_TRB)
  {
    fTRefTRBs = &p_TRB;
  }

  inline bool operator==(const JPetFEB& feb) { return getID() == feb.getID(); }
  inline bool operator!=(const JPetFEB& feb) { return getID() != feb.getID(); }
  

protected:
  TRef fTRefTRBs;
  
  void clearTRefTRBs()
  {
    fTRefTRBs = NULL;
  }
  
  
private:
  ClassDef(JPetFEB, 1);
  
  friend class JPetParamManager;
};

#endif // JPET_FEB_H
