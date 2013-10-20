#include "./JPetEvent.h"

ClassImp(JPetEvent);

JPetEvent::JPetEvent() :
    TNamed("JPetEvent", "Event Structure"), fTime(0.0f), fQualityOfTime(0.0f),
    fHits(new std::pair<JPetHit*,JPetHit*>) {
  *fHits = make_pair((JPetHit*)NULL,(JPetHit*)NULL);
}

JPetEvent::JPetEvent(float Time, float QualityOfTime, JPetHits& Hits) :
    TNamed("JPetEvent","Event Structure"), fTime(Time), fQualityOfTime(QualityOfTime),
    fHits(&Hits) {
}

JPetEvent::~JPetEvent() {
}
