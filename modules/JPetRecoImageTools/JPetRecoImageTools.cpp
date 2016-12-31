#include "./JPetRecoImageTools.h"
#include <vector>
#include <utility>
#include <cmath>
#include <functional>
#include <cassert>
#include <memory>

JPetRecoImageTools::JPetRecoImageTools() { }

JPetRecoImageTools::~JPetRecoImageTools() { }


double JPetRecoImageTools::nearestNeighbour(std::vector<std::vector<int>> & emissionMatrix, double a, double b, int center, int x, int y, bool sang) {
    if(sang) {
        y = (int) std::round(a*x + b);           
        if (y >= -center && y < center )
            return emissionMatrix[x+center][y+center];
        else return 0; 
    } else {
        x = (int) std::round(a*y + b);
        if (x >= -center && x < center )
            return emissionMatrix[x+center][y+center];
        else return 0;
    }
}

double JPetRecoImageTools::linear(std::vector<std::vector<int>> & emissionMatrix, double a, double b, int center, int x, int y, bool sang) {
    if(sang) {
        y = (int) std::round(a*x + b); 
        double weight = std::abs((a*x + b) - std::ceil(a*x + b));
        if (y >= -center && y+1 < center )
            return (1-weight) * emissionMatrix[x+center][y+center]
                    + weight * emissionMatrix[x+center][y+center+1];
        else return 0;
    } else {
        x = (int) std::round(a*y + b);
        double weight = std::abs((a*y + b) - std::ceil(a*y + b));
        if (x >= -center && x+1 < center )
          return (1-weight) * emissionMatrix[x+center][y+center]
                  + weight * emissionMatrix[x+center+1][y+center];
        else return 0;
        
    }
    
}

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

std::vector<std::vector<double>> JPetRecoImageTools::sinogram(std::vector<std::vector<int>>& emissionMatrix, int views, int scans, 
        std::function<double(std::vector<std::vector<int>> &, double, double, int, int, int, bool)> interpolationFunction, 
        float ang1, float ang2, bool scaleResult, int min, int max) {
  assert(emissionMatrix.size() > 0);
  assert(emissionMatrix.size() == emissionMatrix[0].size());
  assert(views > 0);
  assert(scans > 0);
  assert(min < max);
  assert(ang1 < ang2);

  //create vector of size views, initialize it with vector of size scans
  std::vector<std::vector<double>> proj(views, std::vector<double>(scans)); 
  std::unique_ptr<double[]> sintab(new double[views]);
  std::unique_ptr<double[]> costab(new double[views]);
  
  float phi = 0.;
  float stepsize = (ang2 - ang1) / views;

  assert(stepsize > 0); //maybe != 0 ?
  int i = 0;
  for (phi = ang1; phi < ang2; phi = phi + stepsize) {
      sintab[i] = std::sin((double) phi * M_PI / 180 - M_PI/2);
      costab[i] = std::cos((double) phi * M_PI / 180 - M_PI/2);
      i++;
  } i=0;

  int scanNumber=0;
  const int inputMatrixSize = emissionMatrix.size();
  const int center = inputMatrixSize / 2;

  //if no. scans is greater than the image width, then scale will be <1
  double scale = inputMatrixSize*1.42/scans;

  const double sang = std::sqrt(2)/2;
  
  int N=0;
  for (phi=ang1;phi<ang2;phi=phi+stepsize){
      double a = -costab[i]/sintab[i];
      double aa = 1/a;
      for(scanNumber=0;scanNumber<scans;scanNumber++) {
          N = scanNumber - scans/2;
          proj[i][scanNumber] = JPetRecoImageTools::calculateValue(emissionMatrix, std::abs(sintab[i]) > sang, N, costab[i], sintab[i], scale, center, interpolationFunction, a, aa );
      }
      /*if (std::abs(sintab[i]) > sang){
          for (scanNumber=0;scanNumber<scans;scanNumber++){
              N = scanNumber - scans/2;
              double b = (N - costab[i] - sintab[i]) / sintab[i];
              b =  b * scale;
              for (x = -center; x < center; x++){
                  value += interpolationFunction(emissionMatrix, a, b, center, x, y);
              } 
              proj[i][scanNumber] = value/std::abs(sintab[i]); value=0;
          }
      }
      bool nearest = false; // DELETE, JUST FOR TEST
      if (std::abs(sintab[i]) <= sang){
          for (scanNumber=0;scanNumber<scans;scanNumber++){
              N = scanNumber - scans/2;
              double bb = (N - costab[i] - sintab[i]) / costab[i];
              bb = bb * scale;
              for (y = -center; y < center; y++) {
                  value += interpolationFunction(emissionMatrix, aa)
                  if (nearest){ //nearest neighbour interpolation
                      x = (int) std::round(aa*y + bb);
                      if (x >= -center && x < center )
                          value += emissionMatrix(x+center, y+center);
                  } else { //linear interpolation
                      x = (int) std::round(aa*y + bb);
                      weight = std::abs((aa*y + bb) - std::ceil(aa*y + bb));
                      
                      if (x >= -center && x+1 < center )
                          value += (1-weight) * emissionMatrix((x+center), (y+center))
                                  + weight * emissionMatrix((x+center+1), (y+center));
                      
                  }
              } proj[i][scanNumber] = value/std::abs(costab[i]); value=0;
              
          }
          
      }*/ i++;
  }
  i=0;

  if(scaleResult) {
    JPetRecoImageTools::scale(proj, min, max);
  }
  
  return proj;
}

double JPetRecoImageTools::calculateValue(std::vector<std::vector<int>>& emissionMatrix, bool sang, int N, double cos, double sin,
        double scale, int center,
        std::function<double(std::vector<std::vector<int>>&, double, double, int, int, int, bool)>& interpolationFunction, double a, double aa) {
    double b = 0.;
    if(sang)
        b = (N - cos - sin) / sin;
    else 
        b = (N - cos - sin) / cos;
    
    b *= scale;
    double value = 0.;
    int x = 0;
    int y = 0;
    if(sang) {
      for (x = -center; x < center; x++){
        value += interpolationFunction(emissionMatrix, a, b, center, x, y, sang);
      }
      value /= sin;
    } else {
      for (y = -center; y < center; y++){
        value += interpolationFunction(emissionMatrix, aa, b, center, x, y, sang);
      }
      value /= cos;
    }
    return value;
}

void JPetRecoImageTools::scale(std::vector<std::vector<double>>& v, int min, int max) {
    double datamax = v[0][0];
    double datamin = v[0][0];
    for (unsigned int k = 0; k < v.size(); k++ ) {
        for (unsigned int j = 0; j < v[0].size(); j++ ) {
        if(v[k][j] < min) v[k][j] = min;
        if(v[k][j] > datamax) datamax = v[k][j];
        if(v[k][j] < datamin) datamin = v[k][j];
        }
    }

    if(datamax == 0.) // if max value is 0, no need to scale
        return;

    for (unsigned int k = 0; k < v.size(); k++ ) {
        for (unsigned int j = 0; j < v[0].size(); j++ ) {
        v[k][j] = (double) ((v[k][j]-datamin) * max/datamax);
        }
    }
}