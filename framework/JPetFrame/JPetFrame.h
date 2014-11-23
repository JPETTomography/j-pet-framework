// JPet Frame - JPetFrame.h
#ifndef JPET_FRAME_H
#define JPET_FRAME_H

#include "TNamed.h"
#include "../JPetUser/JPetUser.h"
#include "../JPetLayer/JPetLayer.h"


class JPetLayer;


/**
 * @brief Parametric class representing database information on a whole mechanical structure frame of the PET setup.
 *
 * The frame consists of one or more layers represented by JPetLayer objects.
 */
class JPetFrame: public TNamed
{
protected:
  int m_id;
  std::string m_status;
  std::string m_description;
  int m_version;
  JPetUser &m_JPetUser;		//creatorId
  JPetLayer &m_JPetLayer;
  
public:
  JPetFrame(int p_id, std::string p_status, std::string p_description, int p_version, JPetUser &p_JPetUser, JPetLayer &p_JPetLayer);
  virtual ~JPetFrame(void);
  
private:
  JPetFrame(const JPetFrame &frame);
  JPetFrame& operator=(const JPetFrame &frame);
  
public:
  virtual int id(void) const;
  virtual std::string status(void) const;
  virtual std::string description(void) const;
  virtual int version(void) const;

  inline bool operator==(const JPetFrame& frame) { return GetUniqueID() == frame.GetUniqueID(); }
  inline bool operator!=(const JPetFrame& frame) { return GetUniqueID() != frame.GetUniqueID(); }
  
private:
  ClassDef(JPetFrame, 1);
};

#endif // JPET_FRAME_H
