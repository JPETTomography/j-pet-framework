/**
 *  @copyright Copyright (c) 2016, J-PET collaboration
 *  @file JPetParamAsciiConstants.h
 *  @author Tomasz Kisielewski, tymorl@gmail.com
 *  @brief Constants for names in the json file format
 */

#ifndef JPETPARAMASCIICONSTANTS_H
#define JPETPARAMASCIICONSTANTS_H

#include <map>

#include "../JPetParamGetter/JPetParamConstants.h"

const std::map<ParamObjectType, std::string> objectsNames{
  {ParamObjectType::kScintillator, "scintillators"},
  {ParamObjectType::kPM, "PMs"},
  {ParamObjectType::kPMCalib, "PMCalibs"},
  {ParamObjectType::kBarrelSlot, "barrelSlots"},
  {ParamObjectType::kLayer, "layers"},
  {ParamObjectType::kFrame, "frames"},
  {ParamObjectType::kFEB, "FEBs"},
  {ParamObjectType::kTRB, "TRBs"},
  {ParamObjectType::kTOMBChannel, "TOMBChannels"}
};

#endif /*  !JPETPARAMASCIICONSTANTS_H */
