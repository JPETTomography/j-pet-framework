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

JPetRecoImageTools::JPetRecoImageTools() {}

JPetRecoImageTools::~JPetRecoImageTools() {}

double
JPetRecoImageTools::nearestNeighbour(int i, double y,
                                     std::function< double(int, int) > &func)
{
  int j = std::round(y);
  return func(i, j);
}

double JPetRecoImageTools::linear(int i, double y,
                                  std::function< double(int, int) > &func)
{
  int j = std::floor(y);
  double weight = std::abs(y - std::floor(y));
  return (1 - weight) * func(i, j) + weight * func(i, j + 1);
}

std::function< double(int, int) >
JPetRecoImageTools::matrixGetterFactory(const Matrix2D &emissionMatrix,
                                        bool isTransposed)
{
  if (!isTransposed)
  {
    return [&emissionMatrix](int i, int j) {
      if (i >= 0 && i < (int)emissionMatrix[0].size() && j >= 0 &&
          j < (int)emissionMatrix.size())
      {
        return emissionMatrix[i][j];
      }
      else
      {
        return 0;
      }
    };
  }
  else
  {
    return [&emissionMatrix](int i, int j) {
      if (i >= 0 && i < (int)emissionMatrix.size() && j >= 0 &&
          j < (int)emissionMatrix[0].size())
      {
        return emissionMatrix[j][i];
      }
      else
      {
        return 0;
      }
    };
  }
}

JPetRecoImageTools::Matrix2DProj
JPetRecoImageTools::createSinogramWithSingleInterpolation(
    Matrix2D &emissionMatrix, int nViews, int nScans, double angleBeg,
    double angleEnd, InterpolationFunc interpolationFunction,
    RescaleFunc rescaleFunc, int rescaleMinCutoff, int rescaleFactor)
{
  assert(emissionMatrix.size() > 0);
  assert(emissionMatrix.size() == emissionMatrix[0].size());
  assert(nViews > 0);
  assert(nScans > 0);
  assert(angleBeg < angleEnd);
  assert(rescaleMinCutoff < rescaleFactor);

  Matrix2DProj proj(nScans, std::vector< double >(nViews));

  float stepsize = (angleEnd - angleBeg) / nViews;
  assert(stepsize > 0);

  int viewIndex = 0;
  for (auto phi = angleBeg; phi < angleEnd; phi = phi + stepsize, viewIndex++)
  {
    for (auto scanNumber = 0; scanNumber < nScans; scanNumber++)
    {
      proj[nScans - 1 - scanNumber][viewIndex] =
          JPetRecoImageTools::calculateProjection(
              emissionMatrix, phi, scanNumber, nScans, interpolationFunction);
    }
  }
  rescaleFunc(proj, rescaleMinCutoff, rescaleFactor);
  return proj;
}

double JPetRecoImageTools::calculateProjection(
    const Matrix2D &emissionMatrix, double angle, int scanNumber, int nScans,
    InterpolationFunc &interpolationFunction)
{
  int N = scanNumber - std::floor(nScans / 2);
  const int kInputMatrixSize = emissionMatrix.size();
  // if no. nScans is greater than the image width, then scale will be <1
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
  /// The line over which we integrate is perpendicular to any line with the
  /// slope = tg(angle), so it is always  -1/tg(angle).
  /// If the angle is between (45 to 125)
  /// we use  y = a * x + b, and we iterate over rows of the matrix (x).
  /// If the angle is between [0 to 45 ] or [125 to 180]
  /// we use x = a* y +b, and we iterate over columns of the matrix (y)
  bool angleRange45To125 = std::abs(sin) > kSin45or125deg;
  double divided = 1.;
  std::function< double(int, int) > matrixGet;

  if (angleRange45To125)
  {
    assert(sin);
    a = -cos / sin;
    b = (N - cos - sin) / sin;
    b *= scale;
    matrixGet = matrixGetterFactory(
        emissionMatrix, false); // The matrix  elements will be taken as (x,y).
    divided = std::abs(sin);
  }
  else
  {
    assert(cos);
    a = -sin / cos;
    b = (N - cos - sin) / cos;
    b *= scale;
    matrixGet = matrixGetterFactory(
        emissionMatrix,
        true); // The matrix  elements will be taken as (y, x) - transposed.
    divided = std::abs(cos);
  }
  const int kMatrixCenter = std::floor(emissionMatrix.size() / 2);
  double value = 0.;
  for (auto i = -kMatrixCenter; i < kMatrixCenter; i++)
  {
    value += interpolationFunction(i + kMatrixCenter, a * i + b + kMatrixCenter,
                                   matrixGet);
  }
  value /= divided;
  return value;
}

