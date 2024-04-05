#ifndef SRC_MODEL_CHECK_SEQUENCE_H_
#define SRC_MODEL_CHECK_SEQUENCE_H_
#include <list>
#include <stdexcept>

#include "lexem.h"

namespace calc {
/// @brief класс проверяющий порядок лексем используется std::list и итераторы
class CheckSequence {
 private:
  using P_ = Precedence;
  using A_ = Associative;
  using T_ = Type;

 private:
  /// @brief приватный конструктор по умолчанию инициализирующий поля класса
  CheckSequence() : status_bracket_(0), prev_(0U), curr_(0U) {}

 public:
  /// @brief деструктор определен по-умолчанию
  ~CheckSequence() = default;

  /// @brief Конструктор принимающий последовательность лексем записанных в
  /// std::list
  /// @param input std::list<Lexem> список лексем после предварительной
  /// обработки и парсинга входной std::string
  explicit CheckSequence(const std::list<Lexem> input) : CheckSequence() {
    CheckingSequenseLexem(input);
    checkBracket();
  }

 private:
  /// @brief метод проверки порядка следования лексем, бросает исключения
  /// которые отлавливаются в view
  /// @param input std::list<Lexem> список лексем после предварительной
  /// обработки и парсинга входной std::string
  void CheckingSequenseLexem(const std::list<calc::Lexem> input);

  /// @brief метод бросает исключения если status_bracket_ != 0(неравное
  /// количество открывающих и закрывающих скобок)
  void checkBracket();

 private:
  int status_bracket_;
  std::size_t prev_;
  std::size_t curr_;

  /// @brief Булевая матрица, для проверки последовательности доступ по индексу
  static constexpr bool matrix_bool_[7][7] = {
      {0, 1, 0, 1, 1, 1, 0},  // первый и последний индекс строки
      {1, 0, 1, 0, 0, 0, 1},  // числа и x
      {0, 1, 0, 1, 1, 1, 0},  // операции бинарные
      {0, 1, 0, 1, 1, 1, 0},  // унарные + - (@ ~)
      {0, 0, 0, 0, 0, 1, 0},  // функции sin cos tan ...
      {0, 1, 0, 1, 1, 1, 0},  // скобка открывающая (
      {1, 0, 1, 0, 0, 0, 1},  // скобка закрывающая )
  };
};

}  // namespace calc

#endif  // SRC_MODEL_CHECK_SEQUENCE_H_
