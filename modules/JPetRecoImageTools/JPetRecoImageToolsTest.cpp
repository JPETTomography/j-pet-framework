#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetRecoImageToolsTests
#include <boost/test/unit_test.hpp>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>

#include "./JPetRecoImageTools.h"
#include "../../JPetCommonTools/JPetCommonTools.h"

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
BOOST_AUTO_TEST_CASE(matrixGetterFactoryTest)
{
  double epsilon = 0.00001;
  JPetRecoImageTools::Matrix2D matrix = {{1, 2}, {3, 4}};
  auto getter =  JPetRecoImageTools::matrixGetterFactory(matrix, false);
  BOOST_REQUIRE_CLOSE(getter(0, 0), 1, epsilon);
  BOOST_REQUIRE_CLOSE(getter(0, 1), 2, epsilon);
  BOOST_REQUIRE_CLOSE(getter(1, 0), 3, epsilon);
  BOOST_REQUIRE_CLOSE(getter(1, 1), 4, epsilon);
  BOOST_REQUIRE_CLOSE(getter(3, 3), 0, epsilon); /// out of range should return 0
  auto getterT =  JPetRecoImageTools::matrixGetterFactory(matrix, true); /// transposed
  BOOST_REQUIRE_CLOSE(getterT(0, 0), 1, epsilon);
  BOOST_REQUIRE_CLOSE(getterT(0, 1), 3, epsilon);
  BOOST_REQUIRE_CLOSE(getterT(1, 0), 2, epsilon);
  BOOST_REQUIRE_CLOSE(getterT(1, 1), 4, epsilon);
  BOOST_REQUIRE_CLOSE(getterT(3, 3), 0, epsilon); /// out of range should return 0
}

BOOST_AUTO_TEST_CASE(nearestNeighbour)
{
  double epsilon = 0.00001;
  JPetRecoImageTools::Matrix2D matrix = {{1, 2}, {3, 4}};
  auto getter =  JPetRecoImageTools::matrixGetterFactory(matrix, false);
  /// first argument is i second j  (i,j)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(0, 0, getter), 1, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(1, 0, getter), 3, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(0, 0.6, getter), 2, epsilon); // (0,1)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(0, 0.4, getter), 1, epsilon); // (0,0)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(1, 0.4, getter), 3, epsilon); // (0,0)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(1, 0.8, getter), 4, epsilon); // (0,0)
  auto getterT =  JPetRecoImageTools::matrixGetterFactory(matrix, true); /// transposed
  /// first argument is j second i  (j,i)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(0, 0, getterT), 1, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(1, 0, getterT), 2, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(0, 0.6, getterT), 3, epsilon); // (1,0)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(0, 0.4, getterT), 1, epsilon); // (0,0)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(1, 0.4, getterT), 2, epsilon); // (0,1)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(1, 0.8, getterT), 4, epsilon); // (1,1)
}


BOOST_AUTO_TEST_CASE(linear)
{
  double epsilon = 0.00001;
  JPetRecoImageTools::Matrix2D matrix = {{1, 2}, {3, 4}};
  auto getter =  JPetRecoImageTools::matrixGetterFactory(matrix, false);
  /// first argument is i second j  (i,j)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(0, 0, getter), 1, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(0, 1, getter), 2, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(0, 0.9, getter), 1.9, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(1, 0, getter), 3, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(0, 0.4, getter), 1.4, epsilon); // 1 * 0.6 + 2 * 0.4
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(1, 0.4, getter), 3.4, epsilon); //  3* 0.6 + 4 * 0.4
  auto getterT =  JPetRecoImageTools::matrixGetterFactory(matrix, true); /// transposed
  /// first argument is j second i  (j,i)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(0, 0, getterT), 1, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(1, 0, getterT), 2, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(0, 0.6, getterT), 2.2, epsilon); //1*0.4 +  3  *0.6
}

//BOOST_AUTO_TEST_CASE(calculateProjection)
//{
//double epsilon = 0.00001;
//JPetRecoImageTools::Matrix2D matrix = {{4}};
////static double calculateProjection(const Matrix2D& emissionMatrix,
////double phi,
////int scanNumber,
////int nScans,
////InterpolationFunc& interpolationFunction
////);
///// first argument is i second j  (i,j)
//JPetRecoImageTools::InterpolationFunc func = JPetRecoImageTools::nearestNeighbour;
//BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,0,0,1, func), 4, epsilon);
//}

