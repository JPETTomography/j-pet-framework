
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
#include <functional>

class JPetRecoImageTools
{
public:
  using Matrix2D = std::vector<std::vector<int>>;
  using Matrix2DProj = std::vector<std::vector<double>>;
  using InterpolationFunc = std::function<double(const Matrix2D&, double, double, int, int, int, bool)>;
  static double nearestNeighbour(const Matrix2D& emissionMatrix,
                                 double a, double b, int center, int x, int y, bool sang);
  static double linear(const Matrix2D& emissionMatrix,
                       double a, double b, int center, int x, int y, bool sang);

  /*! \brief Function returning sinogram matrix.
   *  \param emissionMatrix matrix,  needs to be NxN
   *  \param nViews number of views on object, degree step is calculated as (angleEnd - angleBeg) / nViews
   *  \param nScans number of scans on object, step is calculated as emissionMatrix[0].size() / nScans
   *  \param interpolationFunction function to interpolate values (Optional, default linear)
   *  \param angleBeg start angle for projection in deg (Optional, default 0)
   *  \param angleEnd end angle for projection in deg(Optional, default 180)
   *  \param scaleResult if set to true, scale result to <min, max> (Optional, default false)
   *  \param min minimum value in returned sinogram (Optional, default 0)
   *  \param max maximum value in returned sinogram (Optional, default 255)
  */
  static Matrix2DProj sinogram(Matrix2D& emissionMatrix,
                               int nViews, int nScans,
                               InterpolationFunc interpolationFunction = linear,
                               float angleBeg = 0, float angleEnd = 180, bool scaleResult = false,
                               int min = 0, int max = 255);
  /// Rescale the Matrix in the following way:
  /// 1. All the values less than minCutoff are set to minCutoff
  /// 2. Removes the common backgroud term. So the values start at zero
  /// 3. Rescales all values by rescaleFactor/maxElement
  /// The final value range is from 0 to rescaleFactor
  static void rescale(Matrix2DProj& v, double minCutoff, double rescaleFactor);
private:
  JPetRecoImageTools();
  ~JPetRecoImageTools();
  JPetRecoImageTools(const JPetRecoImageTools&) = delete;
  JPetRecoImageTools& operator=(const JPetRecoImageTools&) = delete;

  static double calculateProjection(Matrix2D& emissionMatrix, int N, double cos, double sin,
                                    double scale,
                                    InterpolationFunc& interpolationFunction, double a, double aa);
};

#endif
