//
// Created by M.Kojro on 1/7/2022.
//

//
// Created by M.Kojro on 1/7/2022.
//
#include <complex>
#include <fstream>
#include <vector>
#define FOURIER_IMPLEMENTATIONS
#define FOURIER_WITH_FFT 1

#include "fourier.h"
#include "plot.h"
#include "ranges.h"
#include <cassert>

std::vector<double> parse_file(std::istream& stream) {

  assert(stream.good() && "Passed bad file stream");
  size_t size;
  stream >> size;

  std::vector<double> result;
  while (size--) {
	assert(stream.good() && "Bad value");
	double in;
	stream >> in;
	result.push_back(in);
  }

  return result;
}

int main(int argc, char* argv[]) {

  std::fstream file("../data/dane_10.in", std::ios::in);
  auto signal = parse_file(file);
  auto xs = range<double>(signal.size());

  std::fstream file_dft_out("../python-results/dft_out.in", std::ios::in);
  auto python_transformed = parse_file(file_dft_out);

  std::fstream file_idft("../python-results/idft_out.in", std::ios::in);
  auto python_inversed = parse_file(file_idft);

  auto transformed_mine = fourier::dft(signal);

  auto inversed_mine = fourier::ift(transformed_mine);

#ifdef MK_WITH_ROOT
  TApplication app("app", &argc, argv);
  TCanvas canvas("canvas", "Fourier transform", 10, 10, 640, 480);

#if RAW
  show(xs, signal, canvas, 1);
#endif// RAW

#define TRANSFORMED 1
#if TRANSFORMED
  canvas.Divide(2, 1);
  show(xs, abs(transformed_mine), canvas, 1);
  show(xs, python_transformed, canvas, 2);
#endif// TRANSFORMED

#if INVERSED
  canvas.Divide(2, 1);
  show(xs, inversed_mine, canvas, 1);
  show(xs, python_inversed, canvas, 2);
#endif// INVERSED

  app.Run();
#endif
}
