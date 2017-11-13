#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetRecoImageToolsTests
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

#include "../../JPetCommonTools/JPetCommonTools.h"
#include "./JPetFilterCosine.h"
#include "./JPetFilterHamming.h"
#include "./JPetFilterNone.h"
#include "./JPetFilterRamLak.h"
#include "./JPetFilterRidgelet.h"
#include "./JPetFilterSheppLogan.h"
#include "./JPetRecoImageTools.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(rescale_0)
{
  JPetRecoImageTools::Matrix2DProj matrix = {{3, 0}, {0, 0}};
  double resFact = 5;
  double minCutoff = 0;
  double epsilon = 0.00001;
  JPetRecoImageTools::rescale(matrix, minCutoff, resFact);
  BOOST_REQUIRE_CLOSE(matrix[0][0], 5, epsilon);
  BOOST_REQUIRE_CLOSE(matrix[0][1], 0, epsilon);
  BOOST_REQUIRE_CLOSE(matrix[1][0], 0, epsilon);
  BOOST_REQUIRE_CLOSE(matrix[1][1], 0, epsilon);
}

BOOST_AUTO_TEST_CASE(rescale)
{
  JPetRecoImageTools::Matrix2DProj matrix = {{2, 1}, {1, 1}};
  double resFact = 2;
  double minCutoff = 0;
  double epsilon = 0.00001;
  JPetRecoImageTools::rescale(matrix, minCutoff, resFact);
  BOOST_REQUIRE_CLOSE(matrix[0][0], 2, epsilon);
  BOOST_REQUIRE_CLOSE(matrix[0][1], 0, epsilon);
  BOOST_REQUIRE_CLOSE(matrix[1][0], 0, epsilon);
  BOOST_REQUIRE_CLOSE(matrix[1][1], 0, epsilon);
}

BOOST_AUTO_TEST_CASE(rescale_2)
{
  JPetRecoImageTools::Matrix2DProj matrix = {{5, 2}, {1, 2}};
  double resFact = 2;
  double minCutoff = 0;
  double epsilon = 0.00001;
  JPetRecoImageTools::rescale(matrix, minCutoff, resFact);
  BOOST_REQUIRE_CLOSE(matrix[0][0], 2, epsilon);
  BOOST_REQUIRE_CLOSE(matrix[0][1], 0.5, epsilon);
  BOOST_REQUIRE_CLOSE(matrix[1][0], 0., epsilon);
  BOOST_REQUIRE_CLOSE(matrix[1][1], 0.5, epsilon);
}

BOOST_AUTO_TEST_CASE(rescale_3)
{
  JPetRecoImageTools::Matrix2DProj matrix = {{5, 3}, {1, 2}};
  double resFact = 8;
  double minCutoff = 2; /// -> 5, 3 , 2, 2
  /// after background subtraction 3, 1, 0,0
  double epsilon = 0.00001;
  JPetRecoImageTools::rescale(matrix, minCutoff, resFact);
  BOOST_REQUIRE_CLOSE(matrix[0][0], 8, epsilon);
  BOOST_REQUIRE_CLOSE(matrix[0][1], 1. * 8. / 3., epsilon);
  BOOST_REQUIRE_CLOSE(matrix[1][0], 0 * 8. / 3., epsilon);
  BOOST_REQUIRE_CLOSE(matrix[1][1], 0, epsilon);
}
BOOST_AUTO_TEST_CASE(matrixGetterFactoryTest)
{
  double epsilon = 0.00001;
  JPetRecoImageTools::Matrix2D matrix = {{1, 2}, {3, 4}};
  auto getter = JPetRecoImageTools::matrixGetterFactory(matrix, false);
  BOOST_REQUIRE_CLOSE(getter(0, 0), 1, epsilon);
  BOOST_REQUIRE_CLOSE(getter(0, 1), 2, epsilon);
  BOOST_REQUIRE_CLOSE(getter(1, 0), 3, epsilon);
  BOOST_REQUIRE_CLOSE(getter(1, 1), 4, epsilon);
  BOOST_REQUIRE_CLOSE(getter(3, 3), 0,
                      epsilon); /// out of range should return 0
  auto getterT =
      JPetRecoImageTools::matrixGetterFactory(matrix, true); /// transposed
  BOOST_REQUIRE_CLOSE(getterT(0, 0), 1, epsilon);
  BOOST_REQUIRE_CLOSE(getterT(0, 1), 3, epsilon);
  BOOST_REQUIRE_CLOSE(getterT(1, 0), 2, epsilon);
  BOOST_REQUIRE_CLOSE(getterT(1, 1), 4, epsilon);
  BOOST_REQUIRE_CLOSE(getterT(3, 3), 0,
                      epsilon); /// out of range should return 0
}

BOOST_AUTO_TEST_CASE(nearestNeighbour)
{
  double epsilon = 0.00001;
  JPetRecoImageTools::Matrix2D matrix = {{1, 2}, {3, 4}};
  auto getter = JPetRecoImageTools::matrixGetterFactory(matrix, false);
  /// first argument is i second j  (i,j)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(0, 0, getter), 1,
                      epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(1, 0, getter), 3,
                      epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(0, 0.6, getter), 2,
                      epsilon); // (0,1)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(0, 0.4, getter), 1,
                      epsilon); // (0,0)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(1, 0.4, getter), 3,
                      epsilon); // (0,0)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(1, 0.8, getter), 4,
                      epsilon); // (0,0)
  auto getterT =
      JPetRecoImageTools::matrixGetterFactory(matrix, true); /// transposed
  /// first argument is j second i  (j,i)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(0, 0, getterT), 1,
                      epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(1, 0, getterT), 2,
                      epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(0, 0.6, getterT), 3,
                      epsilon); // (1,0)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(0, 0.4, getterT), 1,
                      epsilon); // (0,0)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(1, 0.4, getterT), 2,
                      epsilon); // (0,1)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::nearestNeighbour(1, 0.8, getterT), 4,
                      epsilon); // (1,1)
}

