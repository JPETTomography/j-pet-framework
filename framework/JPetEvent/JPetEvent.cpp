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

int JPetEvent::AddHit(JPetHit* hit){
  assert( hit != NULL );
  if( fFirstHit == NULL ){
    fFirstHit = hit;
    return 1;
  }else if( fSecondHit == NULL){
    fSecondHit = hit;
    return 2;
  }else{
    return 0;
  }
}

const JPetHit & JPetEvent::operator[](int i) const{
  assert( i < 2 && i > 0 );
  if( i==0 ){
    return *fFirstHit;
  }else{
    return *fSecondHit;
  }
}
