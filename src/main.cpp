#include <complex>
#include <fstream>
#include <vector>

#define FOURIER_IMPLEMENTATIONS
#include "fourier.h"
#include "plot.h"
#include "ranges.h"

const double kPi = 3.1415;

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
  //  int samples = 1000;
  //
  //  double from = 0;
  //  auto wave1 =
  //	  linspace([](double x) { return sin(x); }, from, 20 * kPi, samples);
  //  auto wave2 =
  //	  linspace([](double x) { return sin(x); }, from, 40 * kPi, samples);
  //
  //  auto wave_sum = wave1;
  //  for (size_t i = 0; i < wave1.size(); i++) {
  //	wave_sum[i] = wave1[i] + wave2[i];
  //  }

  std::fstream file("../data/dane_08.in", std::ios::in);
  auto wave_sum = parse_file(file);

  std::vector<std::complex<double>> transformed;
  std::vector<double> root, xs, inversed, transformed_double;
  for (int x = 0; x < wave_sum.size(); x++) {
	xs.push_back(x);
	auto result = fourier::dft(wave_sum, x);
	transformed.push_back(result);
	transformed_double.push_back(abs(result));
  }

  for (auto x : range(0, wave_sum.size())) {
	inversed.push_back(fourier::ift(transformed, x));
  }

#ifdef MK_WITH_ROOT
  TApplication app("app", &argc, argv);
  TCanvas canvas("canvas", "Fourier transform", 10, 10, 640, 480);
  canvas.Divide(1, 2);

  TGraph transfomred_graph, original_graph, inverse_graph;
  transfomred_graph.SetMarkerStyle(7);
  transfomred_graph.SetMarkerSize(2);

  for (auto& pair : enumerate(wave_sum)) {
	original_graph.AddPoint(pair.first, pair.second);
  }
  TMultiGraph m_graph;
  m_graph.Add(&original_graph);

  canvas.cd(1);
  for (auto& pair : zip(xs, transformed_double)) {
	transfomred_graph.AddPoint(pair.first, pair.second);
  }
  transfomred_graph.Draw();

  canvas.cd(2);
  for (auto& pair : zip(xs, inversed)) {
	inverse_graph.AddPoint(pair.first, pair.second);
  }
  m_graph.Add(&inverse_graph);
  m_graph.Draw("apl");

  canvas.Draw();
  app.Run();
#endif
}
