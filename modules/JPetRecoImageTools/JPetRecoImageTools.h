
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
 *  @file JPetRecoImageTools.h
 */

#ifndef _JPetRecoImageTools_H_
#define _JPetRecoImageTools_H_

#include <vector>
#include <cmath>
#include <functional>

class JPetRecoImageTools
{
public:
  using Matrix2D = std::vector<std::vector<int>>;
  using Matrix2DProj = std::vector<std::vector<double>>;
  using InterpolationFunc = std::function<double(int i, double y, std::function<double(int, int)>&)>;
  using RescaleFunc = std::function<void(Matrix2DProj& v, double minCutoff, double rescaleFactor)>;

  static double nearestNeighbour(int i, double y, std::function<double(int, int)>& func);
  static double linear(int i, double y, std::function<double(int, int)>& func);

  static std::function<double(int, int)> getValue(const Matrix2D& emissionMatrix);
  static std::function<double(int, int)> getValue2(const Matrix2D& emissionMatrix);

  /// Rescale the Matrix in the following way:
  /// 1. All the values less than minCutoff are set to minCutoff
  /// 2. Removes the common backgroud term. So the values start at zero
  /// 3. Rescales all values by rescaleFactor/maxElement
  /// The final value range is from 0 to rescaleFactor
  static void rescale(Matrix2DProj& v, double minCutoff, double rescaleFactor);
  /// PseudoRescale which does nothing
  static void nonRescale(Matrix2DProj&, double, double) {
    return;
  }

  /*! \brief Function returning sinogram matrix.
   *  \param emissionMatrix matrix,  needs to be NxN
   *  \param nViews number of views on object, degree step is calculated as (angleEnd - angleBeg) / nViews
   *  \param nScans number of scans on object, step is calculated as emissionMatrix[0].size() / nScans
   *  \param interpolationFunction function to interpolate values (Optional, default linear)
   *  \param angleBeg start angle for projection in deg (Optional, default 0)
   *  \param angleEnd end angle for projection in deg(Optional, default 180)
   *  \param rescaleFunc function that rescales the final result (Optional, default no rescaling)
  */
  static Matrix2DProj sinogram(Matrix2D& emissionMatrix,
                               int nViews, int nScans,
                               double angleBeg = 0, double angleEnd = 180,
                               InterpolationFunc interpolationFunction = linear,
                               RescaleFunc rescaleFunc = nonRescale,
                               int rescaleMinCutoff = 0,
                               int rescaleFactor = 255
                              );
private:
  JPetRecoImageTools();
  ~JPetRecoImageTools();
  JPetRecoImageTools(const JPetRecoImageTools&) = delete;
  JPetRecoImageTools& operator=(const JPetRecoImageTools&) = delete;

  static double calculateProjection(Matrix2D& emissionMatrix,
                                    double phi,
                                    int scanNumber,
                                    int nScans,
                                    InterpolationFunc& interpolationFunction
                                   );
  static inline double setToZeroIfSmall(double value, double epsilon) {
    if (std::abs(value) < epsilon) return 0;
    else return value;
  }
};

#endif
