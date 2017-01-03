
#ifndef _JPetRecoImageTools_H_
#define _JPetRecoImageTools_H_

#include <vector>
#include <utility>
#include <functional>

class JPetRecoImageTools
{
public:
  static double nearestNeighbour(std::vector<std::vector<int>> &emissionMatrix,
                                 double a, double b, int center, int x, int y, bool sang);
  static double linear(std::vector<std::vector<int>> &emissionMatrix,
                       double a, double b, int center, int x, int y, bool sang);

  static std::vector<std::vector<double>> sinogram(std::vector<std::vector<int>> &emissionMatrix,
                                                   int views, int scans,
                                                   std::function<double(std::vector<std::vector<int>> &,
                                                   double, double, int, int, int, bool)> interpolationFunction = linear,
                                                   float ang1 = 0, float ang2 = 180, bool scaleResult = false,
                                                   int min = 0, int max = 255);

private:
  JPetRecoImageTools();
  ~JPetRecoImageTools();
  JPetRecoImageTools(const JPetRecoImageTools &) = delete;
  JPetRecoImageTools &operator=(const JPetRecoImageTools &) = delete;

  static void scale(std::vector<std::vector<double>> &v, int min, int max);
  static double calculateValue(std::vector<std::vector<int>> &emissionMatrix, bool sang, int N, double cos, double sin,
                               double scale, int center,
                               std::function<double(std::vector<std::vector<int>> &,
                               double, double, int, int, int, bool)> &interpolationFunction, double a, double aa);
};

#endif
