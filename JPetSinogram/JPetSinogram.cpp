#include "./JPetSinogram.h"
#include <boost/numeric/ublas/matrix.hpp>
using namespace boost::numeric::ublas;

JPetSinogram::JPetSinogram() { }

JPetSinogram::~JPetSinogram() { }

long long JPetSinogram::forwardProjection(float s, float theta, matrix<int> emissionMatrix) {
  long long sum = 0;
  for(unsigned int i = 0; i < emissionMatrix.size2(); i++) {
    for(unsigned int j = s; j < emissionMatrix.size1(); j++) {
      sum += emissionMatrix(i, j);
    }
  }

  return sum;
}