BOOST_AUTO_TEST_CASE(linear)
{
  double epsilon = 0.00001;
  JPetRecoImageTools::Matrix2D matrix = {{1, 2}, {3, 4}};
  auto getter = JPetRecoImageTools::matrixGetterFactory(matrix, false);
  /// first argument is i second j  (i,j)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(0, 0, getter), 1, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(0, 1, getter), 2, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(0, 0.9, getter), 1.9, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(1, 0, getter), 3, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(0, 0.4, getter), 1.4,
                      epsilon); // 1 * 0.6 + 2 * 0.4
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(1, 0.4, getter), 3.4,
                      epsilon); //  3* 0.6 + 4 * 0.4
  auto getterT =
      JPetRecoImageTools::matrixGetterFactory(matrix, true); /// transposed
  /// first argument is j second i  (j,i)
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(0, 0, getterT), 1, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(1, 0, getterT), 2, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::linear(0, 0.6, getterT), 2.2,
                      epsilon); // 1*0.4 +  3  *0.6
}
/*
BOOST_AUTO_TEST_CASE(calculateProjection)
{
  double epsilon = 0.00001;
  JPetRecoImageTools::Matrix2D matrix = {{4}};
  //static double calculateProjection(const Matrix2D& emissionMatrix,
  //double phi,
  //int scanNumber,
  //int nScans,
  //InterpolationFunc& interpolationFunction
  //);
  /// first argument is i second j  (i,j)
  JPetRecoImageTools::InterpolationFunc func =
JPetRecoImageTools::nearestNeighbour;
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,0,0,1,
func), 4, epsilon);
}

BOOST_AUTO_TEST_CASE(calculateProjection2)
{
double epsilon = 0.00001;
JPetRecoImageTools::Matrix2D matrix = {{1, 2}, {3, 4}};
/// 1 2
/// 3 4
/// angle = 0
/// nScans = 2
JPetRecoImageTools::InterpolationFunc func =
JPetRecoImageTools::nearestNeighbour;
const int kNScans = 2;
auto angle = 0.0;
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,angle,0,kNScans,
func), 6, epsilon); // 2 + 4
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,angle,1,kNScans,
func), 4, epsilon); // 1 + 3
//BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,45,0,kNScans,
func), 5, epsilon); // 3 + 2
//BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,45,1,kNScans,
func), 4, epsilon); // 4
//BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,45,-1,kNScans,
func), 1, epsilon); // 1
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,90,0,kNScans,
func), 7, epsilon); // 3 + 4
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,90,1,kNScans,
func), 3, epsilon); // 1 + 2
//BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,125,0,kNScans,
func), 5, epsilon); // 1 + 4
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,180,0,kNScans,
func), 6, epsilon); // 2 + 4
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,180,1,kNScans,
func), 4, epsilon); // 1 + 3
}

BOOST_AUTO_TEST_CASE(calculateProjection3)
{
double epsilon = 0.00001;
JPetRecoImageTools::Matrix2D matrix = {{1, 2, 3}, {4, 5, 6}, {7,8,9}};
/// 1 2 3
/// 4 5 6
/// 7 8 9
/// angle = 0
/// nScans = 3
JPetRecoImageTools::InterpolationFunc func =
JPetRecoImageTools::nearestNeighbour;
const int kNScans = 3;
auto angle = 0.0;
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,angle,0,kNScans,
func), 12, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,angle,1,kNScans,
func), 15, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,angle,2,kNScans,
func), 18, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,45,0,kNScans,
func), 15, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,90,0,kNScans,
func), 6, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,90,1,kNScans,
func), 15, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,90,2,kNScans,
func), 24, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,125,0,kNScans,
func), 15, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,180,0,kNScans,
func), 12, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,180,1,kNScans,
func), 15, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,180,2,kNScans,
func), 18, epsilon);
}

BOOST_AUTO_TEST_CASE(calculateProjection4)
{
double epsilon = 0.00001;
JPetRecoImageTools::Matrix2D matrix = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11,
12}, {13, 14, 15, 16}};
/// 1  2  3  4
/// 5  6  7  8
/// 9  10 11 12
/// 13 14 15 16
/// angle = 0
/// nScans = 4
JPetRecoImageTools::InterpolationFunc func =
JPetRecoImageTools::nearestNeighbour;
const int kNScans = 4;
auto angle = 0.0;
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,angle,0,kNScans,
func), 28, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,angle,1,kNScans,
func), 32, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,angle,2,kNScans,
func), 36, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,angle,3,kNScans,
func), 40, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,45,0,kNScans,
func), 34, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,90,0,kNScans,
func), 10, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,90,1,kNScans,
func), 26, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,90,2,kNScans,
func), 42, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,90,3,kNScans,
func), 58, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,125,0,kNScans,
func), 34, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,180,0,kNScans,
func), 28, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,180,1,kNScans,
func), 32, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,180,2,kNScans,
func), 36, epsilon);
BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection(matrix,180,3,kNScans,
func), 40, epsilon);
}

BOOST_AUTO_TEST_CASE(sinogram1)
{
double epsilon = 0.00001;
JPetRecoImageTools::Matrix2D matrix = {{1, 2, 3}, {4, 5, 6}, {7,8,9}};
/// 1 2 3
/// 4 5 6
/// 7 8 9
JPetRecoImageTools::InterpolationFunc func =
JPetRecoImageTools::nearestNeighbour;
JPetRecoImageTools::RescaleFunc func2= JPetRecoImageTools::nonRescale;
const int kNScans = 3;
const int kNViews = 2;
auto results = JPetRecoImageTools::sinogram(matrix,kNViews,kNScans, 0 , 180,
func, func2);
for (auto i: results)
for (auto j: i)
std::cout <<j <<std::endl;
}

//BOOST_AUTO_TEST_CASE(sinogram2)
//{
//double epsilon = 0.00001;
//JPetRecoImageTools::Matrix2D matrix = {{0, 0, 0}, {0, 10, 0}, {0,0,0}};
//JPetRecoImageTools::InterpolationFunc func =
JPetRecoImageTools::nearestNeighbour;
//JPetRecoImageTools::RescaleFunc func2= JPetRecoImageTools::nonRescale;
//const int kNScans = 3;
//const int kNViews = 4;
//auto results = JPetRecoImageTools::sinogram(matrix,kNViews,kNScans, 0 , 180,
func, func2);
//for (auto i: results)
//for (auto j: i)
//std::cout <<j <<std::endl;
//}
*/
BOOST_AUTO_TEST_CASE(projection1)
{
  double epsilon = 0.00001;
  JPetRecoImageTools::Matrix2D matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  /// 1 2 3
  /// 4 5 6
  /// 7 8 9

  int imageSize = matrix.size();
  double center = (float)(imageSize - 1) / 2.0;
  double length = center * center;
  std::function< double(int, int) > matrixGet;
  matrixGet = JPetRecoImageTools::matrixGetterFactory(
      matrix, false); // The matrix  elements will be taken as (x,y).
  double step = (M_PI / 180);

  double cos = std::cos(step * 0); // 0 degree
  double sin = std::sin(step * 0); // 0 degree
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          0, cos, sin, imageSize, center, length, matrixGet),
                      12, epsilon); // 1 + 4 + 7
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          1, cos, sin, imageSize, center, length, matrixGet),
                      15, epsilon); // 2 + 5 + 8
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          2, cos, sin, imageSize, center, length, matrixGet),
                      18, epsilon); // 3 + 6 + 9

  cos = std::cos(step * 90); // 90 degree
  sin = std::sin(step * 90); // 90 degree

  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          0, cos, sin, imageSize, center, length, matrixGet),
                      24, epsilon); // 9 + 8 + 7
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          1, cos, sin, imageSize, center, length, matrixGet),
                      15, epsilon); // 6 + 5 + 3
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          2, cos, sin, imageSize, center, length, matrixGet),
                      6, epsilon); // 3 + 2 + 1
}

