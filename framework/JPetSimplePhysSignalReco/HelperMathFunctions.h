/**
 * @file HelperMathFunctions.h
 * @copyright Copyright (c) 2015, J-PET collaboration 
 * @brief Helper mathematical functions used in the Reconstruction
 * module. 
 */
#ifndef _HELPERMATHFUNCTIONS_H_
#define _HELPERMATHFUNCTIONS_H_
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
using namespace boost::numeric::ublas;

float polynomialFit(const vector<float>& t, const vector<float>& v_source, int alfa, float v0)
{
  vector<float> v(v_source);
  int K;
  float tSig = -1.0;
  float a, b;
  float meanT = 0.0;
  float meanV = 0.0;
  float sx  = 0.0;
  float sy  = 0.0;
  float sxy = 0.0;

  if (v.size() != t.size() )
    return tSig;

  K = v.size();

  if ((K < 2) || (alfa < 1)) {
    // no regression possible - return
    if (K == 1) {
      tSig = t(0);
    }

    return tSig;
  }

  // prepare the data to fit:
  // 1. change the sign to positive values
  // 2. calculate power 1/alfa
  for (int i = 0; i < K; i++)
    v(i) = pow(-v(i), 1.0 / alfa);

  // evaluate meanT, meanV
  for (int i = 0; i < K; i++) {
    meanT  = meanT + t(i);
    meanV  = meanV + v(i);
  }
  meanT = meanT / K;
  meanV = meanV / K;

  // evaluate sx, sy, sxy
  for (int i = 0; i < K; i++) {
    sx = sx + (t(i) - meanT) * (t(i) - meanT);
    sy = sy + (v(i) - meanV) * (v(i) - meanV);
    sxy = sxy + (t(i) - meanT) * (v(i) - meanV);
  }

  a = sxy / sx;
  b = meanV - a * meanT;

  if (fabs(a) < 1e-10)
    tSig = t(0);
  else {
    if (v0 > 0.0)
      v0 = 0.0;

    tSig = (pow(-v0, 1.0 / alfa) - b) / a;
  }
  return tSig;
}

#endif
