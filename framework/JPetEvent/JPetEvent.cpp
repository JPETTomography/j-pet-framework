/**
 * @file JPetEvent.cpp
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2013, Damian Trybek
 */


#include "./JPetEvent.h"

ClassImp(JPetEvent);

JPetEvent::JPetEvent() :
    TNamed("JPetEvent", "Event Structure"), fTime(0.0f), fQualityOfTime(0.0f),
    fFirstHit(NULL), fSecondHit(NULL) {
}

JPetEvent::JPetEvent(float Time, float QualityOfTime, JPetHit& firstHit, JPetHit& secondHit) :
    TNamed("JPetEvent","Event Structure"), fTime(Time), fQualityOfTime(QualityOfTime),
    fFirstHit(&firstHit), fSecondHit(&secondHit) {
}

JPetEvent::~JPetEvent() {
}
