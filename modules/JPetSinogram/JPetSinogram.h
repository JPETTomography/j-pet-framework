
#ifndef _JPETSINOGRAM_H_
#define _JPETSINOGRAM_H_

#include <boost/numeric/ublas/matrix.hpp>
#include <vector>
#include <utility>
using namespace boost::numeric::ublas;
class JPetSinogram {
public:
  static std::vector<std::vector<double>> sinogram(matrix<int> emissionMatrix, int views, int scans, 
            bool fast = false, float ang1 = 0, float ang2 = 180, bool scaleResult = false, int min = 0, int max = 255);
private:
  JPetSinogram();
  ~JPetSinogram();
};


#endif
