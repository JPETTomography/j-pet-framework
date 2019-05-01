/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetCachedFunction.cpp
 */

#include <TFormula.h>
#include "./JPetCachedFunction.h"
#include "JPetLoggerInclude.h"

namespace  jpet_common_tools
{

JPetCachedFunction::JPetCachedFunction(const JPetCachedFunctionParams& params): fParams(params)
{
}

JPetCachedFunction1D::JPetCachedFunction1D(const JPetCachedFunctionParams& params, const Range& range): JPetCachedFunction(params), fRange(range)
{
  TFormula func("myFunc", fParams.fFormula.c_str());
  func.SetParameters(fParams.fParams.data());
  if (fRange.fBins <= 0) {
    ERROR("Number of bins must be greater than 0!");
    fParams.fValidFunction = false;
    return;
  }
  double step = (fRange.fMax - fRange.fMin) / fRange.fBins;
  if (step <= 0.) {
    ERROR("Check values of XMin:" + std::to_string(fRange.fMin) << " and XMax:" << std::to_string(fRange.fMax) << " !!! getX() function will not work correctly.");
    fParams.fValidFunction = false;
    return;
  }
  fStep = step;
  fValues.reserve(fRange.fBins);
  double currX = fRange.fMin;
  for (int i = 0; i < fRange.fBins; i++) {
    fValues.push_back(func.Eval(currX));
    currX = currX + step;
  }
  fParams.fValidFunction = true;
}

JPetCachedFunction2D::JPetCachedFunction2D(const JPetCachedFunctionParams& params, const Range& xRange, const Range& yRange): JPetCachedFunction(params), fRange(xRange, yRange)
{
  TFormula func("myFunc", fParams.fFormula.c_str());
  func.SetParameters(fParams.fParams.data());
  if (fRange.first.fBins <= 0) {
    ERROR("Number of bins X must be greater than 0!");
    fParams.fValidFunction = false;
    return;
  }
  if (fRange.second.fBins <= 0) {
    ERROR("Number of bins Y must be greater than 0!");
    fParams.fValidFunction = false;
    return;
  }

  double stepX = (fRange.first.fMax - fRange.first.fMin) / fRange.first.fBins;
  double stepY = (fRange.second.fMax - fRange.second.fMin) / fRange.second.fBins;
  if (stepX <= 0.) {
    ERROR("Check values of XMin:" + std::to_string(fRange.first.fMin) << " and XMax:" << std::to_string(fRange.first.fMax) << " !!!");
    fParams.fValidFunction = false;
    return;
  }
  if (stepY <= 0.) {
    ERROR("Check values of YMin:" + std::to_string(fRange.second.fMin) << " and YMax:" << std::to_string(fRange.second.fMax) << " !!!");
    fParams.fValidFunction = false;
    return;
  }

  fSteps = {stepX, stepY};
  fValues.reserve(fRange.first.fBins * fRange.second.fBins);
  double currX = fRange.first.fMin;
  double currY = fRange.second.fMin;
  for (int j = 0; j < fRange.second.fBins; j++) {
    for (int i = 0; i < fRange.first.fBins; i++) {
      fValues.push_back(func.Eval(currX, currY));
      currX = currX + stepX;
    }
    currX = fRange.first.fMin;
    currY = currY + stepY;
  }
  fParams.fValidFunction = true;
}


JPetCachedFunctionParams JPetCachedFunction::getParams() const
{
  return fParams;
}

std::vector<double> JPetCachedFunction::getValues() const
{
  return fValues;
}


double JPetCachedFunction1D::operator()(double x) const
{
  if ((x < fRange.fMin) || (x > fRange.fMax)) return 0;
  int index = xValueToIndex(x);
  assert(index >= 0);
  assert(((unsigned int) index) < getValues().size());
  return getValues()[index];
}

int JPetCachedFunction1D::xValueToIndex(double x) const
{
  assert(fStep > 0.);
  return x / fStep;
}


double JPetCachedFunction2D::operator()(double x, double y) const
{
  if ((x < fRange.first.fMin) || (x > fRange.first.fMax) || (y < fRange.second.fMin) || (y > fRange.second.fMax)) return 0;
  auto index = xyValueToIndex(x, y);
  assert(index >= 0);
  assert(((unsigned int) index) < fValues.size());
  return fValues[index];
}

int JPetCachedFunction2D::xyValueToIndex(double x, double y) const
{
  assert(fSteps.first > 0. && fSteps.second > 0.);
  return (x / fSteps.first) + (y / fSteps.second) * fRange.first.fBins;
}

}
