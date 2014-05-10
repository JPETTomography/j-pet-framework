#include "JPetSigCh.h"
#include <limits>

ClassImp(JPetSigCh);
/// @todo init is not complete
const float JPetSigCh::kTimeUnset = std::numeric_limits<float>::infinity();
void JPetSigCh::init()
{
  SetNameTitle("JPetSigCh", "Signal Channel Structure");
  fAmpl = 0;
  fIsSlow = false;
  fIsComplete = false;
}

/// @todo what to do with those pointers, that is a horrible leak now
JPetSigCh::JPetSigCh(const JPetSigCh& obj)
{
  init();
  if (this != &obj) {
    fAmpl = obj.fAmpl;
    fIsSlow = obj.fIsSlow;
    fIsComplete = obj.fIsComplete;
    fPM = obj.fPM;
    fTRB = obj.fTRB;
    fScin = obj.fScin;
    fBarrelSlot = obj.fBarrelSlot;
    fChannels = obj.fChannels;
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

float JPetSigCh::getTime(EdgeType type) const {
  assert ((type == kRising) || (type == kFalling));
  if (type == kRising) return fChannels.first;
  if (type == kFalling) { 
    if (isSlow()) {
      ERROR("This instance of JPetSigCh is of slow type, hence has no falling edge data.");
      return 0;
    }
    return fChannels.second;
  }
  return 0;
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

void JPetSigCh::addCh(float rise_edge_time, float fall_edge_time)
{
  fChannels.first = rise_edge_time;
  fChannels.second = fall_edge_time;
}

