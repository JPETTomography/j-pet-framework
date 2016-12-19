
#ifndef _JPETSINOGRAM_H_
#define _JPETSINOGRAM_H_

#include <boost/numeric/ublas/matrix.hpp>
#include <vector>
#include <utility>
using namespace boost::numeric::ublas;
class JPetSinogram {
public:
  JPetSinogram();
  ~JPetSinogram();

  typedef std::shared_ptr<double[]> ManagedDouble;
  typedef std::vector<std::vector<double>> resultType;

  long long forwardProjection(float s, float theta, matrix<int> emissionMatrix); //row major orientation, element m[i,j]
  //is mapped as i*n + j element
  resultType sinogram(matrix<int> emissionMatrix, int views, int scans);
private:
  void normalize2DArray(resultType &data, int imax, int jmax, double min, double max);
};


#endif
