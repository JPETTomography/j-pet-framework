/**
 *  @copyright Copyright (c) 2015, The J-Pet Framework Authors.
 *  @file JPetFrame.h
 */

#ifndef JPET_FRAME_H
#define JPET_FRAME_H

#include <TRef.h>
#include "TNamed.h"


/**
 * @brief Parametric class representing database information on a whole mechanical structure frame of the PET setup.
 *
 * The frame consists of one or more layers represented by JPetLayer objects.
 */
class JPetFrame: public TNamed
{
 protected:
  const int fId;
  bool fIsActive;
  std::string fStatus;
  std::string fDescription;
  const int fVersion;
  const int fCreator_id;
  
 public:

  /// The default constructor sets fId, fVersion, fCreator_id to -1.  
  JPetFrame();
  JPetFrame(int id, bool isActive, std::string status, std::string description, int version, int creator_id);

  inline bool operator==(const JPetFrame& frame) { return getId() == frame.getId(); }
  inline bool operator!=(const JPetFrame& frame) { return getId() != frame.getId(); }
  int getId() const { return fId; }
  bool getIsActive() const { return fIsActive; }
  std::string getStatus() const { return fStatus; }
  std::string getDescription() const { return fDescription; }
  int getVersion() const { return fVersion; }
  int getCreator() const { return fCreator_id; }

 private:
  ClassDef(JPetFrame, 1);
};

#endif // JPET_FRAME_H
