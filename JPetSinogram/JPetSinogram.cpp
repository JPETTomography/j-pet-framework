#include "./JPetSinogram.h"
#include <boost/numeric/ublas/matrix.hpp>
using namespace boost::numeric::ublas;

JPetSinogram::JPetSinogram() { }

JPetSinogram::~JPetSinogram() { }

long long JPetSinogram::forwardProjection(float s, float theta, matrix<int> emissionMatrix) {
  long long sum = 0;
  if(theta == 0) {
    for(unsigned int i = 0; i < emissionMatrix.size2(); i++) {
      sum += emissionMatrix(s, i);
    }
  } else if(theta == 90) {
    for(unsigned int i = 0; i < emissionMatrix.size1(); i++) {
      sum += emissionMatrix(i, s);
    }
  }

  return sum;
}
