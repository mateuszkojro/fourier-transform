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
#include "TRootCanvas.h"
#include <TVirtualFFT.h>
#endif

template<class T>
struct FunctionPlot
{
  FunctionPlot(std::string name, std::vector<T> xs, std::vector<T> ys)
	  : name(std::move(name)), xs(std::move(xs)), ys(std::move(ys)) {}
  std::string name;
  std::vector<T> xs;
  std::vector<T> ys;
};

class Plotter {
 public:
  Plotter(int plots_x, int plots_y, int argc, char** argv)
	  : canvas_("canvas", "NeuralNets", 10, 10, 640, 480),
		root_app_("app", &argc, argv) {
	plots_x_ = plots_x;
	plots_y_ = plots_y;
	canvas_.Divide(plots_x, plots_y);
  }

  void add_function(const FunctionPlot<double>& function) {
	functions_.push_back(function);
  }

  void show() {
	int i = 0;
	for (auto f : functions_) {
	  i++;
	  canvas_.cd(i);
	  graphs_.emplace_back(f.xs.size(), f.xs.data(), f.ys.data());
	  auto& graph = graphs_.back();
	  graph.SetTitle(f.name.c_str());
	  graph.Draw();
	}
	canvas_.Draw();
	auto* rc = (TRootCanvas*)canvas_.GetCanvasImp();
	root_app_.Run();
  }

 private:
  int plots_x_;
  int plots_y_;
  std::vector<FunctionPlot<double>> functions_;
  TCanvas canvas_;
  TApplication root_app_;
  std::vector<TGraph> graphs_;
};


#endif// FOURIER_TRANSFORM__PLOT_H_
