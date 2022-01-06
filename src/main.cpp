#include <complex>
#include <vector>

#include "plot.h"
#include "ranges.h"

const double kPi = 3.1415;

std::complex<double> dft(const std::vector<double>& signal, double freq) {
  using namespace std::complex_literals;
  std::complex<double> result(0, 0);
  double N = signal.size();
  for (int i = 0; i < signal.size(); i++) {
	double n = i;
	double k = freq;
	double x = signal[i];
	//	result += signal[i] * exp(-2 * kPi * 1i * n * freq);
	//	result += signal[i] * exp(1i * n * freq);
	result += x * 1. / N * exp(-(1i * n * k) / N);
  }
  return result;
}

int main(int argc, char* argv[]) {
  int samples = 1000;

  double from = 0;
  auto wave1 =
	  linspace([](double x) { return sin(x); }, from, 20 * kPi, samples);
  auto wave2 =
	  linspace([](double x) { return sin(x); }, from, 40 * kPi, samples);

  auto wave_sum = wave1;
  for (size_t i = 0; i < wave1.size(); i++) {
	wave_sum[i] = wave1[i] + wave2[i];
  }

  std::vector<double> transformed, root, xs;
  for (int x = 0; x < 200; x++){
	xs.push_back(x);
	transformed.push_back(abs(dft(wave_sum, x)));
  }

#ifdef MK_WITH_ROOT
  TApplication app("app", &argc, argv);
  TCanvas canvas("canvas", "Fourier transform", 10, 10, 640, 480);
  canvas.Divide(1, 2);

  TGraph transfomred_graph, original_graph;
  transfomred_graph.SetMarkerStyle(7);
  transfomred_graph.SetMarkerSize(2);


  canvas.cd(1);
  for (auto& pair : enumerate(wave_sum)) {
	original_graph.AddPoint(pair.first, pair.second);
  }
  original_graph.Draw();

  canvas.cd(2);
  for (auto& pair : zip(xs, transformed)) {
	transfomred_graph.AddPoint(pair.first, pair.second);
  }

  transfomred_graph.Draw();
  canvas.Draw();
  app.Run();
#endif
}