BOOST_AUTO_TEST_CASE(projection2)
{
  double epsilon = 0.00001;
  JPetRecoImageTools::Matrix2D matrix = {{1, 2}, {3, 4}};
  /// 1 2
  /// 3 4

  int imageSize = matrix.size();
  double center = (float)(imageSize - 1) / 2.0;
  double length = center * center;
  std::function< double(int, int) > matrixGet;
  matrixGet = JPetRecoImageTools::matrixGetterFactory(
      matrix, false); // The matrix  elements will be taken as (x,y).
  double step = (M_PI / 180);

  double cos = std::cos(step * 0); // 0 degree
  double sin = std::sin(step * 0); // 0 degree
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          0, cos, sin, imageSize, center, length, matrixGet),
                      4, epsilon); // 1 + 3
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          1, cos, sin, imageSize, center, length, matrixGet),
                      6, epsilon); // 2 + 4

  cos = std::cos(step * 90); // 90 degree
  sin = std::sin(step * 90); // 90 degree

  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          0, cos, sin, imageSize, center, length, matrixGet),
                      7, epsilon); // 3 + 4
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          1, cos, sin, imageSize, center, length, matrixGet),
                      3, epsilon); // 1 + 2
}

BOOST_AUTO_TEST_CASE(projection3)
{
  double epsilon = 0.00001;
  JPetRecoImageTools::Matrix2D matrix = {{1, 2, 3, 4, 5},
                                         {6, 7, 8, 9, 10},
                                         {11, 12, 13, 14, 15},
                                         {16, 17, 18, 19, 20},
                                         {21, 22, 23, 24, 25}};
  /// 1  2  3  4  5
  /// 6  7  8  9  10
  /// 11 12 13 14 15
  /// 16 17 18 19 20
  /// 21 22 23 24 25
  /// angle = 0
  /// nScans = 4
  int imageSize = matrix.size();
  double center = (float)(imageSize - 1) / 2.0;
  double length = center * center;
  std::function< double(int, int) > matrixGet;
  matrixGet = JPetRecoImageTools::matrixGetterFactory(
      matrix, false); // The matrix  elements will be taken as (x,y).
  double step = (M_PI / 180);

  double cos = std::cos(step * 0); // 0 degree
  double sin = std::sin(step * 0); // 0 degree
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          0, cos, sin, imageSize, center, length, matrixGet),
                      55, epsilon); // 21 + 16 + 11 + 6 + 1
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          1, cos, sin, imageSize, center, length, matrixGet),
                      60, epsilon); // 22 + 17 + 12 + 7 + 2
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          2, cos, sin, imageSize, center, length, matrixGet),
                      65, epsilon); // 23 + 18 + 13 + 8 + 3
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          3, cos, sin, imageSize, center, length, matrixGet),
                      70, epsilon); // 24 + 19 + 14 + 9 + 4
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          4, cos, sin, imageSize, center, length, matrixGet),
                      75, epsilon); // 25 + 20 + 15 + 10 + 5

  // cos = std::cos(step * 45); //45 degree
  // sin = std::sin(step * 45); //45 degree
  //
  // BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(0,
  //               cos, sin, imageSize, center, length, matrixGet), 70,
  //               epsilon); // 24 + 19 + 14 + 9 + 4

  cos = std::cos(step * 90); // 90 degree
  sin = std::sin(step * 90); // 90 degree

  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          0, cos, sin, imageSize, center, length, matrixGet),
                      115, epsilon); // 25 + 24 + 23 + 22 + 21
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          1, cos, sin, imageSize, center, length, matrixGet),
                      90, epsilon); // 20 + 19 + 18 + 17 + 16
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          2, cos, sin, imageSize, center, length, matrixGet),
                      65, epsilon); // 15 + 14 + 13 + 12 + 11
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          3, cos, sin, imageSize, center, length, matrixGet),
                      40, epsilon); // 10 + 9 + 8 + 7 + 6
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          4, cos, sin, imageSize, center, length, matrixGet),
                      15, epsilon); // 5 + 4 + 3 + 2 + 1
}