//BOOST_AUTO_TEST_CASE(calculateProjection2)
//{
//double epsilon = 0.00001;
//JPetRecoImageTools::Matrix2D matrix = {{1, 2}, {3, 4}};
////static double calculateProjection(const Matrix2D& emissionMatrix,
////double phi,
////int scanNumber,
////int nScans,
////InterpolationFunc& interpolationFunction
////);
///// first argument is i second j  (i,j)
//JPetRecoImageTools::InterpolationFunc func = JPetRecoImageTools::linear;
//BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,0,0,1, func), 4, epsilon);
//}


//BOOST_AUTO_TEST_CASE(ONE_POINT_MATRIX_NOT_IN_CENTER)
//{
//std::vector<std::vector<int>> m(4, std::vector<int>(4));
//for (unsigned int i = 0; i < 4; i++) {
//for (unsigned int j = 0; j < 4; j++) {
//m[i][j] = 0;
//}
//}
//m[2][2] = 100;
//int views = 2;
//int scans = 4;
//std::vector<std::vector<double>> result = JPetRecoImageTools::sinogram(m, views, scans);
//for (int i = 0; i < views; i++) {
//for (int j = 0; j < scans; j++) {
//if ((i == 0 && j == 2) || (i == 1 && j == 1))
//BOOST_REQUIRE_EQUAL(result[i][j], 100);
//else
//BOOST_REQUIRE_EQUAL(result[i][j], 0);
//}
//}
//}

//BOOST_AUTO_TEST_CASE(ONE_POINT_MATRIX_NOT_IN_CENTER_2)
//{
//std::vector<std::vector<int>> m(4, std::vector<int>(4));
//for (unsigned int i = 0; i < 4; i++) {
//for (unsigned int j = 0; j < 4; j++) {
//m[i][j] = 0;
//}
//}
//m[2][2] = 100;
//int views = 2;
//int scans = 4;
//std::vector<std::vector<double>> result2 = JPetRecoImageTools::sinogram(m, views, scans, 0, 180,  JPetRecoImageTools::nearestNeighbour);
//for (int i = 0; i < views; i++) {
//for (int j = 0; j < scans; j++) {
//if ((i == 0 && j == 2) || (i == 1 && j == 1))
//BOOST_REQUIRE_EQUAL(result2[i][j], 100);
//else
//BOOST_REQUIRE_EQUAL(result2[i][j], 0);
//}
//}
//}

/// This test takes a Shepp-Logan phantom and creates a sinogram.
BOOST_AUTO_TEST_CASE(sinogram)
{
  const auto inFile = "unitTestData/JPetSinogramTest/phantom.pgm";
  const auto outFile = "sinogram.ppm";
  /// read phantom
  std::ifstream in(inFile);
  BOOST_REQUIRE(in);
  std::string line;
  getline(in, line);
  unsigned int width;
  unsigned int height;
  in >> width;
  in >> height;
  int val;
  in >> val; // skip max val
  std::vector<std::vector<int>> m(width, std::vector<int>(height));
  for (unsigned int i = 0; i < width; i++) {
    for (unsigned int j = 0; j < height; j++) {
      in >> val;
      m[i][j] = val;
    }
  }
  int views = 180;
  int scans = 256;
  std::vector<std::vector<double>> result = JPetRecoImageTools::sinogram(m, views, scans, 0, 180, JPetRecoImageTools::linear, JPetRecoImageTools::rescale);
  /// save sinogram
  std::ofstream res(outFile);
  res << "P2" << std::endl;
  res << scans << " " << views << std::endl;
  res << "255" << std::endl;
  for (int i = 0; i < views; i++) {
    for (int j = 0; j < scans; j++) {
      res << static_cast<int>(result[i][j]) << " ";
    }
    res << std::endl;
  }
  res.close();
  BOOST_REQUIRE(JPetCommonTools::ifFileExisting(outFile));
}
BOOST_AUTO_TEST_SUITE_END()
