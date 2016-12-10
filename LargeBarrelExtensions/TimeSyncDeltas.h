#ifndef _________DELTAS_H_______
#       define _________DELTAS_H_______
#include <iostream>
#include <memory>
#include <functional>
#include "../JPetHit/JPetHit.h"
#include "BarrelExtensions.h"
#include "PetDict.h"
struct SynchroStrip{double A,B;};
inline std::istream&operator>>(std::istream&str,SynchroStrip&item){
  return str>>item.A>>item.B;
}
inline std::ostream&operator<<(std::ostream&str,const SynchroStrip&item){
  return str<<item.A<<"\t"<<item.B;
}
class Synchronization{
public:
  typedef std::function<double(const std::vector<double>&)> TimeCalculation;
  Synchronization(const std::shared_ptr<AbstractBarrelMapping>map,std::istream&str,const TimeCalculation timecalc);
  virtual ~Synchronization();
  const SynchroStrip GetTimes(const JPetHit&hit)const;
private:
  std::shared_ptr<AbstractBarrelMapping> f_mapping;
  std::shared_ptr<JPetMap<SynchroStrip>> f_offsets;
  TimeCalculation f_time_calc;
};
const double DefaultTimeCalculation(const std::vector<double>&P);
#endif
