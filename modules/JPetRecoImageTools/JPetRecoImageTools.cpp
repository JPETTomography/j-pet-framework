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

double JPetRecoImageTools::nearestNeighbour(Matrix2D& emissionMatrix, double a, double b,
    int center, int x, int y, bool sang)
{
  if (sang) {
    y = (int)std::round(a * x + b) + center;
    if (y >= 0 && y < (int) emissionMatrix[0].size())
      return emissionMatrix[x + center][y];
    else return 0;
  } else {
    x = (int)std::round(a * y + b) + center + 1; // not really know why need to +1 to x, but it works
    if (x >= 0 && x < (int)emissionMatrix.size())
      return emissionMatrix[x][y + center];
    else return 0;
  }
}

double JPetRecoImageTools::linear(Matrix2D& emissionMatrix, double a, double b,
                                  int center, int x, int y, bool sang)
{
  if (sang) {
    y = (int)std::round(a * x + b) + center;
    double weight = std::abs((a * x + b) - std::ceil(a * x + b));
    if (y >= 0 && y < (int)emissionMatrix[0].size()) {
      return (1 - weight) * emissionMatrix[x + center][y] + weight * emissionMatrix[x + center][y + 1];
    } else return 0;
  } else {
    x = (int)std::round(a * y + b) + center + 1; // not really know why need to +1 to x, but it works
    double weight = std::abs((a * y + b) - std::ceil(a * y + b));
    if (x >= 0 && x + 1 < (int)emissionMatrix.size()) {
      if (weight == 0)
        return emissionMatrix[x][y + center];
      else
        return (1 - weight) * emissionMatrix[x][y + center] + weight * emissionMatrix[x + 1][y + center];
    } else return 0;
  }
}


JPetRecoImageTools::Matrix2DProj JPetRecoImageTools::sinogram(Matrix2D& emissionMatrix,
    int nViews, int nScans,
    InterpolationFunc interpolationFunction,
    float angleBeg, float angleEnd, bool scaleResult, int min, int max)
{
  assert(emissionMatrix.size() > 0);
  assert(emissionMatrix.size() == emissionMatrix[0].size());
  assert(nViews > 0);
  assert(nScans > 0);
  assert(min < max);
  assert(angleBeg < angleEnd);

  //create vector of size nViews, initialize it with vector of size nScans
  Matrix2DProj proj(nViews, std::vector<double>(nScans));

  float stepsize = (angleEnd - angleBeg) / nViews;
  assert(stepsize > 0); //maybe != 0 ?

  const int inputMatrixSize = emissionMatrix.size();
  const int center = inputMatrixSize / 2;

  //if no. nScans is greater than the image width, then scale will be <1
  const double scale = inputMatrixSize / nScans;
  const double kSin45deg = std::sqrt(2) / 2; /// sin(45) deg

  int N = 0;
  int i = 0;

  double sinValue = 0., cosValue = 0.;
  double a = 0., aa = 0.;

  for (auto phi = angleBeg; phi < angleEnd; phi = phi + stepsize) {
    sinValue = std::sin((double)phi * M_PI / 180 - M_PI / 2);
    if (std::abs(sinValue) < 0.0000001) {
      sinValue = 0;
    }
    cosValue = std::cos((double)phi * M_PI / 180 - M_PI / 2);
    if (std::abs(cosValue) < 0.0000001) {
      cosValue = 0;
    }
    a = -cosValue / sinValue;
    if (std::isinf(a) || std::isinf(-a) || std::abs(a) < 0.0000001) {
      a = 0;
      aa = 0;
    } else aa = 1 / a;
    for (auto scanNumber = 0; scanNumber < nScans; scanNumber++) {
      N = scanNumber - nScans / 2;
      proj[i][nScans - 1 - scanNumber] = JPetRecoImageTools::calculateProjection(emissionMatrix, std::abs(sinValue) > kSin45deg,
                                         N, cosValue, sinValue, scale, center,
                                         interpolationFunction, a, aa);
    }
    i++;
  }

  if (scaleResult) {
    JPetRecoImageTools::rescale(proj, min, max);
  }

  return proj;
}

double JPetRecoImageTools::calculateProjection(Matrix2D& emissionMatrix, bool sang, int N, double cos,
    double sin, double scale, int center,
    InterpolationFunc& interpolationFunction,
    double a, double aa)
{
  double b = 0.;
  if (sang)
    b = (N - cos - sin) / sin;
  else
    b = (N - cos - sin) / cos;
  b *= scale;
  double value = 0.;
  int x = 0;
  int y = 0;
  if (sang) {
    for (x = -center; x < center; x++) {
      value += interpolationFunction(emissionMatrix, a, b, center, x, y, sang);
    }
    value /= std::abs(sin);
  } else {
    for (y = -center; y < center; y++) {
      value += interpolationFunction(emissionMatrix, aa, b, center, x, y, sang);
    }
    value /= std::abs(cos);
  }
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
