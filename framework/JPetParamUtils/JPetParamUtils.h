/**
 *  @copyright Copyright (c) 2015, The J-Pet Framework Authors.
 *  @file JPetParamUtils.h
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief Helper class to calculate several things based on parameter objects.
 */

#ifndef JPETPARAMUTILS_H
#define JPETPARAMUTILS_H

#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetLayer/JPetLayer.h"

class JPetParamUtils
{
 public:
  /// -1 is returned if slot1 and slot2 does not belong to the same layer.
  static double distance(const JPetBarrelSlot& slot1, const JPetBarrelSlot& slot2) {
    return -1;
  }
 private:
  JPetParamUtils(const JPetParamUtils&);
  void operator=(const JPetParamUtils&);
};

#endif /*  !JPETPARAMUTILS_H */