BOOST_AUTO_TEST_CASE(projection4)
{
  double epsilon = 0.00001;
  JPetRecoImageTools::Matrix2D matrix = {
      {1, 10, 100, 1000, 10000, 100000, 1000000},
      {2, 20, 200, 2000, 20000, 200000, 2000000},
      {3, 30, 300, 3000, 30000, 300000, 3000000},
      {4, 40, 400, 4000, 40000, 400000, 4000000},
      {5, 50, 500, 5000, 50000, 500000, 5000000},
      {6, 60, 600, 6000, 60000, 600000, 6000000},
      {7, 70, 700, 7000, 70000, 700000, 7000000}};
  int imageSize = matrix.size();
  double center = (float)(imageSize - 1) / 2.0;
  double length = center * center;
  std::function< double(int, int) > matrixGet;
  matrixGet = JPetRecoImageTools::matrixGetterFactory(
      matrix, false); // The matrix  elements will be taken as (x,y).
  double step = (M_PI / 180);

  double cos = std::cos(step * 0); // 0 degree
  double sin = std::sin(step * 0); // 0 degree
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          0, cos, sin, imageSize, center, length, matrixGet),
                      28, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          1, cos, sin, imageSize, center, length, matrixGet),
                      280, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          2, cos, sin, imageSize, center, length, matrixGet),
                      2800, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          3, cos, sin, imageSize, center, length, matrixGet),
                      28000, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          4, cos, sin, imageSize, center, length, matrixGet),
                      280000, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          5, cos, sin, imageSize, center, length, matrixGet),
                      2800000, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          6, cos, sin, imageSize, center, length, matrixGet),
                      28000000, epsilon);

  cos = std::cos(step * 90); // 90 degree
  sin = std::sin(step * 90); // 90 degree

  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          0, cos, sin, imageSize, center, length, matrixGet),
                      7777777, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          1, cos, sin, imageSize, center, length, matrixGet),
                      6666666, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          2, cos, sin, imageSize, center, length, matrixGet),
                      5555555, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          3, cos, sin, imageSize, center, length, matrixGet),
                      4444444, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          4, cos, sin, imageSize, center, length, matrixGet),
                      3333333, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          5, cos, sin, imageSize, center, length, matrixGet),
                      2222222, epsilon);
  BOOST_REQUIRE_CLOSE(JPetRecoImageTools::calculateProjection2(
                          6, cos, sin, imageSize, center, length, matrixGet),
                      1111111, epsilon);
}

// This test takes a Shepp-Logan phantom and creates a sinogram.
BOOST_AUTO_TEST_CASE(sinogram)
{
  const auto inFile = "unitTestData/JPetRecoImageToolsTest/phantom.pgm";
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
  std::vector< std::vector< int > > m(width, std::vector< int >(height));
  for (unsigned int i = 0; i < width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      in >> val;
      m[i][j] = val;
    }
  }
  int views = 180;
  int scans = 256;
  std::vector< std::vector< double > > result =
      JPetRecoImageTools::createSinogramWithSingleInterpolation(
          m, views, scans, 0, 180, JPetRecoImageTools::linear,
          JPetRecoImageTools::rescale);
  /// save sinogram
  std::ofstream res(outFile);
  res << "P2" << std::endl;
  res << result[0].size() << " " << result.size() << std::endl;
  res << "255" << std::endl;
  for (unsigned int i = 0; i < result.size(); i++)
  {
    for (unsigned int j = 0; j < result[0].size(); j++)
    {
      res << static_cast< int >(result[i][j]) << " ";
    }
    res << std::endl;
  }
  res.close();
  BOOST_REQUIRE(JPetCommonTools::ifFileExisting(outFile));
}

