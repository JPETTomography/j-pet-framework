
#ifndef _JPETSINOGRAM_H_
#define _JPETSINOGRAM_H_

#include <boost/numeric/ublas/matrix.hpp>
using namespace boost::numeric::ublas;
class JPetSinogram {
public:
  JPetSinogram();
  ~JPetSinogram();

  long long forwardProjection(float s, float theta, matrix<int> emissionMatrix); //row major orientation, element m[i,j]
  //is mapped as i*n + j element
private:

};


#endif
