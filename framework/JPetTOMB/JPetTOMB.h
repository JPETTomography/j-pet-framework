// JPet TOMB - JPetTOMB.h
#ifndef JPET_TOMB_H
#define JPET_TOMB_H

#include "TNamed.h"


class JPetTOMB: public TNamed
{
protected:
  struct TOMBInput
  {
    int fId;
    std::string fDescription;
    
    TOMBInput(int p_id, std::string p_description) : fId(p_id), fDescription(p_description)
    {}
  };
  
public:
  JPetTOMB(void);
  JPetTOMB(int p_id, std::string p_description, int p_setupId);
  ~JPetTOMB(void);
  
  int getId() const { return fId; }
  std::string getDescription() const { return fDescription; }
  int getSetupId() const { return fSetupId; }
  //TOMBInput getTOMBInput() const { return fTOMBInput; }
  
protected:
  int fId;
  std::string fDescription;
  int fSetupId;
  //TOMBInput fTOMBInput;
  
  ClassDef(JPetTOMB, 1);
};

#endif // JPET_TOMB_H
