#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetCachedFunctionTest

#include "JPetCachedFunction/JPetCachedFunction.h"
#include "JPetLoggerInclude.h"
#include <boost/test/unit_test.hpp>

using namespace jpet_common_tools;
/// Returns Time-over-threshold for given deposited energy
/// the current parametrization is par1 + par2 * eDep
/// Returned value in ps, and eDep is given in keV.
double getToT1(double eDep, double  par1 = -91958., double par2 = 19341.)
{
  if (eDep < 0. ) return 0.;
  double value = par1 + eDep * par2;
  return value;
}

BOOST_AUTO_TEST_SUITE(JPetCachedFunctionTestSuite)

BOOST_AUTO_TEST_CASE(getTot_params)
{
  JPetCachedFunctionParams params("pol1", { -91958., 19341.});
  JPetCachedFunction1D func(params, Range(100, 0., 100.));
  BOOST_CHECK(func.getParams().fValidFunction);
  BOOST_CHECK_EQUAL(func.getParams().fParams.size(), 2);
  BOOST_CHECK_EQUAL(func.getParams().fParams[0], -91958.);
  BOOST_CHECK_EQUAL(func.getParams().fParams[1], 19341.);
  BOOST_CHECK_EQUAL(func.getValues().size(), 100);
  auto vals = func.getValues();
}

BOOST_AUTO_TEST_CASE(getTot_standardFunc)
{
  JPetCachedFunctionParams params("pol1", { -91958., 19341.});
  JPetCachedFunction1D func(params, Range( 10000, 0., 100.));
  BOOST_CHECK(func.getParams().fValidFunction);
  BOOST_CHECK_CLOSE(func(0.), getToT1(0.), 0.1);
  BOOST_CHECK_CLOSE(func(1.), getToT1(1.), 0.1);
  BOOST_CHECK_CLOSE(func(10.), getToT1(10.), 0.1);
  BOOST_CHECK_CLOSE(func(59.5), getToT1(59.5), 0.1);
  BOOST_CHECK_CLOSE(func(99.9), getToT1(99.9), 0.1);
}

BOOST_AUTO_TEST_CASE(getTot_quadratic)
{
  JPetCachedFunctionParams params("pol2", {1., 1., 1.}); /// 1 + x + x^2
  JPetCachedFunction1D func(params, Range(10000, 0., 100.));
  BOOST_CHECK(func.getParams().fValidFunction);
  BOOST_CHECK_CLOSE(func(0), 1., 0.1);
  BOOST_CHECK_CLOSE(func(1), 3., 0.1);
  BOOST_CHECK_CLOSE(func(2), 7., 0.1);
  BOOST_CHECK_CLOSE(func(3), 13., 0.1);
}

BOOST_AUTO_TEST_CASE(cached_2D)
{
  JPetCachedFunctionParams params("[0] + [1] * x  + [2] * y", {1., 1., 2.}); /// 1 + x + 2 * y
  JPetCachedFunction2D func(params, Range(100, 0., 100.), Range(100, 0., 100.));
  BOOST_CHECK(func.getParams().fValidFunction);
  BOOST_CHECK_CLOSE(func(0., 0.), 1., 0.1);
  BOOST_CHECK_CLOSE(func(1, 1.), 4., 0.1);
  BOOST_CHECK_CLOSE(func(0., 1.), 3., 0.1);
  BOOST_CHECK_CLOSE(func(1., 0.), 2., 0.1);
}

BOOST_AUTO_TEST_CASE(cached_log)
{
  JPetCachedFunctionParams params("[0] + [1] * TMath::Log(x)", {1., -2.}); /// 1 + -2 * log(x)
  JPetCachedFunction1D func(params, Range(10000, 2., 100.));
  BOOST_CHECK(func.getParams().fValidFunction);
  BOOST_CHECK_CLOSE(func(2.), -0.386294, 0.1);
  BOOST_CHECK_CLOSE(func(3.), -1.19696, 0.1);
  BOOST_CHECK_CLOSE(func(99.), -8.19005, 0.1);
}
BOOST_AUTO_TEST_SUITE_END()
