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

#include <cmath>
#include <functional>
#include <vector>

#include <cassert>
#include <fftw3.h>
#include <memory>
#include <utility>

#include "JPetFilterInterface.h"

#include <boost/function_types/function_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>

class JPetRecoImageTools
{
public:
  using Matrix2D = std::vector< std::vector< int > >;
  using Matrix2DProj = std::vector< std::vector< double > >;
  using InterpolationFunc = std::function< double(
      int i, double y, std::function< double(int, int) > &) >;
  using RescaleFunc = std::function< void(Matrix2DProj &v, double minCutoff,
                                          double rescaleFactor) >;
  using FourierTransformFunction = std::function< Matrix2DProj(
      Matrix2DProj &sinogram, JPetFilterInterface &filterFunction) >;

  /// Returns a matrixGetter, that can be used to return matrix elements in the
  /// following way:
  /// if isTransposed is set to false, matrixGetter returns matrix[i][j]
  /// else matrixGetter returns matrix[j][i].
  /// In addition if the indices goes outside of the matrix range 0 is retuned.
  /// It is assumed that the input matrix is quadratic.
  /// The produced functions can be used as an input to interpolation functions.
  static std::function< double(int, int) >
  matrixGetterFactory(const Matrix2D &emissionMatrix,
                      bool isTransposed = false);

  /*! \brief function returning func(i,j) where j is the nearest neighbour
   * index with respect to y.
   *  \param i discrete index being the first parameter of the function func.
   *  \param y the double value for which the nearste neighoubring discrete
   * index is calculated.
   *  \param func function that returns double value based on two discrete i,j.
  */
  static double nearestNeighbour(int i, double y,
                                 std::function< double(int, int) > &func);
  /*! \brief Linear interpolation function returning (1-t)*func(i,j) + t*
   * func(i,j+1).
   *  \param i discrete index being the first parameter of the function func.
   *  \param y the double value for which the j index  and t parameters are
   * calculated.
   *  \param func function that returns double value based on two discrete i,j.
  */
  static double linear(int i, double y,
                       std::function< double(int, int) > &func);

  /// Rescale the Matrix in the following way:
  /// 1. All the values less than minCutoff are set to minCutoff
  /// 2. Removes the common backgroud term. So the values start at zero
  /// 3. Rescales all values by rescaleFactor/maxElement
  /// The final value range is from 0 to rescaleFactor
  static void rescale(Matrix2DProj &v, double minCutoff, double rescaleFactor);
  /// PseudoRescale which does nothing
  static void nonRescale(Matrix2DProj &, double, double) { return; }

  /*! \brief Function returning sinogram matrix.
   *  \param emissionMatrix matrix,  needs to be NxN
   *  \param nViews number of views on object, degree step is calculated as
   * (angleEnd - angleBeg) / nViews
   *  \param nScans number of scans on object, step is calculated as
   * emissionMatrix[0].size() / nScans
   *  \param interpolationFunction function to interpolate values (Optional,
   * default linear)
   *  \param angleBeg start angle for projection in deg (Optional, default 0)
   *  \param angleEnd end angle for projection in deg(Optional, default 180)
   *  \param rescaleFunc function that rescales the final result (Optional,
   * default no rescaling)
  */
  static Matrix2DProj createSinogramWithSingleInterpolation(
      Matrix2D &emissionMatrix, int nViews, int nScans, double angleBeg = 0,
      double angleEnd = 180, InterpolationFunc interpolationFunction = linear,
      RescaleFunc rescaleFunc = nonRescale, int rescaleMinCutoff = 0,
      int rescaleFactor = 255);

  static double calculateProjection(const Matrix2D &emissionMatrix, double phi,
                                    int scanNumber, int nScans,
                                    InterpolationFunc &interpolationFunction);

  /*! \brief Function returning sinogram matrix with both variables interpolated
   *  \param emissionMatrix matrix, needs to be NxN
   *  \param nAngles angle step is calculated as PI / nAngles
   *  \param rescaleFunc function that rescales the final result (Optional,
   * default no rescaling)
   *  \param rescaleMinCutoff min value to set in rescale (Optional)
   *  \param rescaleFactor max value to set in rescale (Optional)
  */
  static Matrix2DProj
  createSinogramWithDoubleInterpolation(Matrix2D &emissionMatrix, int nAngles,
                                        RescaleFunc rescaleFunc = nonRescale,
                                        int rescaleMinCutoff = 0,
                                        int rescaleFactor = 255);

  static double
  calculateProjection2(int step, double cos, double sin, int imageSize,
                       double center, double length,
                       std::function< double(int, int) > matrixGet);

  /*! \brief Function image from sinogram matrix
   *  \param sinogram matrix containing sinogram to backProject
   *  \param nAngles angle step is calculated as PI / nAngles
   *  \param rescaleFunc function that rescales the final result (Optional,
   * default no rescaling)
   *  \param rescaleMinCutoff min value to set in rescale (Optional)
   *  \param rescaleFactor max value to set in rescale (Optional)
  */
  static Matrix2DProj backProject(Matrix2DProj &sinogram, int angles,
                                  RescaleFunc rescaleFunc, int rescaleMinCutoff,
                                  int rescaleFactor);

  /*! \brief Function filtering given sinogram using fouriner implementation and
   filter
   *  \param ftf function filtering sinogram with given filter
   *  \param filter type of filter
   *  \param sinogram data to filter
  */
  static Matrix2DProj FilterSinogram(FourierTransformFunction &ftf,
                                     JPetFilterInterface &filter,
                                     Matrix2DProj &sinogram);

  /*! \brief Fourier transform implementation using FFTW library
   *  \param sinogram data to filter
   *  \param filter type of filter
  */
  static Matrix2DProj doFFTW(Matrix2DProj &sinogram,
                             JPetFilterInterface &filter);

  /*! \brief Fourier transform implementation
   *  \param sinogram data to filter
   *  \param filter type of filter
   */
  static Matrix2DProj doFFTSLOW(Matrix2DProj &sinogram,
                                JPetFilterInterface &filter);

private:
  JPetRecoImageTools();
  ~JPetRecoImageTools();
  JPetRecoImageTools(const JPetRecoImageTools &) = delete;
  JPetRecoImageTools &operator=(const JPetRecoImageTools &) = delete;

  static void doFFTSLOWT(std::vector< double > &Re, std::vector< double > &Im,
                         int size, int shift);

  static void doFFTSLOWI(std::vector< double > &Re, std::vector< double > &Im,
                         int size, int shift);

  static inline double setToZeroIfSmall(double value, double epsilon)
  {
    if (std::abs(value) < epsilon)
      return 0;
    else
      return value;
  }
};

#endif
