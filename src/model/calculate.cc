#include "../controller/controller_smart_calc.h"

void calc::Calculate::FunctionGraphMath(const std::string &input_str,
                                        double x_begin, double x_end,
                                        double y_begin, double y_end) {
  double number_points = (fabs(x_begin) + fabs(x_end));
  std::vector<double> x_values, y_values;
  double step = addStep(number_points);
  double c = 0.000001;
  Validation input_string{input_str};

  Conversion polish_not{input_string.getQueueLexemes()};
  output_ = polish_not.getQueueIpn();
  for (double x = x_begin + c; x <= x_end + c; x += step) {
    double result = FunctionMath(x);
    if (result < y_begin - 10 || result > y_end + 10) {
      continue;
    }
    x_values.push_back(x);
    y_values.push_back(result);
  }
  graph_ = std::make_pair(x_values, y_values);
}

double calc::Calculate::FunctionMath(double value_x) {
  input_ = output_;
  while (!input_.empty()) {
    std::visit(
        overloaded{[&](double function) { PushToResultPopInput(function); },
                   [&](function_unary function) {
                     PushToResultPopInput(function(PopResultFromStack()));
                   },
                   [&](function_binary function) {
                     double right_argument = PopResultFromStack();
                     double left_argument = PopResultFromStack();
                     PushToResultPopInput(
                         function(left_argument, right_argument));
                   },
                   [&](auto) { PushToResultPopInput(value_x); }},
        input_.front().getFunc());
  }
  return PopResultFromStack();
}

void calc::Calculate::PushToResultPopInput(double val) {
  result_.push(val);
  input_.pop();
}

double calc::Calculate::PopResultFromStack() {
  double result = result_.top();
  result_.pop();
  return result;
}

calc::Calculate::Calculate(const std::string input_str, double value_x) {
  Validation input_string{input_str};
  Conversion polish_not{input_string.getQueueLexemes()};
  output_ = polish_not.getQueueIpn();
  answer_ = FunctionMath(value_x);
}

double calc::Calculate::addStep(double number_point) {
  if (number_point > 1000000) {
    return 0.4;
  } else if (number_point > 1000) {
    return 0.1;
  } else {
    return 0.001;
  }
}
