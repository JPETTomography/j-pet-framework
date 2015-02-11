/**
 * @file JPetLOR.cpp
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2013, Damian Trybek
 */

#include "./JPetLOR.h"

ClassImp(JPetLOR);

JPetLOR::JPetLOR() :
    TNamed("JPetLOR", "Event Structure"), fTime(0.0f), fQualityOfTime(0.0f),
    fTimeDiff(0.0f), fQualityOfTimeDiff(0.0f)
{
  fIsHitSet[0] = false;
  fIsHitSet[1] = false;
}

JPetLOR::JPetLOR(float Time, float QualityOfTime, JPetHit& firstHit,
                 JPetHit& secondHit) :
    TNamed("JPetLOR", "Event Structure"), fTime(Time),
    fQualityOfTime(QualityOfTime), fFirstHit(firstHit), fSecondHit(secondHit),
    fTimeDiff(0.0f), fQualityOfTimeDiff(0.0f)
{
  fIsHitSet[0] = true;
  fIsHitSet[1] = true;
}

JPetLOR::~JPetLOR()
{
}

