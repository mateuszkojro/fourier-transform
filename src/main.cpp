#include <complex>
#include <fstream>
#include <vector>

#define FOURIER_IMPLEMENTATIONS
#define FOURIER_WITH_FFT 1

#include "fourier.h"
#include "plot.h"
#include "ranges.h"

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

  std::fstream file("../data/dane_08.in", std::ios::in);
  auto wave_sum = parse_file(file);

  auto transformed = fourier::dft(wave_sum);
  auto inverted = fourier::ift(transformed);

#ifdef MK_WITH_ROOT
  TApplication app("app", &argc, argv);
  TCanvas canvas("canvas", "Fourier transform", 10, 10, 640, 480);
  canvas.Divide(1, 3);

  TMultiGraph m_graph;
  TGraph transfomred_graph, fft_graph, original_graph, inverse_graph,
	  inverse_fft_graph;

  for (auto& pair : enumerate(wave_sum)) {
	original_graph.AddPoint(pair.first, pair.second);
  }
  for (auto& pair : enumerate(inverted)) {
	inverse_graph.AddPoint(pair.first, pair.second);
  }

  for (auto& pair : enumerate(fourier::ift(fourier::fft(wave_sum)))) {
	inverse_fft_graph.AddPoint(pair.first, pair.second);
  }

  canvas.cd(1);
  m_graph.Add(&inverse_graph);
  m_graph.Add(&original_graph);
//  m_graph.Add(&inverse_fft_graph);
  m_graph.Draw("apl");

  canvas.cd(2);
  for (auto& pair : enumerate(transformed)) {
	transfomred_graph.AddPoint(pair.first, abs(pair.second));
  }
  transfomred_graph.Draw();

//  canvas.cd(3);
//  for (auto& pair : enumerate(fourier::fft(wave_sum))) {
//	fft_graph.AddPoint(pair.first, abs(pair.second));
//  }
//  fft_graph.Draw();

  canvas.Draw();
  app.Run();
#endif
}
