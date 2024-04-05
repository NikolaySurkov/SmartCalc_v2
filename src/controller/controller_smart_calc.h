///  Copyright [2023] ns <ns>
#ifndef SRC_CONTROLLER_CONTROLLER_SMART_CALC_H_
#define SRC_CONTROLLER_CONTROLLER_SMART_CALC_H_

#include "../model/calculate.h"
namespace calc {

class Controller {
  using pair_vector = std::pair<std::vector<double>, std::vector<double>>;

 public:
  Controller() = default;
  ~Controller() = default;
  void CalcMath(std::string input_str, double x) {
    Calculate SmartCalc(input_str, x);
    answer_ = SmartCalc.getResult();
  }
  double getAnswer() { return answer_; }

  void GraphCreate(const std::string input_str, double x_begin, double x_end,
                   double y_begin, double y_end) {
    Calculate GraphCalc(input_str, x_begin, x_end, y_begin, y_end);
    graph_ = GraphCalc.getGraph();
  }

  std::vector<double> getVectorX() { return graph_.first; }

  std::vector<double> getVectorY() { return graph_.second; }

 private:
  pair_vector graph_{};
  double answer_;
};

}  // namespace calc
#endif  // SRC_CONTROLLER_CONTROLLER_SMART_CALC_H_