// This test takes a Shepp-Logan phantom and creates a sinogram.
BOOST_AUTO_TEST_CASE(sinogram2)
{
  const auto inFile = "unitTestData/JPetRecoImageToolsTest/phantom.pgm";
  const auto outFile = "sinogram2.ppm";
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
  std::vector< std::vector< int > > m(width, std::vector< int >(height));
  for (unsigned int i = 0; i < width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      in >> val;
      m[i][j] = val;
    }
  }
  std::vector< std::vector< double > > result =
      JPetRecoImageTools::createSinogramWithDoubleInterpolation(
          m, 180, JPetRecoImageTools::rescale, 0, 255);
  /// save sinogram
  std::ofstream res(outFile);
  res << "P2" << std::endl;
  res << result[0].size() << " " << result.size() << std::endl;
  res << "255" << std::endl;
  for (unsigned int i = 0; i < result.size(); i++)
  {
    for (unsigned int j = 0; j < result[0].size(); j++)
    {
      res << static_cast< int >(result[i][j]) << " ";
    }
    res << std::endl;
  }
  res.close();
  BOOST_REQUIRE(JPetCommonTools::ifFileExisting(outFile));
}

BOOST_AUTO_TEST_CASE(backProject)
{
  const auto inFile = "unitTestData/JPetRecoImageToolsTest/phantom.pgm";
  const auto outFile = "backproject.ppm";
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
  std::vector< std::vector< int > > m(width, std::vector< int >(height));
  for (unsigned int i = 0; i < width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      in >> val;
      m[i][j] = val;
    }
  }
  int views = 180;
  int scans = 256;
  JPetRecoImageTools::Matrix2DProj sinogram =
      JPetRecoImageTools::createSinogramWithSingleInterpolation(
          m, views, scans, 0, 180, JPetRecoImageTools::linear,
          JPetRecoImageTools::rescale);
  JPetRecoImageTools::Matrix2DProj result = JPetRecoImageTools::backProject(
      sinogram, 180, JPetRecoImageTools::rescale, 0, 255);
  std::ofstream res(outFile);
  res << "P2" << std::endl;
  res << result[0].size() << " " << result.size() << std::endl;
  res << "255" << std::endl;
  for (unsigned int i = 0; i < result.size(); i++)
  {
    for (unsigned int j = 0; j < result[0].size(); j++)
    {
      res << static_cast< int >(result[i][j]) << " ";
    }
    res << std::endl;
  }
  res.close();
  BOOST_REQUIRE(JPetCommonTools::ifFileExisting(outFile));
}

BOOST_AUTO_TEST_CASE(backProjectNone)
{
  const auto inFile = "unitTestData/JPetRecoImageToolsTest/phantom.pgm";
  const auto outFile = "backprojectNone.ppm";
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
  std::vector< std::vector< int > > m(width, std::vector< int >(height));
  for (unsigned int i = 0; i < width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      in >> val;
      m[i][j] = val;
    }
  }
  JPetRecoImageTools::Matrix2DProj sinogram =
      JPetRecoImageTools::createSinogramWithDoubleInterpolation(
          m, 180, JPetRecoImageTools::rescale, 0, 255);
  JPetFilterNone noneFilter;
  JPetRecoImageTools::FourierTransformFunction f = JPetRecoImageTools::doFFTW;
  JPetRecoImageTools::Matrix2DProj filteredSinogram =
      JPetRecoImageTools::FilterSinogram(f, noneFilter, sinogram);
  JPetRecoImageTools::Matrix2DProj result = JPetRecoImageTools::backProject(
      filteredSinogram, 180, JPetRecoImageTools::rescale, 0, 255);
  std::ofstream res(outFile);
  res << "P2" << std::endl;
  res << result[0].size() << " " << result.size() << std::endl;
  res << "255" << std::endl;
  for (unsigned int i = 0; i < result.size(); i++)
  {
    for (unsigned int j = 0; j < result[0].size(); j++)
    {
      res << static_cast< int >(result[i][j]) << " ";
    }
    res << std::endl;
  }
  res.close();
  BOOST_REQUIRE(JPetCommonTools::ifFileExisting(outFile));
}

BOOST_AUTO_TEST_CASE(backProjectRamLak)
{
  const auto inFile = "unitTestData/JPetRecoImageToolsTest/phantom.pgm";
  const auto outFile = "backprojectRamLak.ppm";
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
  std::vector< std::vector< int > > m(width, std::vector< int >(height));
  for (unsigned int i = 0; i < width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      in >> val;
      m[i][j] = val;
    }
  }
  JPetRecoImageTools::Matrix2DProj sinogram =
      JPetRecoImageTools::createSinogramWithDoubleInterpolation(
          m, 180, JPetRecoImageTools::rescale, 0, 255);
  JPetFilterRamLak ramlakFilter;
  JPetRecoImageTools::FourierTransformFunction f = JPetRecoImageTools::doFFTW;
  JPetRecoImageTools::Matrix2DProj filteredSinogram =
      JPetRecoImageTools::FilterSinogram(f, ramlakFilter, sinogram);
  JPetRecoImageTools::Matrix2DProj result = JPetRecoImageTools::backProject(
      filteredSinogram, 180, JPetRecoImageTools::rescale, 0, 255);
  std::ofstream res(outFile);
  res << "P2" << std::endl;
  res << result[0].size() << " " << result.size() << std::endl;
  res << "255" << std::endl;
  for (unsigned int i = 0; i < result.size(); i++)
  {
    for (unsigned int j = 0; j < result[0].size(); j++)
    {
      res << static_cast< int >(result[i][j]) << " ";
    }
    res << std::endl;
  }
  res.close();
  BOOST_REQUIRE(JPetCommonTools::ifFileExisting(outFile));
}

