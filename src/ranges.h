//
// Created by M.Kojro on 1/6/2022.
//

#ifndef FOURIER_TRANSFORM_SRC_RANGES_H_
#define FOURIER_TRANSFORM_SRC_RANGES_H_

#include <cmath>

/*
 * !! This is not optimised for performance !!
 */

static std::vector<double> linspace(double (*f)(double), double from, double to,
									int samples) {

  std::vector<double> results;

  double divisor = (to - from) / samples;
  for (double x = from; x < to; x += divisor) { results.push_back(f(x)); }

  return results;
}

std::vector<int64_t> range(int64_t from, int64_t to, int64_t step = 1) {
  std::vector<int64_t> result;
  result.reserve((to - from) / step);
  for (int64_t i = from; i < to; i += step) { result.push_back(i); }
  return result;
}

std::vector<std::pair<double, double>> zip(const std::vector<double>& v1,
										   const std::vector<double>& v2) {

  std::vector<std::pair<double, double>> result(v1.size());

  assert(v1.size() == v2.size() && "Sizes need to be equal");

  for (size_t i = 0; i < v1.size(); i++) {
	result[i] = std::make_pair(v1[i], v2[i]);
  }

  return result;
}

template<class T>
std::vector<std::pair<size_t, T>> enumerate(const std::vector<T>& v) {
  std::vector<std::pair<size_t, T>> result(v.size());

  for (size_t i = 0; i < v.size(); i++) { result[i] = std::make_pair(i, v[i]); }

  return result;
}

#endif// FOURIER_TRANSFORM_SRC_RANGES_H_
