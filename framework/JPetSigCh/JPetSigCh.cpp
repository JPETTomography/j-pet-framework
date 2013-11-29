#include "JPetSigCh.h"

ClassImp(JPetSigCh);

void JPetSigCh::init()
{
  SetNameTitle("JPetSigCh", "Signal Channel Structure");
  fPM = NULL;
  fTRB = NULL;
  fScin = NULL;
  fBarrelSlot = NULL;
  fAmpl = 0;
  fIsSlow = 0;
}

JPetSigCh::JPetSigCh(const JPetSigCh& obj)
{
  init();
  if (this != &obj) {
    fAmpl = obj.getAmpl();
    fIsSlow = obj.isSlow();
    setPM(obj.getPM());
    setTRB(obj.getTRB());
    setScin(obj.getScin());
    setBarrelSlot(obj.getBarrelSlot());
    fChannels.clear();
    for (int i = 0; i < obj.getChSet().size(); i++) fChannels.push_back(obj.getChSet()[i]);

    //fChannels.obj.getChSet();
  }
}

JPetSigCh::JPetSigCh(float edge_time, float fall_edge_time)
{
  init();
  if (fall_edge_time == 0) fIsSlow = 1;
  addCh(edge_time, fall_edge_time);
}

float JPetSigCh::getTime(JPetSigCh::EdgeType type, int ch_no) const
{
  if (fIsSlow && type == kFalling) {
    ERROR("This instance of JPetSigCh is of slow type, hence has no falling edge data.");
    return 0;
  }
  return fChannels[ch_no].find(type)->second;
}

template <class T>
void JPetSigCh::set(T** dest, const T& source) throw(bad_alloc)
{
  assert(dest != NULL);

  if ( &source == NULL && *dest != NULL ) {
    delete *dest;
    *dest = NULL;
    return;
  }

  if (&source != NULL) {
    if (*dest == NULL) {
      try {
        *dest = new T;
      } catch (bad_alloc& b_a) {
        ERROR("Could not allocate memory.");
        ERROR(b_a.what());
      }
    }
    ** dest = source;
  }
}

void JPetSigCh::addCh(float edge_time, float fall_edge_time)
{
  SingleCh tmp;
  tmp[kRising] = edge_time;
  tmp[kFalling] = fall_edge_time;
  fChannels.push_back(tmp);
}

JPetSigCh& JPetSigCh::operator=(const JPetSigCh& obj)
{
  JPetSigCh temp(obj);
  swap(temp, *this);
  return *this;
}