BOOST_AUTO_TEST_CASE(backProjectSheppLogan)
{
  const auto inFile = "unitTestData/JPetRecoImageToolsTest/phantom.pgm";
  const auto outFile = "backprojectSheppLogan.ppm";
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
  std::vector< std::vector< int > > m(width, std::vector< int >(height));
  for (unsigned int i = 0; i < width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      in >> val;
      m[i][j] = val;
    }
  }
  JPetRecoImageTools::Matrix2DProj sinogram =
      JPetRecoImageTools::createSinogramWithDoubleInterpolation(
          m, 180, JPetRecoImageTools::rescale, 0, 255);
  JPetFilterSheppLogan shepploganFilter;
  JPetRecoImageTools::FourierTransformFunction f = JPetRecoImageTools::doFFTW;
  JPetRecoImageTools::Matrix2DProj filteredSinogram =
      JPetRecoImageTools::FilterSinogram(f, shepploganFilter, sinogram);
  JPetRecoImageTools::Matrix2DProj result = JPetRecoImageTools::backProject(
      filteredSinogram, 180, JPetRecoImageTools::rescale, 0, 255);
  std::ofstream res(outFile);
  res << "P2" << std::endl;
  res << result[0].size() << " " << result.size() << std::endl;
  res << "255" << std::endl;
  for (unsigned int i = 0; i < result.size(); i++)
  {
    for (unsigned int j = 0; j < result[0].size(); j++)
    {
      res << static_cast< int >(result[i][j]) << " ";
    }
    res << std::endl;
  }
  res.close();
  BOOST_REQUIRE(JPetCommonTools::ifFileExisting(outFile));
}

BOOST_AUTO_TEST_CASE(backProjectCosine)
{
  const auto inFile = "unitTestData/JPetRecoImageToolsTest/phantom.pgm";
  const auto outFile = "backprojectCosine.ppm";
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
  std::vector< std::vector< int > > m(width, std::vector< int >(height));
  for (unsigned int i = 0; i < width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      in >> val;
      m[i][j] = val;
    }
  }
  JPetRecoImageTools::Matrix2DProj sinogram =
      JPetRecoImageTools::createSinogramWithDoubleInterpolation(
          m, 180, JPetRecoImageTools::rescale, 0, 255);
  JPetFilterCosine cosineFilter;
  JPetRecoImageTools::FourierTransformFunction f = JPetRecoImageTools::doFFTW;
  JPetRecoImageTools::Matrix2DProj filteredSinogram =
      JPetRecoImageTools::FilterSinogram(f, cosineFilter, sinogram);
  JPetRecoImageTools::Matrix2DProj result = JPetRecoImageTools::backProject(
      filteredSinogram, 180, JPetRecoImageTools::rescale, 0, 255);
  std::ofstream res(outFile);
  res << "P2" << std::endl;
  res << result[0].size() << " " << result.size() << std::endl;
  res << "255" << std::endl;
  for (unsigned int i = 0; i < result.size(); i++)
  {
    for (unsigned int j = 0; j < result[0].size(); j++)
    {
      res << static_cast< int >(result[i][j]) << " ";
    }
    res << std::endl;
  }
  res.close();
  BOOST_REQUIRE(JPetCommonTools::ifFileExisting(outFile));
}

BOOST_AUTO_TEST_CASE(backProjectHamming)
{
  const auto inFile = "unitTestData/JPetRecoImageToolsTest/phantom.pgm";
  const auto outFile = "backprojectHamming.ppm";
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
  std::vector< std::vector< int > > m(width, std::vector< int >(height));
  for (unsigned int i = 0; i < width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      in >> val;
      m[i][j] = val;
    }
  }
  JPetRecoImageTools::Matrix2DProj sinogram =
      JPetRecoImageTools::createSinogramWithDoubleInterpolation(
          m, 180, JPetRecoImageTools::rescale, 0, 255);
  JPetFilterHamming hammingFilter(0.45);
  JPetRecoImageTools::FourierTransformFunction f = JPetRecoImageTools::doFFTW;
  JPetRecoImageTools::Matrix2DProj filteredSinogram =
      JPetRecoImageTools::FilterSinogram(f, hammingFilter, sinogram);
  JPetRecoImageTools::Matrix2DProj result = JPetRecoImageTools::backProject(
      filteredSinogram, 180, JPetRecoImageTools::rescale, 0, 255);
  std::ofstream res(outFile);
  res << "P2" << std::endl;
  res << result[0].size() << " " << result.size() << std::endl;
  res << "255" << std::endl;
  for (unsigned int i = 0; i < result.size(); i++)
  {
    for (unsigned int j = 0; j < result[0].size(); j++)
    {
      res << static_cast< int >(result[i][j]) << " ";
    }
    res << std::endl;
  }
  res.close();
  BOOST_REQUIRE(JPetCommonTools::ifFileExisting(outFile));
}

