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
  } else if(theta == 45) {
    unsigned int j = (emissionMatrix.size2() - 1) - s < 0 ? 0 : (emissionMatrix.size2() - 1) - s;
    unsigned int i = (emissionMatrix.size2() - 1) - s < 0 ? - ((emissionMatrix.size2() - 1 - s)) : 0;// select row, start from upper right corner
    for(; j < emissionMatrix.size2(); j++) { //-1 bcs matrix start from 0
      if(i < emissionMatrix.size1()) {
        sum += emissionMatrix(i, j);
        i++;
      }
      else { } // exception
    }

  }

  return sum;
}