JPetRecoImageTools::Matrix2DProj
JPetRecoImageTools::createSinogramWithDoubleInterpolation(
    Matrix2D &emissionMatrix, int nAngles, RescaleFunc rescaleFunc,
    int rescaleMinCutoff, int rescaleFactor)
{
  assert(emissionMatrix.size() > 0);
  assert(emissionMatrix.size() == emissionMatrix[0].size());
  assert(nAngles > 0);
  assert(rescaleMinCutoff < rescaleFactor);
  int imageSize = emissionMatrix[0].size();
  double center = (double)(imageSize - 1) / 2.0;
  double center2 = center * center;
  double angleStep = M_PI / nAngles;

  Matrix2DProj proj(imageSize, std::vector< double >(nAngles));
  std::function< double(int, int) > matrixGet;
  matrixGet = matrixGetterFactory(
      emissionMatrix, false); // The matrix  elements will be taken as (x,y).
  for (int angle = 0; angle < nAngles; angle++)
  {
    double cos = std::cos((double)angle * angleStep);
    double sin = std::sin((double)angle * angleStep);
    for (int scanNumber = 0; scanNumber < imageSize - 1; scanNumber++)
    {
      proj[scanNumber][angle] = calculateProjection2(
          scanNumber, cos, sin, imageSize, center, center2, matrixGet);
    }
  }
  rescaleFunc(proj, rescaleMinCutoff, rescaleFactor);
  return proj;
}

double JPetRecoImageTools::calculateProjection2(
    int step, double cos, double sin, int imageSize, double center,
    double center2, std::function< double(int, int) > matrixGet)
{
  double stepMinusCenter = step - center;
  double xtmp = center + stepMinusCenter * cos;
  double ytmp = center - stepMinusCenter * sin;
  int nmin =
      step == 0 || step == imageSize - 1
          ? 0
          : std::floor(center - std::sqrt((center2 - (stepMinusCenter *
                                                      stepMinusCenter))));
  double p = 0.0;
  for (int n = nmin; n < imageSize - nmin; n++)
  {
    double nMinusCenter = (double)n - center;
    int x = std::floor((xtmp - nMinusCenter * sin) + 0.5);
    int y = std::floor((ytmp - nMinusCenter * cos) + 0.5);
    p += matrixGet(y, x); // y - height, x - widht
  }
  return p;
}

