// JPet TOMB - JPetTOMB.h
#ifndef JPET_TOMB_H
#define JPET_TOMB_H

#include "TNamed.h"

/**
 * @brief Parametric class representing the abstract global channel number from the database.
 *
 * The TOMB channel abstracts over the hardware channels of certain TRB and fron-end boards (FEB).
 */
class JPetTOMB: public TNamed
{
protected:
  /*struct JPetTOMBInput
  {
    JPetTOMBInput(int p_id, std::string p_description);
    int m_id;
    std::string m_description;
  };*/
  
  int m_id;
  std::string m_description;
  //JPetTOMBInput m_TOMBInput;
  
public:
  JPetTOMB(int p_id, std::string p_description/*, int p_TOMBInputId, std::string p_TOMBInputDescription*/);
  virtual ~JPetTOMB(void);
  
  virtual int id(void) const;
  virtual std::string description(void) const;
  
private:
  ClassDef(JPetTOMB, 1);
};

#endif // JPET_TOMB_H
