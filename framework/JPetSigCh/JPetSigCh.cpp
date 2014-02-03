#include "JPetSigCh.h"

ClassImp(JPetSigCh);

void JPetSigCh::init()
{
  SetNameTitle("JPetSigCh", "Signal Channel Structure");
  fPM = 0;
  fTRB = 0;
  fScin = 0;
  fBarrelSlot = 0;
  fAmpl = 0;
  fIsSlow = false;
}

/// @todo what to do with those pointers, that is a horrible leak now
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
    fChannels = obj.getChSet();
  }
}

JPetSigCh& JPetSigCh::operator=(JPetSigCh obj)
{
  my_swap(*this, obj);
  return *this;
}

JPetSigCh::JPetSigCh(float edge_time, float fall_edge_time)
{
  init();
  if (fall_edge_time == 0) fIsSlow = true;
  addCh(edge_time, fall_edge_time);
}

/// @todo add some destructor
//JPetSigCh::~JPetSigCh() 
//{
//
//}

float JPetSigCh::getTime(JPetSigCh::EdgeType type, int ch_no) const
{
  if (fIsSlow && type == kFalling) {
    ERROR("This instance of JPetSigCh is of slow type, hence has no falling edge data.");
    return 0;
  }
  return fChannels[ch_no].find(type)->second;
}

template <class T>
void JPetSigCh::set(T** dest, const T& source) throw(std::bad_alloc)
{
  assert(dest != 0);

  if ( &source == 0 && *dest != 0 ) {
    delete *dest;
    *dest = 0;
    return;
  }

  if (&source != 0) {
    if (*dest == 0) {
      try {
        *dest = new T;
      } catch (std::bad_alloc& b_a) {
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

