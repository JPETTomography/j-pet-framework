#ifndef _JPETTRB_H_
#define _JPETTRB_H_

#include "TNamed.h"
#include <TRef.h>

/**
 * @brief Parametric class representing database information on parameters of a TRB board.
 *
 */
class JPetTRB: public TNamed
{
 public:
  JPetTRB();
  JPetTRB(int id, int type, int channel);
  ~JPetTRB();

  inline int getID() const { return fID; }
  inline int getType() const { return fType; }
  inline int getChannel() const { return fChannel; }
  inline void setID(int id) { fID = id; }
  inline void setType(int type) { fType = type; }
  inline void setChannel(int ch) { fChannel = ch; }

  inline bool operator==(const JPetTRB& trb) { return getID() == trb.getID(); }
  inline bool operator!=(const JPetTRB& trb) { return getID() != trb.getID(); }
  
 private:
  int fID;
  int fType;
  int fChannel;
  /// @todo do implementacji
  //JPetFEB* KBId;
  //KBType;
  //KBChan;
  //
  ClassDef(JPetTRB, 2);
  
protected:
  
  friend class JPetParamManager;
};

#endif
