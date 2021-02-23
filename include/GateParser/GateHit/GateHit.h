#ifndef GateHit_h
#define GateHit_h

#include <TObject.h>

class GateHit : public TObject
{
public:
  GateHit() {}
  void copy(GateHit gh)
  {
    event_id = gh.event_id;
    track_id = gh.track_id;
    edep = gh.edep;
    time = gh.time;
    posx = gh.posx;
    posy = gh.posy;
    posz = gh.posz;
    sourcex = gh.sourcex;
    sourcey = gh.sourcey;
    sourcez = gh.sourcez;
    sci_id = gh.sci_id;
  }
  int event_id = -1;
  int track_id = -1;
  double edep = 0.0;
  double time = 0.0;
  double posx = 0.0;
  double posy = 0.0;
  double posz = 0.0;
  double sourcex = 0.0;
  double sourcey = 0.0;
  double sourcez = 0.0;
  int sci_id = 0;
  ClassDef(GateHit, 2)
};

#endif
