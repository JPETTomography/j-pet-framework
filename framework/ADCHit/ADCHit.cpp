#include "ADCHit.h"

ClassImp(ADCHit);

ADCHit::ADCHit() {
  Clear();
}

ADCHit::~ADCHit() {
}

void ADCHit::Clear() {
  channel = -1;
  ADC = -1;
  localPtr = 0;
  nHits = 0;
  for (int i = 0; i < MAX_SAMPLES; i++) samples[i] = -1;
}
