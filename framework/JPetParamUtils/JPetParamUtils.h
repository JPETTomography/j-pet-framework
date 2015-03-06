/**
 *  @copyright Copyright (c) 2015, The J-Pet Framework Authors.
 *  @file JPetParamUtils.h
 *  @author Tomasz Bednarski, tomasz.bednarski@uj.edu.pl based on scheme from Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief Helper class to calculate several things based on parameter objects.
 */

#ifndef JPETPARAMUTILS_H
#define JPETPARAMUTILS_H

#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetLayer/JPetLayer.h"
#include "../../JPetLoggerInclude.h"
#include "TMath.h"

class JPetParamUtils
{
 public:
  /**
     @brief Function for calculation distance between two barrel slots in XY plane (perpendicular to strips) based on JPetBarrelSlot objects
   **/
  static double distanceXY(const JPetBarrelSlot& slot1, const JPetBarrelSlot& slot2);

  /**
     @brief Function for calculation distance between two photomultipliers  in XY plane (perpendicular to strips) based on JPetPM object

     It does not take into account photomultipliers side of the barrel. For photomultipliers from different sides the function calculate the distance as if they were at the same side (only XY plane).
  **/
  static double distanceXY(const JPetPM& PM1, const JPetPM& PM2);

 private:
  JPetParamUtils(const JPetParamUtils&){}
  void operator=(const JPetParamUtils&){}
};

#endif /*  !JPETPARAMUTILS_H */
