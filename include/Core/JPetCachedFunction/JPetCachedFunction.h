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
 *  @file JPetCachedFunction.h
 */

#ifndef JPETCACHEDFUNCTION_H
#define JPETCACHEDFUNCTION_H

#include <vector>
#include <string>

namespace  jpet_common_tools
{

struct Range {
  Range(int bins, double min, double max): fBins(bins), fMin(min), fMax(max) {}
  Range() = default;
  int fBins = 100 ;  /// Number of times the function is sampled.
  double fMin =  -1.;
  double fMax = -1.;
};


struct JPetCachedFunctionParams {
  JPetCachedFunctionParams(const std::string& formula, const std::vector<double>& params):
    fFormula(formula), fParams(params)
  {
  }
  std::string fFormula;  /// Function formula that must be understood by TFormula from ROOT.
  std::vector<double> fParams; /// Parameters used by the function described by TFormula.
  bool fValidFunction = false;
};

/**
 * @brief  Class represent function of TFormula type with the cached values
 *
 * Special class based on TFormula that precomputes and stores function values in the cache. 
 * The classes JPetCachedFunction1D and JPetCachedFunction2D correspond to  func(x,p0,p1,...) 
 * and func(x,y, p0,p1, ...) implementations.
 * Base class JPetCachedFunction is not ment to be created separately.
 * 
 */
class JPetCachedFunction
{
protected:
  explicit JPetCachedFunction(const JPetCachedFunctionParams& params); 

public:
  JPetCachedFunctionParams getParams() const;
  std::vector<double> getValues() const;

protected:
  std::vector<double> fValues; /// Lookup table containg the function values.
  JPetCachedFunctionParams fParams;  /// Parameters describing the function.
};


/**
 * @brief 1D version of JPetCachedFunction so f(x,p0,p1,...) 
 */
class JPetCachedFunction1D: public JPetCachedFunction
{

public:
  explicit JPetCachedFunction1D(const JPetCachedFunctionParams& params, const Range& range);

  double operator()(double x) const;

protected:
  int xValueToIndex(double x) const;

private:
  Range fRange;
  double fStep = 1.; /// Step size with which the lookup table is filled.
};

/**
 * @brief 2D version of JPetCachedFunction so f(x,y, p0,p1,...) 
 */
class JPetCachedFunction2D: public JPetCachedFunction
{

public:
  JPetCachedFunction2D(const JPetCachedFunctionParams& params, const Range& xRange, const Range& yRange);

  double operator()(double x, double y) const;

protected:
  int xyValueToIndex(double x, double y) const;

private:
  std::pair<Range, Range> fRange;
  std::pair<double, double> fSteps = {1., 1.}; /// Step size with which the lookup table is filled.
};

}
#endif /*  !JPETCACHEDFUNCTION_H */
