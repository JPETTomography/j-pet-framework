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
 *  @file JPetRecoImageTools.cpp
 */

#include "./JPetRecoImageTools.h"
#include "../../JPetLoggerInclude.h"
#include <vector>
#include <utility>
#include <cmath>
#include <functional>
#include <cassert>
#include <memory>

JPetRecoImageTools::JPetRecoImageTools() {}

JPetRecoImageTools::~JPetRecoImageTools() {}

double JPetRecoImageTools::nearestNeighbour( int i, double y, std::function<double(int, int)>& func)
{
  int j = std::round(y);
  return func (i, j);
}

double JPetRecoImageTools::linear(int i, double y, std::function<double(int, int)>& func)
{
  int j = std::floor(y);
  double weight = std::abs(y - std::floor(y));
  return (1 - weight) * func(i, j) + weight * func(i, j + 1);
}

std::function<double(int, int)> JPetRecoImageTools::matrixGetterFactory(const Matrix2D& emissionMatrix, bool isTransposed)
{
  if (!isTransposed) {
    return [& emissionMatrix](int i, int j) {
      if (i >= 0 && i < (int) emissionMatrix[0].size() && j >= 0 && j < (int) emissionMatrix.size() ) {
        return emissionMatrix[i][j];
      } else {
        return 0;
      }
    };
  } else {
    return [& emissionMatrix](int i, int j) {
      if (i >= 0 && i < (int) emissionMatrix.size() && j >= 0 && j < (int) emissionMatrix[0].size() ) {
        return emissionMatrix[j][i];
      } else {
        return 0;
      }
    };
  }
}

JPetRecoImageTools::Matrix2DProj JPetRecoImageTools::sinogram(Matrix2D& emissionMatrix,
    int nViews, int nScans,
    double angleBeg, double angleEnd,
    InterpolationFunc interpolationFunction,
    RescaleFunc rescaleFunc,
    int minCutoff,
    int scaleFactor)
{
  assert(emissionMatrix.size() > 0);
  assert(emissionMatrix.size() == emissionMatrix[0].size());
  assert(nViews > 0);
  assert(nScans > 0);
  assert(angleBeg < angleEnd);
  assert(minCutoff < scaleFactor);

  //create vector of size nViews, initialize it with vector of size nScans
  Matrix2DProj proj(nViews, std::vector<double>(nScans));

  float stepsize = (angleEnd - angleBeg) / nViews;
  assert(stepsize > 0); //maybe != 0 ?

  int viewIndex = 0;
  for (auto phi = angleBeg; phi < angleEnd; phi = phi + stepsize, viewIndex++) {
    for (auto scanNumber = 0; scanNumber < nScans; scanNumber++) {
      proj[viewIndex][nScans  - 1 - scanNumber] = JPetRecoImageTools::calculateProjection(emissionMatrix,
          phi, scanNumber, nScans,
          interpolationFunction);
    }
  }
  rescaleFunc(proj, minCutoff, scaleFactor);
  return proj;
}



JPetRecoImageTools::Matrix2DProj JPetRecoImageTools::sinogram2(
    Matrix2D& emissionMatrix,
    int nAngles, RescaleFunc rescaleFunc,
    int rescaleMinCutoff,
    int rescaleFactor)
{
  int imageSize = emissionMatrix.size();
  double center = (imageSize - 1) / 2.0;

  double angleStep = M_PI / nAngles;
  double length = center * center;
  Matrix2DProj proj(imageSize, std::vector<double>(nAngles));
  std::function<double(int, int)> matrixGet;
  matrixGet  = matrixGetterFactory(emissionMatrix, false); // The matrix  elements will be taken as (x,y).
  for (int angle = 0 ; angle < nAngles; angle++) 
  {
    double cos = std::cos((double)angle * angleStep);
    double sin = std::sin((double)angle * angleStep);
    for (int scanNumber = 0; scanNumber < imageSize - 1; scanNumber++) 
    {
      proj[scanNumber][angle] = calculateProjection2(scanNumber, cos, sin, imageSize, center, length, matrixGet);
    }
  }
  rescaleFunc(proj, rescaleMinCutoff, rescaleFactor);
  return proj;
}

