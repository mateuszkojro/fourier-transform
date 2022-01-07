//
// Created by M.Kojro on 1/6/2022.
//

#ifndef FOURIER_TRANSFORM__PLOT_H_
#define FOURIER_TRANSFORM__PLOT_H_

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

//#define INVERSED

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
#endif// FOURIER_TRANSFORM__PLOT_H_
