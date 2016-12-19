#include "./JPetSinogram.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <vector>
#include <utility>
#include <cmath> //for sin and cos
using namespace boost::numeric::ublas;

JPetSinogram::JPetSinogram() { }

JPetSinogram::~JPetSinogram() { }

long long JPetSinogram::forwardProjection(float s, float theta, matrix<int> emissionMatrix) {
  long long sum = 0;

  if(s == 0)
    return sum; // not implemented yet

  if(theta == 90) {
    for(unsigned int i = 0; i < emissionMatrix.size1(); i++) {
      sum += emissionMatrix(i, s);
    }
  } else {
    //prosta prostopadła Ax + By + C = 0
    //w zmiennych biegunowych: x * cos(theta) + y * sin(theta) - s = 0
    //prostopadła x * (-sin(theta)) + y * cos(theta) + C = 0
    int x = std::floor(std::cos(-theta) * s);
    int y = -std::floor(std::sin(-theta) * s);
    float theta2 = 90 / emissionMatrix.size1();
    std::cout << "x: " << x << " y: " << y << " theta2: " << theta2 << std::endl;
    while(x >= 0 && y >= 0 && x < emissionMatrix.size1() && y < emissionMatrix.size2()) {
      sum += emissionMatrix(x, y);
      s++;
      x = std::floor(std::cos(-theta) * s);
      y = -std::round(std::sin(-theta) * s);
      std::cout << "x: " << x << " y: " << y << std::endl;
      //float cos = std::cos(theta2 - theta);
      //float r = s / cos;
//
      //x = std::round(std::cos(theta2) * r);
      //y = std::round(std::sin(theta2) * r);
      //std::cout << "x: " << x << " y: " << y << " theta2: " << theta2  << " r: " << r \
      //<< " cos " << cos << std::endl;
      //theta2 += 90 / emissionMatrix.size1();
    }
  }

  /*if(theta == 0) {
    for(unsigned int i = 0; i < emissionMatrix.size2(); i++) {
      sum += emissionMatrix(s, i);
    }
  } else if(theta == 90) {
    for(unsigned int i = 0; i < emissionMatrix.size1(); i++) {
      sum += emissionMatrix(i, s);
    }
  } else if(theta == 45) {
    unsigned int j = (emissionMatrix.size2() - 1) - s < 0 ? 0 : (emissionMatrix.size2() - 1) - s;
    unsigned int i = (emissionMatrix.size2() - 1) - s < 0 ? - ((emissionMatrix.size2() - 1 - s)) : 0;// select row, start from upper right corner
    for(; j < emissionMatrix.size2(); j++) { //-1 bcs matrix start from 0
      if(i < emissionMatrix.size1()) {
        sum += emissionMatrix(i, j);
        i++;
      }
      else { } // exception
    }

  }*/
  std::cout << "s: " << s << " theta: " << theta << " sum: " << sum << std::endl;
  return sum;
}

// std::vector<std::tuple<long long, float, int>> JPetSinogram::sinogram(matrix<int> emissionMatrix) {
//   std::vector<std::tuple<long long, float, int>> result; // value, theta, s
//   for(int i = 0; i < emissionMatrix.size1(); i++) {
//     result.push_back(std::tuple<long long, float, int>(forwardProjection(i, 0., emissionMatrix), 0., i));
//     result.push_back(std::tuple<long long, float, int>(forwardProjection(i, 90., emissionMatrix), 90., i));
//     result.push_back(std::tuple<long long, float, int>(forwardProjection(i, 45., emissionMatrix), 45., i));
//   }
//   /*
//   for(int i = 0; i < emissionMatrix.size1() * 2 - 1; i++) {
//     result.push_back(std::tuple<long long, float, int>(forwardProjection(i, 45., emissionMatrix), 45.));
//   }*/
//   return result;
// }
  typedef std::shared_ptr<double[]> ManagedDouble;
  typedef std::vector<std::vector<double>> resultType;

