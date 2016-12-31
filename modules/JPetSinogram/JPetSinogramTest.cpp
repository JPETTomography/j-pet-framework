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

BOOST_AUTO_TEST_CASE(ONE_POINT_MATRIX_IN_CENTER)
{
  matrix<int> m(10, 10);
  for (unsigned int i = 0; i < 10; i++)
  {
    for (unsigned int j = 0; j < 10; j++)
    {
      m(i, j) = 0;
    }
  }

  m(5, 5) = 100;
  int views = 2;
  int scans = 10;
  std::vector<std::vector<double>> result = JPetSinogram::sinogram(m, views, scans);
  for (int i = 0; i < views; i++)
  {
    for (int j = 0; j < scans; j++)
    {
      std::cout << result[i][j] << " ";
      //if(j == 4) 
      //  BOOST_REQUIRE_EQUAL((int)result[i][j], 100);
      //else 
      //  BOOST_REQUIRE_EQUAL((int)result[i][j], 0);
    }
    std::cout << std::endl;
  }
}

BOOST_AUTO_TEST_CASE(ONE_POINT_MATRIX_NOT_IN_CENTER)
{
  matrix<int> m(10, 10);
  for (unsigned int i = 0; i < 10; i++)
  {
    for (unsigned int j = 0; j < 10; j++)
    {
      m(i, j) = 0;
    }
  }

  m(3, 3) = 100;
  int views = 2;
  int scans = 10;
  std::vector<std::vector<double>> result = JPetSinogram::sinogram(m, views, scans);
  for (int i = 0; i < views; i++)
  {
    for (int j = 0; j < scans; j++)
    {
      std::cout << (int)result[i][j] << " "; //barray[i + j * views] = (byte) projection[i][j];
    }
    std::cout << std::endl;
  }
}

BOOST_AUTO_TEST_CASE(sinogram)
{

  std::ifstream in;
  in.open("unitTestData/JPetSinogramTest/phantom.pgm");
  std::string line;
  getline(in, line);
  if (line != "P2")
  { /*error*/
  }

  unsigned int width;
  unsigned int height;
  in >> width;
  in >> height;
  int val;
  in >> val; // skip max val
  matrix<int> m(width, height);
  for (unsigned int i = 0; i < width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      in >> val;
      m(i, j) = val;
    }
  }
  int views = 180;
  int scans = 256;
  std::vector<std::vector<double>> result = JPetSinogram::sinogram(m, views, scans, false, 0, 180, true, 0, 255); // value, theta, s
  std::ofstream res;
  res.open("image.ppm");
  res << "P2" << std::endl;
  res << scans << " " << views << std::endl;
  res << "255" << std::endl;

  for (int i = 0; i < views; i++)
  {
    for (int j = 0; j < scans; j++)
    {
      res << (int)result[i][j] << " "; //barray[i + j * views] = (byte) projection[i][j];
    }
    res << std::endl;
  }

  for (std::vector<double> p : result)
  {
    for (double r : p)
      res << (int)r << " ";
    res << std::endl;
  }
  res.close();
}

BOOST_AUTO_TEST_SUITE_END()
