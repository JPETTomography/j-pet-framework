/**
 * @file JPetLOR.cpp
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2013, Damian Trybek
 */


#include "./JPetLOR.h"

ClassImp(JPetLOR);

JPetLOR::JPetLOR() :
    TNamed("JPetLOR", "Event Structure"), fTime(0.0f), fQualityOfTime(0.0f),
    fTimeDiff(0.0f), fQualityOfTimeDiff(0.0f), fNhits(0)
{
}

JPetLOR::JPetLOR(float Time, float QualityOfTime, JPetHit& firstHit, JPetHit& secondHit) :
    TNamed("JPetLOR","Event Structure"), fTime(Time), fQualityOfTime(QualityOfTime),
    fFirstHit(firstHit), fSecondHit(secondHit),
    fTimeDiff(0.0f), fQualityOfTimeDiff(0.0f), fNhits(2) {
}

JPetLOR::~JPetLOR() {
}

int JPetLOR::addHit(JPetHit & hit){
  
  if( fNhits == 0 ){
    fFirstHit = hit;
    return fNhits++;
  }else if( fNhits == 1){
    fSecondHit = hit;
    return fNhits++;
  }else{
    return 0;
  }
}

const JPetHit & JPetLOR::operator[](int i) const{
  assert( i < fNhits && i > 0 );
  if( i==0 ){
    return fFirstHit;
  }else{
    return fSecondHit;
  }
}