double JPetRecoImageTools::calculateProjection2(int step, double cos, double sin, 
                                                int imageSize, double center, double length, 
                                                std::function<double(int, int)> matrixGet)
{
  double stepMinusCenter = step - center;
  double xtmp = center + stepMinusCenter * cos;
  double ytmp = center - stepMinusCenter * sin;
  //int nmin = std::floor(center - std::sqrt((length - (stepMinusCenter * stepMinusCenter)))); 
  //TODO Repair, when step is last step in emissionMatrix it's calculating wrong value
  //for nmin = 0 we checking a lot of unnecessary values
  int nmin = 0;
  //std::cout << "center: " << center << " length: " << length << " m * m: " << stepMinusCenter * stepMinusCenter << "\n";
  //std::cout << "nmin: " << nmin << "\n";
  double p = 0.0; 
  for(int n = nmin; n < imageSize - nmin; n++)
  {
    double nMinusCenter = (double)n - center;
    int x = std::floor((xtmp - nMinusCenter * sin) + 0.5);
    int y = std::floor((ytmp - nMinusCenter * cos) + 0.5);
    p += matrixGet(x, y);
    //std::cout << "x: " << x << " y: " << y << " val: " << matrixGet(x, y) << "\n";
  }
  return p;
}


double JPetRecoImageTools::calculateProjection(const Matrix2D& emissionMatrix, double angle, int scanNumber, int nScans,
    InterpolationFunc& interpolationFunction)
{
  int N = scanNumber - std::floor(nScans / 2) ;
  const int kInputMatrixSize = emissionMatrix.size();
  //if no. nScans is greater than the image width, then scale will be <1
  const double scale = kInputMatrixSize / nScans;
  const double kSin45or125deg = std::sqrt(2) / 2; /// sin(45) deg
  const double kEpsilon = 0.0000001;
  const double kDegToRad = M_PI / 180.;

  double sin = std::sin(angle * kDegToRad - M_PI / 2.);
  sin = setToZeroIfSmall(sin, kEpsilon);
  double cos = std::cos(angle * kDegToRad - M_PI / 2.);
  cos = setToZeroIfSmall(cos, kEpsilon);

  double a = 0.;
  double b = 0.;
  /// The line over which we integrate is perpendicular to any line with the slope = tg(angle), so it is always  -1/tg(angle).
  /// If the angle is between (45 to 125)
  /// we use  y = a * x + b, and we iterate over rows of the matrix (x).
  /// If the angle is between [0 to 45 ] or [125 to 180]
  /// we use x = a* y +b, and we iterate over columns of the matrix (y)
  bool angleRange45To125 = std::abs(sin) > kSin45or125deg;
  double divided = 1.;
  std::function<double(int, int)> matrixGet;

  if (angleRange45To125) {
    assert(sin);
    a = -cos / sin;
    b = (N - cos - sin) / sin;
    b *= scale;
    matrixGet  = matrixGetterFactory(emissionMatrix, false); // The matrix  elements will be taken as (x,y).
    divided = std::abs(sin);
  } else {
    assert(cos);
    a = -sin / cos;
    b = (N - cos - sin) / cos;
    b *= scale;
    matrixGet  = matrixGetterFactory(emissionMatrix, true); // The matrix  elements will be taken as (y, x) - transposed.
    divided = std::abs(cos);
  }
  const int kMatrixCenter = std::floor(emissionMatrix.size() / 2);
  double value = 0.;
  for (auto i = -kMatrixCenter; i < kMatrixCenter; i++) {
    value += interpolationFunction(i + kMatrixCenter , a * i + b + kMatrixCenter, matrixGet);
  }
  value /= divided;
  return value;
}

void JPetRecoImageTools::rescale(Matrix2DProj& matrix, double minCutoff, double rescaleFactor)
{

  double datamax = matrix[0][0];
  double datamin = matrix[0][0];
  for (unsigned int k = 0; k < matrix.size(); k++) {
    for (unsigned int j = 0; j < matrix[k].size(); j++) {
      ///Applying min Cutoff
      if (matrix[k][j] < minCutoff)
        matrix[k][j] = minCutoff;
      /// Finding the largest and the smallest element in the matrix.
      if (matrix[k][j] > datamax)
        datamax = matrix[k][j];
      if (matrix[k][j] < datamin)
        datamin = matrix[k][j];
    }
  }
  /// datamin represents the constant background factor.
  if ((datamax - datamin) == 0.) {
    WARNING("Maximum value in the matrix to rescale is 0. No rescaling performed.");
    return;
  }

  for (unsigned int k = 0; k < matrix.size(); k++) {
    for (unsigned int j = 0; j < matrix[0].size(); j++) {
      matrix[k][j] = (matrix[k][j] - datamin) * rescaleFactor / (datamax - datamin);
    }
  }
}
