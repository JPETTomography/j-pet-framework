
#ifndef _JPetRecoImageTools_H_
#define _JPetRecoImageTools_H_

#include <boost/numeric/ublas/matrix.hpp>
#include <vector>
#include <utility>

class JPetRecoImageTools {
public:
  static std::vector<std::vector<double>> sinogram(boost::numeric::ublas::matrix<int> emissionMatrix, int views, int scans, 
            bool fast = false, float ang1 = 0, float ang2 = 180, bool scaleResult = false, int min = 0, int max = 255);
private:
  JPetRecoImageTools();
  ~JPetRecoImageTools();

  static void scale(std::vector<std::vector<double>>& v, int min, int max);
};


#endif
