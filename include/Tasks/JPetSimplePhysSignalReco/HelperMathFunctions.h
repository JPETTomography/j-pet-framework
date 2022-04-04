/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 */

#ifndef HELPERMATHFUNCTIONS_H
#define HELPERMATHFUNCTIONS_H

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>

/**
 * @brief Helper mathematical functions used in the reconstruction of signal time
 */
namespace ublas = boost::numeric::ublas;

double polynomialFit(const ublas::vector<double>& t, const ublas::vector<double>& v_source, int alfa, double v0)
{
  ublas::vector<double> v(v_source);
  int K;
  double tSig = -1.0;
  double a, b;
  double meanT = 0.0;
  double meanV = 0.0;
  double sx = 0.0;
  double sxy = 0.0;

  if (v.size() != t.size())
  {
    return tSig;
  }

  K = v.size();
  if ((K < 2) || (alfa < 1))
  {
    if (K == 1)
    {
      tSig = t(0);
    }
    return tSig;
  }

  for (int i = 0; i < K; i++)
  {
    v(i) = pow(-v(i), 1.0 / alfa);
  }

  for (int i = 0; i < K; i++)
  {
    meanT = meanT + t(i);
    meanV = meanV + v(i);
  }
  meanT = meanT / K;
  meanV = meanV / K;

  for (int i = 0; i < K; i++)
  {
    sx = sx + (t(i) - meanT) * (t(i) - meanT);
    sxy = sxy + (t(i) - meanT) * (v(i) - meanV);
  }
  a = sxy / sx;
  b = meanV - a * meanT;

  if (fabs(a) < 1e-10)
  {
    tSig = t(0);
  }
  else
  {
    if (v0 > 0.0)
      v0 = 0.0;
    tSig = (pow(-v0, 1.0 / alfa) - b) / a;
  }
  return tSig;
}

#endif /* !HELPERMATHFUNCTIONS_H */