BOOST_AUTO_TEST_CASE(backProjectRidgelet)
{
  const auto inFile = "unitTestData/JPetRecoImageToolsTest/phantom.pgm";
  const auto outFile = "backprojectRidgelet.ppm";
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
  std::vector< std::vector< int > > m(width, std::vector< int >(height));
  for (unsigned int i = 0; i < width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      in >> val;
      m[i][j] = val;
    }
  }
  JPetRecoImageTools::Matrix2DProj sinogram =
      JPetRecoImageTools::createSinogramWithDoubleInterpolation(
          m, 180, JPetRecoImageTools::rescale, 0, 255);
  JPetFilterRidgelet ridgeletFilter;
  JPetRecoImageTools::FourierTransformFunction f = JPetRecoImageTools::doFFTW;
  JPetRecoImageTools::Matrix2DProj filteredSinogram =
      JPetRecoImageTools::FilterSinogram(f, ridgeletFilter, sinogram);
  JPetRecoImageTools::Matrix2DProj result = JPetRecoImageTools::backProject(
      filteredSinogram, 180, JPetRecoImageTools::rescale, 0, 255);
  std::ofstream res(outFile);
  res << "P2" << std::endl;
  res << result[0].size() << " " << result.size() << std::endl;
  res << "255" << std::endl;
  for (unsigned int i = 0; i < result.size(); i++)
  {
    for (unsigned int j = 0; j < result[0].size(); j++)
    {
      res << static_cast< int >(result[i][j]) << " ";
    }
    res << std::endl;
  }
  res.close();
  BOOST_REQUIRE(JPetCommonTools::ifFileExisting(outFile));
}

BOOST_AUTO_TEST_CASE(backProjectNoneSlow)
{
  const auto inFile = "unitTestData/JPetRecoImageToolsTest/phantom.pgm";
  const auto outFile = "backprojectNoneSlow.ppm";
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
  std::vector< std::vector< int > > m(width, std::vector< int >(height));
  for (unsigned int i = 0; i < width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      in >> val;
      m[i][j] = val;
    }
  }
  JPetRecoImageTools::Matrix2DProj sinogram =
      JPetRecoImageTools::createSinogramWithDoubleInterpolation(
          m, 180, JPetRecoImageTools::rescale, 0, 255);
  JPetFilterNone noneFilter;
  JPetRecoImageTools::FourierTransformFunction f =
      JPetRecoImageTools::doFFTSLOW;
  JPetRecoImageTools::Matrix2DProj filteredSinogram =
      JPetRecoImageTools::FilterSinogram(f, noneFilter, sinogram);
  JPetRecoImageTools::Matrix2DProj result = JPetRecoImageTools::backProject(
      filteredSinogram, 180, JPetRecoImageTools::rescale, 0, 255);
  std::ofstream res(outFile);
  res << "P2" << std::endl;
  res << result[0].size() << " " << result.size() << std::endl;
  res << "255" << std::endl;
  for (unsigned int i = 0; i < result.size(); i++)
  {
    for (unsigned int j = 0; j < result[0].size(); j++)
    {
      res << static_cast< int >(result[i][j]) << " ";
    }
    res << std::endl;
  }
  res.close();
  BOOST_REQUIRE(JPetCommonTools::ifFileExisting(outFile));
}

BOOST_AUTO_TEST_CASE(backProjectRamLakSlow)
{
  const auto inFile = "unitTestData/JPetRecoImageToolsTest/phantom.pgm";
  const auto outFile = "backprojectRamLakSlow.ppm";
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
  std::vector< std::vector< int > > m(width, std::vector< int >(height));
  for (unsigned int i = 0; i < width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      in >> val;
      m[i][j] = val;
    }
  }
  JPetRecoImageTools::Matrix2DProj sinogram =
      JPetRecoImageTools::createSinogramWithDoubleInterpolation(
          m, 180, JPetRecoImageTools::rescale, 0, 255);
  JPetFilterRamLak ramlak;
  JPetRecoImageTools::FourierTransformFunction f =
      JPetRecoImageTools::doFFTSLOW;
  JPetRecoImageTools::Matrix2DProj filteredSinogram =
      JPetRecoImageTools::FilterSinogram(f, ramlak, sinogram);
  JPetRecoImageTools::Matrix2DProj result = JPetRecoImageTools::backProject(
      filteredSinogram, 180, JPetRecoImageTools::rescale, 0, 255);
  std::ofstream res(outFile);
  res << "P2" << std::endl;
  res << result[0].size() << " " << result.size() << std::endl;
  res << "255" << std::endl;
  for (unsigned int i = 0; i < result.size(); i++)
  {
    for (unsigned int j = 0; j < result[0].size(); j++)
    {
      res << static_cast< int >(result[i][j]) << " ";
    }
    res << std::endl;
  }
  res.close();
  BOOST_REQUIRE(JPetCommonTools::ifFileExisting(outFile));
}

BOOST_AUTO_TEST_CASE(backProjectSheppLoganSlow)
{
  const auto inFile = "unitTestData/JPetRecoImageToolsTest/phantom.pgm";
  const auto outFile = "backprojectSheppLoganSlow.ppm";
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
  std::vector< std::vector< int > > m(width, std::vector< int >(height));
  for (unsigned int i = 0; i < width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      in >> val;
      m[i][j] = val;
    }
  }
  JPetRecoImageTools::Matrix2DProj sinogram =
      JPetRecoImageTools::createSinogramWithDoubleInterpolation(
          m, 180, JPetRecoImageTools::rescale, 0, 255);
  JPetFilterSheppLogan shepplogan;
  JPetRecoImageTools::FourierTransformFunction f =
      JPetRecoImageTools::doFFTSLOW;
  JPetRecoImageTools::Matrix2DProj filteredSinogram =
      JPetRecoImageTools::FilterSinogram(f, shepplogan, sinogram);
  JPetRecoImageTools::Matrix2DProj result = JPetRecoImageTools::backProject(
      filteredSinogram, 180, JPetRecoImageTools::rescale, 0, 255);
  std::ofstream res(outFile);
  res << "P2" << std::endl;
  res << result[0].size() << " " << result.size() << std::endl;
  res << "255" << std::endl;
  for (unsigned int i = 0; i < result.size(); i++)
  {
    for (unsigned int j = 0; j < result[0].size(); j++)
    {
      res << static_cast< int >(result[i][j]) << " ";
    }
    res << std::endl;
  }
  res.close();
  BOOST_REQUIRE(JPetCommonTools::ifFileExisting(outFile));
}

