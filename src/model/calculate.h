#ifndef SRC_MODEL_CALCULATE_H_
#define SRC_MODEL_CALCULATE_H_
#include <cmath>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "../controller/controller_smart_calc.h"
#include "check_sequence.h"
#include "conversion.h"
#include "lexem.h"
#include "parser.h"
#include "validation.h"

namespace calc {

template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;
/// @brief Класс подсчета результата выражения
class Calculate {
  using pair_vector = std::pair<std::vector<double>, std::vector<double>>;
  using function_unary = std::function<double(double)>;
  using function_binary = std::function<double(double, double)>;
  using function_variant =
      std::variant<double, function_unary, function_binary, nullptr_t>;
  using P_ = Precedence;
  using A_ = Associative;
  using T_ = Type;

 public:
  /// @brief конструктор по умолчанию
  Calculate() = default;

  /// @brief Конструктор, вызывается при нажатии клавиши =
  /// @param input_str  входная строка с математическим выражением
  /// @param value_x  переменная хранящая значение x
  Calculate(const std::string input_str, double value_x);

  /// @brief Конструктор, вызывается при нажатии клавиши OK
  /// @param input_str Входная строка с математическим выражением
  /// @param x_begin начальное значение x,
  /// @param x_end конечное значение х
  /// @param y_begin начальное значение y
  /// @param y_end конечное значение y
  Calculate(const std::string &input_str, double x_begin, double x_end,
            double y_begin, double y_end) {
    FunctionGraphMath(input_str, x_begin, x_end, y_begin, y_end);
  }

  /// @brief Функция подсчета математического выражения
  /// @param value_x значение x
  /// @return   double результат подсчета
  double FunctionMath(double value_x);

  /// @brief Функция подсчета коодинат оси Y
  /// @param input_str входная строка с математическим выражением
  /// @param x_begin наименьшее значение х, первая точка подсчета
  /// @param x_end наибольшее значение х, последняя точка подсчета
  /// @param y_begin  наименьшее значение по оси y
  /// @param y_end наибольшее значение по оси y
  void FunctionGraphMath(const std::string &input_str, double x_begin,
                         double x_end, double y_begin, double y_end);

  /// @brief Функция задающая шаг(расстояние между соседними значениями х)
  /// @param number_point расстояние от x_begin до x_end
  /// @return double число прибавляемое к x-current при каждой итерации
  double addStep(double number_point);

  /// @brief Процедура записывающая в стек число и удаляющая из входной очереди
  /// @param val число double левый или правый операнд или результат вычисления
  /// функции
  void PushToResultPopInput(double val);

  /// @brief Функция извлекающая из вершины стека число и возвращающая его копию
  /// @return double число из вершины стека
  double PopResultFromStack();

  /// @brief Метод дающий доступ извне к значению поля пары векторов для
  /// отрисовки графика функции
  /// @return std::pair<std::vector<double>, std::vector<double>> пара векторов
  /// хранящие координаты точек x and y
  pair_vector getGraph() { return graph_; }

  /// @brief Метод дающий доступ извне к значению поля answer_(результат
  /// подсчета выражения)
  /// @return double результат получившийся после парсинга строки, перевода в
  /// IPN и подсчета
  double getResult() { return answer_; }

 private:
  // double x_{NAN};
  double answer_ = 0.0;
  std::stack<double, std::vector<double>> result_;
  std::queue<Lexem> input_;
  std::queue<Lexem> output_;
  pair_vector graph_;
};

}  //  namespace calc

#endif  // SRC_MODEL_CALCULATE_H_
