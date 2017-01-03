#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetRecoImageToolsTests
#include <boost/test/unit_test.hpp>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>

#include "./JPetRecoImageTools.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(rescale_0)
{
  JPetRecoImageTools::Matrix2DProj matrix = { {3, 0}, {0, 0}};
  double resFact = 5;
  double minCutoff = 0;
  double epsilon = 0.00001;
  JPetRecoImageTools::rescale(matrix, minCutoff, resFact);
  BOOST_REQUIRE_CLOSE(matrix[0][0], 5, epsilon );
  BOOST_REQUIRE_CLOSE(matrix[0][1], 0, epsilon );
  BOOST_REQUIRE_CLOSE(matrix[1][0], 0, epsilon );
  BOOST_REQUIRE_CLOSE(matrix[1][1], 0, epsilon );
}

BOOST_AUTO_TEST_CASE(rescale)
{
  JPetRecoImageTools::Matrix2DProj matrix = { {2, 1}, {1, 1}};
  double resFact = 2;
  double minCutoff = 0;
  double epsilon = 0.00001;
  JPetRecoImageTools::rescale(matrix, minCutoff, resFact);
  BOOST_REQUIRE_CLOSE(matrix[0][0], 2, epsilon );
  BOOST_REQUIRE_CLOSE(matrix[0][1], 0, epsilon );
  BOOST_REQUIRE_CLOSE(matrix[1][0], 0, epsilon );
  BOOST_REQUIRE_CLOSE(matrix[1][1], 0, epsilon );
}

BOOST_AUTO_TEST_CASE(rescale_2)
{
  JPetRecoImageTools::Matrix2DProj matrix = { {5, 2}, {1, 2}};
  double resFact = 2;
  double minCutoff = 0;
  double epsilon = 0.00001;
  JPetRecoImageTools::rescale(matrix, minCutoff, resFact);
  BOOST_REQUIRE_CLOSE(matrix[0][0], 2, epsilon );
  BOOST_REQUIRE_CLOSE(matrix[0][1], 0.5, epsilon );
  BOOST_REQUIRE_CLOSE(matrix[1][0], 0., epsilon );
  BOOST_REQUIRE_CLOSE(matrix[1][1], 0.5, epsilon );
}

BOOST_AUTO_TEST_CASE(rescale_3)
{
  JPetRecoImageTools::Matrix2DProj matrix = { {5, 3}, {1, 2}};
  double resFact = 8;
  double minCutoff = 2; /// -> 5, 3 , 2, 2
  /// after background subtraction 3, 1, 0,0
  double epsilon = 0.00001;
  JPetRecoImageTools::rescale(matrix, minCutoff, resFact);
  BOOST_REQUIRE_CLOSE(matrix[0][0], 8, epsilon );
  BOOST_REQUIRE_CLOSE(matrix[0][1], 1. * 8. / 3., epsilon );
  BOOST_REQUIRE_CLOSE(matrix[1][0], 0 * 8. / 3., epsilon );
  BOOST_REQUIRE_CLOSE(matrix[1][1], 0, epsilon );
}

BOOST_AUTO_TEST_CASE(ONE_POINT_MATRIX_NOT_IN_CENTER)
{
  std::vector<std::vector<int>> m(4, std::vector<int>(4));
  for (unsigned int i = 0; i < 4; i++) {
    for (unsigned int j = 0; j < 4; j++) {
      m[i][j] = 0;
    }
  }
  m[2][2] = 100;
  int views = 2;
  int scans = 4;
  std::vector<std::vector<double>> result = JPetRecoImageTools::sinogram(m, views, scans);
  for (int i = 0; i < views; i++) {
    for (int j = 0; j < scans; j++) {
      if ((i == 0 && j == 2) || (i == 1 && j == 1))
        BOOST_REQUIRE_EQUAL(result[i][j], 100);
      else
        BOOST_REQUIRE_EQUAL(result[i][j], 0);
    }
  }

  std::vector<std::vector<double>> result2 = JPetRecoImageTools::sinogram(m, views, scans, JPetRecoImageTools::nearestNeighbour);
  for (int i = 0; i < views; i++) {
    for (int j = 0; j < scans; j++) {
      if ((i == 0 && j == 2) || (i == 1 && j == 1))
        BOOST_REQUIRE_EQUAL(result2[i][j], 100);
      else
        BOOST_REQUIRE_EQUAL(result2[i][j], 0);
    }
  }
}

//BOOST_AUTO_TEST_CASE(sinogram)
//{

//std::ifstream in;
//in.open("unitTestData/JPetRecoImageToolsTest/phantom.pgm");
//std::string line;
//getline(in, line);
//if (line != "P2")
//{
//}

//unsigned int width;
//unsigned int height;
//in >> width;
//in >> height;
//int val;
//in >> val; // skip max val
//std::vector<std::vector<int>> m(width, std::vector<int>(height));
//for (unsigned int i = 0; i < width; i++)
//{
//for (unsigned int j = 0; j < height; j++)
//{
//in >> val;
//m[i][j] = val;
//}
//}
//int views = 180;
//int scans = 256;
//std::vector<std::vector<double>> result = JPetRecoImageTools::sinogram(m, views, scans, JPetRecoImageTools::linear, 0, 180, true, 0, 255);
//std::ofstream res;
//res.open("unitTestData/JPetRecoImageToolsTest/sinogram.ppm");
//res << "P2" << std::endl;
//res << scans << " " << views << std::endl;
//res << "255" << std::endl;

//for (int i = 0; i < views; i++)
//{
//for (int j = 0; j < scans; j++)
//{
//res << (int)result[i][j] << " ";
//}
//res << std::endl;
//}

//res.close();
//}

BOOST_AUTO_TEST_SUITE_END()
