//
// Created by M.Kojro on 1/6/2022.
//

#ifndef FOURIER_TRANSFORM_SRC_RANGES_H_
#define FOURIER_TRANSFORM_SRC_RANGES_H_

#include <cmath>

/*
 * !! This is not optimised for performance !!
 */

template<class T>
static std::vector<T> cut(const std::vector<T>& vec, size_t to) {

  std::vector<double> result;
  result.reserve(to);

  for (size_t i = 0; i < to; i++) { result.push_back(vec[i]); }
  return result;
}

static std::vector<double> abs(const std::vector<std::complex<double>>& vec) {
  std::vector<double> result(vec.size());
  for (size_t i = 0; i < vec.size(); i++) { result[i] = abs(vec[i]); }
  return result;
}

static std::vector<double> linspace(double (*f)(double), double from, double to,
									int samples) {

  std::vector<double> results;

  double divisor = (to - from) / samples;
  for (double x = from; x < to; x += divisor) { results.push_back(f(x)); }

  return results;
}

static std::vector<double> linspace(double from, double to, int samples) {
  return linspace([](double x) { return x; }, from, to, samples);
}

template<class T>
std::vector<T> range(int64_t from, int64_t to, int64_t step = 1) {
  std::vector<T> result;
  result.reserve((to - from) / step);
  for (T i = from; i < to; i += step) { result.push_back(i); }
  return result;
}

template<class T>
std::vector<T> range(int64_t to) {
  return range<T>(0, to, 1);
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