resultType JPetSinogram::sinogram(matrix<int> emissionMatrix, int views, int scans) {
  int i;
  i=0;
  std::vector<std::vector<double>> proj(views, std::vector<double>(scans));
  //resultType proj = resultType(new ManagedDouble[views]);
  //std::shared_ptr<double**> proj(new double*[views]);
  //for(int k = 0; k < views; k++) {
  //  proj[k] = ManagedDouble(new double[scans]);
  //}

  double pos, val, Aleft, Aright;
  int x, y, Xcenter, Ycenter, Ileft, Iright;
  std::unique_ptr<double[]>  sintab(new double[views]);
  std::unique_ptr<double[]>  costab(new double[views]);
  
  int S=0;
  int inputimgsize = emissionMatrix.size1();

  float phi = 0., stepsize = 0.;
  int ang1 = 0, ang2 = 180;
  stepsize = (ang2 - ang1) / views;
  for (phi=ang1;phi<ang2;phi=phi+stepsize){
      sintab[i] = std::sin((double) phi * M_PI / 180 - M_PI/2);
      costab[i] = std::cos((double) phi * M_PI / 180 - M_PI/2);
      i++;
  }
  
  // Project each pixel in the image
  Xcenter = inputimgsize / 2;
  Ycenter = inputimgsize / 2;
  i=0;
  //if no. scans is greater than the image width, then scale will be <1
  
  double scale = inputimgsize*1.42/scans;
  
  int N=0; val = 0;
  double weight = 0;
  double sang = std::sqrt(2)/2;
  double progr=0;
  bool fast = false;
  for (phi=ang1;phi<ang2;phi=phi+stepsize){
      double a = -costab[i]/sintab[i] ;
      double aa = 1/a;
      if (std::abs(sintab[i]) > sang){
          for (S=0;S<scans;S++){
              N = S - scans/2;
              double b = (N - costab[i] - sintab[i]) / sintab[i];
              b =  b * scale;
              
              for (x = -Xcenter; x < Xcenter; x++){
                  if (fast == true){
                      y = (int) std::round(a*x + b);
                      
                      if (y >= -Xcenter && y < Xcenter )
                          val += emissionMatrix((x+Xcenter),(y+Ycenter));
                      
                  } else {
                      y = (int) std::round(a*x + b);
                      weight = std::abs((a*x + b) - std::ceil(a*x + b));
                      
                      if (y >= -Xcenter && y+1 < Xcenter )
                          val += (1-weight) * emissionMatrix((x+Xcenter),(y+Ycenter))
                                  + weight * emissionMatrix((x+Xcenter), (y+Ycenter+1));
                      
                  }
              } proj[i][S] = val/std::abs(sintab[i]); val=0;
              
          }
      }
      if (std::abs(sintab[i]) <= sang){
          for (S=0;S<scans;S++){
              N = S - scans/2;
              double bb = (N - costab[i] - sintab[i]) / costab[i];
              bb = bb * scale;
              //IJ.write("bb="+bb+" ");
              for (y = -Ycenter; y < Ycenter; y++) {
                  if (fast ==true){
                      x = (int) std::round(aa*y + bb);
                      if (x >= -Xcenter && x < Xcenter )
                          val += emissionMatrix(x+Xcenter, y+Ycenter);
                  } else {
                      x = (int) std::round(aa*y + bb);
                      weight = std::abs((aa*y + bb) - std::ceil(aa*y + bb));
                      
                      if (x >= -Xcenter && x+1 < Xcenter )
                          val += (1-weight) * emissionMatrix((x+Xcenter), (y+Ycenter))
                                  + weight * emissionMatrix((x+Xcenter+1), (y+Ycenter));
                      
                  }
              } proj[i][S] = val/std::abs(costab[i]); val=0;
              
          }
          
      } i++;
  }
  i=0;

  int min = 0;
  int max = 255;

  double datamax = proj[0][0];
  double datamin = proj[0][0];
  for (unsigned int k = 0; k < proj.size(); k++ ) {
    for (unsigned int j = 0; j < proj[0].size(); j++ ) {
      if(proj[k][j] < 0) proj[k][j] = 0;
      if(proj[k][j] > datamax) datamax = proj[k][j];
      if(proj[k][j] < datamin) datamin = proj[k][j];
    }
  }
  std::cout << "datamax: " << datamax  << "datamin: " << datamin << std::endl;
  for (unsigned int k = 0; k < proj.size(); k++ ) {
    for (unsigned int j = 0; j < proj[0].size(); j++ ) {
      //std::cout << proj[i][j] << " ";
      double factor = max/datamax;
      //std::cout << "factor: " << factor << " res: " << ((proj[k][j]-datamin) * factor) << " val: " << proj[k][j] <<std::endl;
      
      proj[k][j] = ((proj[k][j]-datamin) * factor);
      //std::cout << proj[i][j] << " " << (((proj[i][j]-datamin) * (max))/datamax) << std::endl;
    }
  }
  
  return proj;
}