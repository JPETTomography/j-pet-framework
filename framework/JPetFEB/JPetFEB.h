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
  int m_version;
  //JPetUser &m_JPetUser;		//creatorId
  int m_userId;		// creatorId 
  /// @todo userId is inaccesible!!!

public:
  JPetFEB();
  JPetFEB(int p_id, bool p_isActive, std::string p_status, std::string p_description, int p_version, int p_userId);
  virtual ~JPetFEB(void);
  
  virtual int id(void) const;
  virtual bool isActive(void) const;
  virtual std::string status(void) const;
  virtual std::string description(void) const;
  virtual int version(void) const;
  
  JPetTRB* getTRefTRB() { return (JPetTRB*)fTRefTRBs.GetObject(); }
  
  void setTRefTRB(JPetTRB &p_TRB)
  {
    fTRefTRBs = &p_TRB;
  }
  
  /*std::vector<TRef> getTRefTRBs() const { return fTRefTRBs; }

  JPetTRB* getTRefTRB(int p_index)
  {
    if(p_index < fTRefTRBs.size())
    {
      return (JPetTRB*)fTRefTRBs[p_index].GetObject();
    }
    return NULL;
  }
  
  void setTRefTRBs(std::vector<TRef> &p_TRefTRBs)
  {
    fTRefTRBs = p_TRefTRBs;
  }
  
  void addTRefKB(JPetTRB &p_TRB)
  {
    fTRefTRBs.push_back(&p_TRB);
  }*/

protected:
  TRef fTRefTRBs;
  
  void clearTRefTRBs()
  {
    fTRefTRBs = NULL;
  }
  
  /*std::vector<TRef> fTRefTRBs;
  
  void clearTRefTRBs()
  {
    fTRefTRBs.clear();
  }*/
  
private:
  ClassDef(JPetFEB, 1);
  
  friend class JPetParamManager;
};

#endif // JPET_FEB_H
