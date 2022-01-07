//
// Created by M.Kojro on 1/7/2022.
//
#include <complex>
#include <fstream>
#include <vector>
#define FOURIER_IMPLEMENTATIONS
#define FOURIER_WITH_FFT 1

#include "fourier.h"
#include "ranges.h"
#include <cassert>

#ifdef MK_WITH_ROOT
#include "TApplication.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TH1.h"
#include "TMultiGraph.h"
#include "TRootCanvas.h"
#include "TStyle.h"
#include <TVirtualFFT.h>
#endif

#define INVERSED

template<class T>
TGraph* show(std::vector<T> xs, std::vector<double> ys, TCanvas& canvas,
			 int idx) {
  auto* graph = new TGraph;
  assert(xs.size() == ys.size() && "Sizes need to be equal");

  for (size_t i = 0; i < xs.size(); i++) { graph->AddPoint(xs[i], ys[i]); }
  canvas.cd(idx);
  graph->Draw();
  canvas.Draw();
  return graph;
}

int main(int argc, char* argv[]) {

  auto xs = linspace(0, 10 * fourier::kPi, 1000);
  std::vector<double> wave1, wave2, wave_sum;

  for (auto x : xs) {
	double w1 = sin(x);
	double w2 = sin(2 * x);

	wave1.push_back(w1);
	wave2.push_back(w2);
	wave_sum.push_back(w1 + w2);
  }

#ifdef MK_WITH_ROOT
  TApplication app("app", &argc, argv);
  TCanvas canvas("canvas", "Fourier transform", 10, 10, 640, 480);

#ifdef RAW
  canvas.Divide(1, 3);

  show(xs, wave1, canvas, 1);
  show(xs, wave2, canvas, 2);
  show(xs, wave_sum, canvas, 3);
#endif// RAW

  auto cutoff = 12;
  //  auto short_xs = linspace(0, cutoff, 100);

  auto short_xs = range<double>(cutoff);

  auto transformed1 = fourier::dft(wave1);
  auto transformed2 = fourier::dft(wave2);
  auto transformed3 = fourier::dft(wave_sum);

#ifdef TRANSFOMED
  auto transformed1_cut = cut(abs(transformed1), cutoff);
  auto transformed2_cut = cut(abs(transformed2), cutoff);
  auto transformed3_cut = cut(abs(transformed3), cutoff);

  canvas.Divide(1, 3);

  show(short_xs, transformed1_cut, canvas, 1);
  show(short_xs, transformed2_cut, canvas, 2);
  show(short_xs, transformed3_cut, canvas, 3);
#endif// TRANSFOMED

  auto reversed1 = fourier::ift(transformed1);
  auto reversed2 = fourier::ift(transformed2);
  auto reversed3 = fourier::ift(transformed3);

#ifdef INVERSED

  canvas.Divide(1, 3);
  show(xs, reversed1, canvas, 1);
  show(xs, reversed2, canvas, 2);
  show(xs, reversed3, canvas, 3);

#endif// INVERSED

  //  gStyle->SetPaperSize(15, 30.);
  //  gStyle->SetPadRightMargin(1);
  //  gStyle->SetPadLeftMargin(1);
  //  gStyle->SetTextFont(12);

  //  canvas.Print("../report/hpx.tex");
  //  canvas.Draw();
  app.Run();
#endif
}
