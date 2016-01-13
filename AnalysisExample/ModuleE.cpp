#include "./ModuleE.h"

ClassImp(ModuleE);

ModuleE::ModuleE(const char* name, const char* title,
                 const char * in_file_suffix, const char * out_file_suffix) :
    JPetCommonAnalysisModule(name, title, in_file_suffix, out_file_suffix) {
  setVersion(MODULE_VERSION);
}

ModuleE::~ModuleE() {
}

void ModuleE::begin() {
  fInitialHits = 0;
  fPairsFound = 0;
}

void ModuleE::exec() {
  if (fEvent > fEventNb - 2) return;

  // A dummy analysis example:
  JPetHit hits[10];
  int count = 0;
  // read subsequent hits
  while (true) {
    if (fEvent == fEventNb) break;
    hits[count] = (JPetHit&) fReader->getCurrentEvent();
    if (hits[count].getSignalA().getTSlotIndex()
        == hits[0].getSignalB().getTSlotIndex()) {
      count++;
      fReader->nextEvent();
    } else {
      break;
    }
  }

  fInitialHits += count;

  if (count >= 2) {

    for (int i = 0; i < count; i++) { // iterate over signals
      for (int j = i + 1; j < count; j++) {

        if (hits[i].getScintillator() != hits[j].getScintillator()) {
          // found 2 hits in different scintillators -> an event!

          // create an event object
          JPetLOR event;

          // convention: "first hit" is the one with earlier time
          if (hits[i].getTime() < hits[j].getTime()) {
            event.setFirstHit(hits[i]);
            event.setSecondHit(hits[j]);
          } else {
            event.setFirstHit(hits[j]);
            event.setSecondHit(hits[i]);
          }

          double dt = event.getFirstHit().getTime()
              - event.getSecondHit().getTime();
          event.setTimeDiff(dt);

          fPairsFound++;
          fWriter->write(event);

        }

      }
    }

  }

}

void ModuleE::end() {
  INFO(
      Form("From %d initial hits %d events were paired.", fInitialHits,
           fPairsFound));

}
