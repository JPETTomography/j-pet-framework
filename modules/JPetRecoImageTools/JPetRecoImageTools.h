
#ifndef _JPetRecoImageTools_H_
#define _JPetRecoImageTools_H_

#include <vector>
#include <functional>

class JPetRecoImageTools
{
public:
  using Matrix2D = std::vector<std::vector<int>>;
  using Matrix2DProj = std::vector<std::vector<double>>;
  using InterpolationFunc = std::function<double(Matrix2D&, double, double, int, int, int, bool)>;
  static double nearestNeighbour(Matrix2D& emissionMatrix,
                                 double a, double b, int center, int x, int y, bool sang);
  static double linear(Matrix2D& emissionMatrix,
                       double a, double b, int center, int x, int y, bool sang);

  /*! \brief Function returning vector of vectors with value of sinogram
   *  \param emissionMatrix matrix, need to be NxN
   *  \param views number of views on object, degree step is calculated as (ang2 - ang1) / views
   *  \param scans number of scans on object, step is calculated as emissionMatrix[0].size() / scans
   *  \param interpolationFunction function to interpolate values (Optional, default linear)
   *  \param ang1 start angle for projection (Optional, default 0)
   *  \param ang2 end angle for projection (Optional, default 180)
   *  \param scaleResult if set to true, scale result to <min, max> (Optional, default false)
   *  \param min minimum value in returned sinogram (Optional, default 0)
   *  \param max maximum value in returned sinogram (Optional, default 255)
  */
  static Matrix2DProj sinogram(Matrix2D& emissionMatrix,
                               int views, int scans,
                               InterpolationFunc interpolationFunction = linear,
                               float ang1 = 0, float ang2 = 180, bool scaleResult = false,
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

  static double calculateValue(Matrix2D& emissionMatrix, bool sang, int N, double cos, double sin,
                               double scale, int center,
                               InterpolationFunc& interpolationFunction, double a, double aa);
};

#endif
