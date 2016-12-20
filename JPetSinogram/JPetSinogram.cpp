#include "./JPetSinogram.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <vector>
#include <utility>
#include <cmath> //for sin and cos
using namespace boost::numeric::ublas;

JPetSinogram::JPetSinogram() { }

JPetSinogram::~JPetSinogram() { }

/*! \brief Function returning vector of vectors with value of sinogram(180/views degree step and emissionMatrix.size1()/scans size) scaled to <min,max> 
 *  \param emissionMatrix matrix
 *  \param views number of views on object, degree step is calculated as (ang2 - ang1) / views
 *  \param scans number of scans on object, step is calculated as emissionMatrix.size(1) / scans
 *  \param fast if true use nearest neighbour interpolation instead linear interpolation in calculation (Optional, default false)
 *  \param min minimum value in returned sinogram (Optional, default 0)
 *  \param max maximum value in returned sinogram (Optional, default 255)
 *  \param ang1 start angle for projection (Optional, default 0)
 *  \param ang2 end angle for projection (Optional, defautl 180) 
*/

std::vector<std::vector<double>> JPetSinogram::sinogram(matrix<int> emissionMatrix, int views, int scans, 
                                                      bool fast, int min, int max, float ang1, float ang2) {
  int i = 0;
  std::vector<std::vector<double>> proj(views, std::vector<double>(scans)); //create vector of size views, initialize it with vector of size scans

  int x = 0, y = 0, Xcenter = 0, Ycenter = 0;

  std::unique_ptr<double[]>  sintab(new double[views]);
  std::unique_ptr<double[]>  costab(new double[views]);
  
  int scanNumber=0;
  int inputMatrixSize = emissionMatrix.size1();

  float phi = 0., stepsize = 0.;
  stepsize = (ang2 - ang1) / views;
  for (phi = ang1; phi < ang2; phi = phi + stepsize) {
      sintab[i] = std::sin((double) phi * M_PI / 180 - M_PI/2);
      costab[i] = std::cos((double) phi * M_PI / 180 - M_PI/2);
      i++;
  }
  
  Xcenter = inputMatrixSize / 2;
  Ycenter = inputMatrixSize / 2;
  i=0;
  //if no. scans is greater than the image width, then scale will be <1
  
  double scale = inputMatrixSize*1.42/scans;
  
  int N=0;
  double value = 0.;
  double weight = 0;
  double sang = std::sqrt(2)/2;
  for (phi=ang1;phi<ang2;phi=phi+stepsize){
      double a = -costab[i]/sintab[i] ;
      double aa = 1/a;
      if (std::abs(sintab[i]) > sang){
          for (scanNumber=0;scanNumber<scans;scanNumber++){
              N = scanNumber - scans/2;
              double b = (N - costab[i] - sintab[i]) / sintab[i];
              b =  b * scale;
              
              for (x = -Xcenter; x < Xcenter; x++){
                  if (fast == true){ //nearest neighbour interpolation
                      y = (int) std::round(a*x + b);
                      
                      if (y >= -Xcenter && y < Xcenter )
                          value += emissionMatrix((x+Xcenter),(y+Ycenter));
                      
                  } else {
                      y = (int) std::round(a*x + b); //linear interpolation
                      weight = std::abs((a*x + b) - std::ceil(a*x + b));
                      
                      if (y >= -Xcenter && y+1 < Xcenter )
                          value += (1-weight) * emissionMatrix((x+Xcenter),(y+Ycenter))
                                  + weight * emissionMatrix((x+Xcenter), (y+Ycenter+1));
                      
                  }
              } proj[i][scanNumber] = value/std::abs(sintab[i]); value=0;
              
          }
      }
      if (std::abs(sintab[i]) <= sang){
          for (scanNumber=0;scanNumber<scans;scanNumber++){
              N = scanNumber - scans/2;
              double bb = (N - costab[i] - sintab[i]) / costab[i];
              bb = bb * scale;
              for (y = -Ycenter; y < Ycenter; y++) {
                  if (fast ==true){ //nearest neighbour interpolation
                      x = (int) std::round(aa*y + bb);
                      if (x >= -Xcenter && x < Xcenter )
                          value += emissionMatrix(x+Xcenter, y+Ycenter);
                  } else { //linear interpolation
                      x = (int) std::round(aa*y + bb);
                      weight = std::abs((aa*y + bb) - std::ceil(aa*y + bb));
                      
                      if (x >= -Xcenter && x+1 < Xcenter )
                          value += (1-weight) * emissionMatrix((x+Xcenter), (y+Ycenter))
                                  + weight * emissionMatrix((x+Xcenter+1), (y+Ycenter));
                      
                  }
              } proj[i][scanNumber] = value/std::abs(costab[i]); value=0;
              
          }
          
      } i++;
  }
  i=0;

  double datamax = proj[0][0];
  double datamin = proj[0][0];
  for (unsigned int k = 0; k < proj.size(); k++ ) {
    for (unsigned int j = 0; j < proj[0].size(); j++ ) {
      if(proj[k][j] < min) proj[k][j] = min;
      if(proj[k][j] > datamax) datamax = proj[k][j];
      if(proj[k][j] < datamin) datamin = proj[k][j];
    }
  }
  std::cout << "datamax: " << datamax  << "datamin: " << datamin << std::endl;
  for (unsigned int k = 0; k < proj.size(); k++ ) {
    for (unsigned int j = 0; j < proj[0].size(); j++ ) {
      proj[k][j] = (double) ((proj[k][j]-datamin) * max/datamax);
    }
  }
  
  return proj;
}