#include "./JPetEvent.h"

#include <cstddef>

JPetHits::JPetHits() :
    fFirst(NULL), fSecond(NULL) {
}

JPetHits::JPetHits (JPetHit& firstHit, JPetHit& secondHit) :
    fFirst(&firstHit), fSecond(&secondHit) {
}

JPetHits::~JPetHits() {
}

JPetEvent::JPetEvent() :
  fTime(0.0f), fQualityOfTime(0.0f), fHits(NULL) {
}

JPetEvent::~JPetEvent() {
}