BOOST_AUTO_TEST_CASE(backProjectCosineSlow)
{
  const auto inFile = "unitTestData/JPetRecoImageToolsTest/phantom.pgm";
  const auto outFile = "backprojectCosineSlow.ppm";
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
  std::vector< std::vector< int > > m(width, std::vector< int >(height));
  for (unsigned int i = 0; i < width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      in >> val;
      m[i][j] = val;
    }
  }
  JPetRecoImageTools::Matrix2DProj sinogram =
      JPetRecoImageTools::createSinogramWithDoubleInterpolation(
          m, 180, JPetRecoImageTools::rescale, 0, 255);
  JPetFilterCosine cosine;
  JPetRecoImageTools::FourierTransformFunction f =
      JPetRecoImageTools::doFFTSLOW;
  JPetRecoImageTools::Matrix2DProj filteredSinogram =
      JPetRecoImageTools::FilterSinogram(f, cosine, sinogram);
  JPetRecoImageTools::Matrix2DProj result = JPetRecoImageTools::backProject(
      filteredSinogram, 180, JPetRecoImageTools::rescale, 0, 255);
  std::ofstream res(outFile);
  res << "P2" << std::endl;
  res << result[0].size() << " " << result.size() << std::endl;
  res << "255" << std::endl;
  for (unsigned int i = 0; i < result.size(); i++)
  {
    for (unsigned int j = 0; j < result[0].size(); j++)
    {
      res << static_cast< int >(result[i][j]) << " ";
    }
    res << std::endl;
  }
  res.close();
  BOOST_REQUIRE(JPetCommonTools::ifFileExisting(outFile));
}

BOOST_AUTO_TEST_CASE(backProjectHammingSlow)
{
  const auto inFile = "unitTestData/JPetRecoImageToolsTest/phantom.pgm";
  const auto outFile = "backprojectHammingSlow.ppm";
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
  std::vector< std::vector< int > > m(width, std::vector< int >(height));
  for (unsigned int i = 0; i < width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      in >> val;
      m[i][j] = val;
    }
  }
  JPetRecoImageTools::Matrix2DProj sinogram =
      JPetRecoImageTools::createSinogramWithDoubleInterpolation(
          m, 180, JPetRecoImageTools::rescale, 0, 255);
  JPetFilterHamming hamming;
  JPetRecoImageTools::FourierTransformFunction f =
      JPetRecoImageTools::doFFTSLOW;
  JPetRecoImageTools::Matrix2DProj filteredSinogram =
      JPetRecoImageTools::FilterSinogram(f, hamming, sinogram);
  JPetRecoImageTools::Matrix2DProj result = JPetRecoImageTools::backProject(
      filteredSinogram, 180, JPetRecoImageTools::rescale, 0, 255);
  std::ofstream res(outFile);
  res << "P2" << std::endl;
  res << result[0].size() << " " << result.size() << std::endl;
  res << "255" << std::endl;
  for (unsigned int i = 0; i < result.size(); i++)
  {
    for (unsigned int j = 0; j < result[0].size(); j++)
    {
      res << static_cast< int >(result[i][j]) << " ";
    }
    res << std::endl;
  }
  res.close();
  BOOST_REQUIRE(JPetCommonTools::ifFileExisting(outFile));
}

BOOST_AUTO_TEST_CASE(backProjectRidgeletSlow)
{
  const auto inFile = "unitTestData/JPetRecoImageToolsTest/phantom.pgm";
  const auto outFile = "backprojectRidgeletSlow.ppm";
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
  std::vector< std::vector< int > > m(width, std::vector< int >(height));
  for (unsigned int i = 0; i < width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      in >> val;
      m[i][j] = val;
    }
  }
  JPetRecoImageTools::Matrix2DProj sinogram =
      JPetRecoImageTools::createSinogramWithDoubleInterpolation(
          m, 180, JPetRecoImageTools::rescale, 0, 255);
  JPetFilterRidgelet ridgelet;
  JPetRecoImageTools::FourierTransformFunction f =
      JPetRecoImageTools::doFFTSLOW;
  JPetRecoImageTools::Matrix2DProj filteredSinogram =
      JPetRecoImageTools::FilterSinogram(f, ridgelet, sinogram);
  JPetRecoImageTools::Matrix2DProj result = JPetRecoImageTools::backProject(
      filteredSinogram, 180, JPetRecoImageTools::rescale, 0, 255);
  std::ofstream res(outFile);
  res << "P2" << std::endl;
  res << result[0].size() << " " << result.size() << std::endl;
  res << "255" << std::endl;
  for (unsigned int i = 0; i < result.size(); i++)
  {
    for (unsigned int j = 0; j < result[0].size(); j++)
    {
      res << static_cast< int >(result[i][j]) << " ";
    }
    res << std::endl;
  }
  res.close();
  BOOST_REQUIRE(JPetCommonTools::ifFileExisting(outFile));
}

BOOST_AUTO_TEST_SUITE_END()
