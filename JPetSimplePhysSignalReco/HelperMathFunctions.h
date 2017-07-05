/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file HelperMathFunctions.h
 *  @copyright Copyright (c) 2015, J-PET collaboration 
 *  @brief Helper mathematical functions used in the Reconstruction
 */

#ifndef _HELPERMATHFUNCTIONS_H_
#define _HELPERMATHFUNCTIONS_H_
#include <boost/serialization/array_wrapper.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace ublas = boost::numeric::ublas;

float polynomialFit(const ublas::vector<float>& t, const ublas::vector<float>& v_source, int alfa, float v0)
{
  ublas::vector<float> v(v_source);
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