void JPetRecoImageTools::rescale(Matrix2DProj &matrix, double minCutoff,
                                 double rescaleFactor)
{

  double datamax = matrix[0][0];
  double datamin = matrix[0][0];
  for (unsigned int k = 0; k < matrix.size(); k++)
  {
    for (unsigned int j = 0; j < matrix[k].size(); j++)
    {
      /// Applying min Cutoff
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
  if ((datamax - datamin) == 0.)
  {
    WARNING(
        "Maximum value in the matrix to rescale is 0. No rescaling performed.");
    return;
  }

  for (unsigned int k = 0; k < matrix.size(); k++)
  {
    for (unsigned int j = 0; j < matrix[0].size(); j++)
    {
      matrix[k][j] =
          (matrix[k][j] - datamin) * rescaleFactor / (datamax - datamin);
    }
  }
}

JPetRecoImageTools::Matrix2DProj
JPetRecoImageTools::backProject(Matrix2DProj &sinogram, int nAngles,
                                RescaleFunc rescaleFunc, int rescaleMinCutoff,
                                int rescaleFactor)
{
  int imageSize = sinogram.size();
  double center = (double)(imageSize - 1) / 2.0;
  double center2 = center * center;
  double angleStep = M_PI / (double)nAngles;

  Matrix2DProj reconstructedProjection(imageSize,
                                       std::vector< double >(imageSize));

  for (int angle = 0; angle < nAngles; angle++)
  {
    double cos = std::cos((double)angle * (double)angleStep);
    double sin = std::sin((double)angle * (double)angleStep);

    for (int x = 0; x < imageSize; x++)
    {
      double xMinusCenter = (double)x - center;
      double xMinusCenter2 = xMinusCenter * xMinusCenter;
      double ttemp = xMinusCenter * cos + center;

      for (int y = 0; y < imageSize; y++)
      {
        double yMinusCenter = (double)y - center;
        double yMinusCenter2 = yMinusCenter * yMinusCenter;
        if (yMinusCenter2 + xMinusCenter2 < center2)
        {
          double t = ttemp - yMinusCenter * sin;
          int n = std::floor(t + 0.5F);
          reconstructedProjection[y][x] += sinogram[n][angle];
        }
      }
    }
  }

  for (int x = 0; x < imageSize; x++)
  {
    for (int y = 0; y < imageSize; y++)
    {
      reconstructedProjection[y][x] *= angleStep;
    }
  }
  rescaleFunc(reconstructedProjection, rescaleMinCutoff, rescaleFactor);
  return reconstructedProjection;
}

JPetRecoImageTools::Matrix2DProj JPetRecoImageTools::FilterSinogram(
    JPetRecoImageTools::FourierTransformFunction &ftf,
    JPetFilterInterface &filterFunction,
    JPetRecoImageTools::Matrix2DProj &sinogram)
{
  return ftf(sinogram, filterFunction);
}

// see http://www.fftw.org/doc/One_002dDimensional-DFTs-of-Real-Data.html
// http://www.fftw.org/fftw3.pdf
JPetRecoImageTools::Matrix2DProj
JPetRecoImageTools::doFFTW(Matrix2DProj &sinogram, JPetFilterInterface &filter)
{
  assert(sinogram.size() > 1);
  JPetRecoImageTools::Matrix2DProj result(
      sinogram.size(), std::vector< double >(sinogram[0].size()));
  int nAngles = sinogram[0].size();
  int nScanSize = sinogram.size();
  int inFTLength = std::floor(((nAngles / 2.)) + 1);
  int outputSize = nScanSize * inFTLength;
  int size = nScanSize * nAngles;
  double *in;
  in = (double *)malloc(size * sizeof(double));
  double *outDouble;
  outDouble = (double *)malloc(size * sizeof(double));
  fftw_complex *out;
  out = (fftw_complex *)fftw_malloc(outputSize * sizeof(fftw_complex));
  fftw_plan plan, invPlan;
  plan = fftw_plan_dft_r2c_2d(nScanSize, nAngles, in, out, FFTW_MEASURE);
  invPlan =
      fftw_plan_dft_c2r_2d(nScanSize, nAngles, out, outDouble, FFTW_MEASURE);
  for (int y = 0; y < nScanSize; y++)
  {
    for (int x = 0; x < nAngles; x++)
    {
      in[x + y * nAngles] = sinogram[y][x];
    }
  }
  fftw_execute(plan);

  // max radius
  double maxR = std::sqrt((inFTLength / 2. * inFTLength / 2.) +
                          (nScanSize / 2. * nScanSize / 2.));

  for (int x = 0; x < inFTLength; x++)
  {
    double xN = ((double)x - ((double)inFTLength / 2.));
    for (int y = 0; y < nScanSize; y++)
    {
      // go by columns
      uint gid = y * inFTLength + x;
      // shifting coordinates
      double yN = ((double)y - ((double)nScanSize / 2.));

      // current radius normalized to [0 .. 1]
      double r = std::sqrt((xN * xN + yN * yN)) / maxR;
      double filterValue = std::abs(filter(1 - r));
      out[gid][0] *= filterValue;
      out[gid][1] *= filterValue;
    }
  }
  fftw_execute(invPlan);

  for (int y = 0; y < nScanSize; y++)
  {
    for (int x = 0; x < nAngles; x++)
    {
      result[y][x] = outDouble[x + y * nAngles] / size;
    }
  }

  fftw_free(out);
  fftw_destroy_plan(plan);
  fftw_destroy_plan(invPlan);
  fftw_cleanup();
  return result;
}

JPetRecoImageTools::Matrix2DProj
JPetRecoImageTools::doFFTSLOW(Matrix2DProj &sinogram,
                              JPetFilterInterface &filter)
{
  int nAngles = sinogram[0].size();
  int nScanSize = sinogram.size();
  int pow = std::round(std::log(nScanSize) / std::log(2.0));
  int padlen = std::round(std::pow(2.0, pow + 1));
  JPetRecoImageTools::Matrix2DProj result(nScanSize,
                                          std::vector< double >(nAngles));
  std::vector< double > Re(padlen);
  std::vector< double > Im(padlen);
  for (int x = 0; x < nAngles; x++)
  {
    for (int y = 0; y < nScanSize; y++)
    {
      Re[y] = sinogram[y][x];
      Im[y] = 0.;
    }
    for (int y = nScanSize; y < padlen; y++)
    {
      Re[y] = 0.;
      Im[y] = 0.;
    }
    doFFTSLOWT(Re, Im, padlen, 0);
    for (int y = 0; y < (padlen / 2); y++)
    {
      double highest = padlen / 2; // highest value is on middle of 1D column
      double r = y / highest;      // distance from highest value
      double filterValue = std::abs(filter(r));

      Re[y] *= filterValue;
      Im[y] *= filterValue;
      Re[padlen - y] *= filterValue;
      Im[padlen - y] *= filterValue;
    }

    Re[padlen / 2] *= std::abs(filter(1));
    Im[padlen / 2] *= std::abs(filter(1));

    doFFTSLOWI(Re, Im, padlen, 0);
    for (int y = 0; y < nScanSize; y++)
    {
      result[y][x] = Re[y];
    }
  }
  return result;
}

void JPetRecoImageTools::doFFTSLOWT(std::vector< double > &Re,
                                    std::vector< double > &Im, int size,
                                    int shift)
{

  int m = (int)(std::log((double)size) / std::log(2.0));
  int n = 1 << m;
  std::vector< double > Imarg(n);
  std::vector< double > Rearg(n);

  int i;
  for (i = 0; i < n; ++i)
  {
    double arg = 2 * M_PI * (double)((float)i) / (double)((float)n);
    Rearg[i] = std::cos(arg);
    Imarg[i] = -std::sin(arg);
  }

  int j = shift;

  double Retmp;
  double Imtmp;
  for (i = shift; i < shift + n - 1; ++i)
  {
    if (i < j)
    {
      Retmp = Re[i];
      Imtmp = Im[i];
      Re[i] = Re[j];
      Im[i] = Im[j];
      Re[j] = Retmp;
      Im[j] = Imtmp;
    }

    int k;
    for (k = n >> 1; k + shift <= j; k /= 2)
    {
      j -= k;
    }

    j += k;
  }

  int stepsize = 1;

  for (int shifter = m - 1; stepsize < n; --shifter)
  {
    for (j = shift; j < shift + n; j += stepsize << 1)
    {
      for (i = 0; i < stepsize; ++i)
      {
        int i_j = i + j;
        int i_j_s = i_j + stepsize;
        if (i > 0)
        {
          Retmp =
              Rearg[i << shifter] * Re[i_j_s] - Imarg[i << shifter] * Im[i_j_s];
          Im[i_j_s] =
              Rearg[i << shifter] * Im[i_j_s] + Imarg[i << shifter] * Re[i_j_s];
          Re[i_j_s] = Retmp;
        }

        Retmp = Re[i_j] - Re[i_j_s];
        Imtmp = Im[i_j] - Im[i_j_s];
        Re[i_j] += Re[i_j_s];
        Im[i_j] += Im[i_j_s];
        Re[i_j_s] = Retmp;
        Im[i_j_s] = Imtmp;
      }
    }

    stepsize <<= 1;
  }
}

void JPetRecoImageTools::doFFTSLOWI(std::vector< double > &Re,
                                    std::vector< double > &Im, int size,
                                    int shift)
{

  for (int i = shift; i < shift + size; ++i)
  {
    Im[i] = -Im[i];
  }

  doFFTSLOWT(Re, Im, size, shift);

  for (int i1 = shift; i1 < shift + size; ++i1)
  {
    Re[i1] /= (double)size;
    Im[i1] = -Im[i1] / (double)size;
  }
}
