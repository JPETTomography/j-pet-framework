#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSinogramTest
#include <boost/test/unit_test.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>
using namespace boost::numeric::ublas;

#include "./JPetSinogram.h"


BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( sinogram )
{
  
  std::ifstream in;
  in.open("phantom.pgm");
  std::string line;
  getline(in, line);
  if(line != "P2") { /*error*/ }

  unsigned int width;
  unsigned int height;
  in >> width;
  in >> height;
  std::cout << line << std::endl;
  std::cout << width << " " << height << std::endl;
  int val;
  in >> val; // skip max val
  matrix<int> m (width, height);
  for(unsigned int i = 0; i < width; i++) {
    for(unsigned int j = 0; j < height; j++) {
      in >> val;
      m(i, j) = val;
    }
  }
  //m(30, 30) = 100;
  JPetSinogram sin;
  std::vector<std::vector<double>> result = sin.sinogram(m, 180, 256); // value, theta, s
  std::ofstream res;
  res.open("image.ppm");
  res << "P2" << std::endl;
  res << width << " " << height << std::endl;
  res << "255" << std::endl;

  for (int i = 0; i < 180; i++ ) {
    for (int j = 0; j < 256; j++ ) {
      res << (int)result[i][j] << " "; //barray[i + j * views] = (byte) projection[i][j];
    }
    res << std::endl;
  }

  for(std::vector<double> p : result) {
    for(double r : p)
      res << (int)r << " ";
    res << std::endl;
  }
  res.close();
}

BOOST_AUTO_TEST_SUITE_END()
