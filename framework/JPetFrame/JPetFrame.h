// JPet Frame - JPetFrame.h
#ifndef JPET_FRAME_H
#define JPET_FRAME_H

/*#include "TNamed.h"
#include "../JPetUser/JPetUser.h"
#include "../JPetLayer/JPetLayer.h"*/

#include <TRef.h>
#include "TNamed.h"

//class JPetLayer;


/**
 * @brief Parametric class representing database information on a whole mechanical structure frame of the PET setup.
 *
 * The frame consists of one or more layers represented by JPetLayer objects.
 */
class JPetFrame: public TNamed
{
protected:
  int fId;
  bool fIsActive;
  std::string fStatus;
  std::string fDescription;
  int fVersion;
  int fCreator_id;
  
  //friend class JPetParamManager;
  
public:
  JPetFrame(void);
  JPetFrame(int id, bool isActive, std::string status, std::string description, int version, int creator_id);
  ~JPetFrame(void);

  inline bool operator==(const JPetFrame& frame) { return getId() == frame.getId(); }
  inline bool operator!=(const JPetFrame& frame) { return getId() != frame.getId(); }
  
  int getId() const { return fId; }
  bool getIsActive() const { return fIsActive; }
  std::string getStatus() const { return fStatus; }
  std::string getDescription() const { return fDescription; }
  int getVersion() const { return fVersion; }
  int getCreator() const { return fCreator_id; }
  
/*private:
  JPetFrame(const JPetFrame &frame);
  JPetFrame& operator=(const JPetFrame &frame);*/

private:
  ClassDef(JPetFrame, 1);
};

#endif // JPET_FRAME_H
