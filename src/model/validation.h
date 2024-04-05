#ifndef SRC_MODEL_VALIDATION_H_
#define SRC_MODEL_VALIDATION_H_
#include <algorithm>
#include <queue>
#include <string>

#include "check_sequence.h"
#include "lexem.h"
#include "parser.h"

namespace calc {

/// @brief Класс проверяющий входную строку с математическим выражением на
/// корректность
class Validation {
 private:
  using string = std::string;
  using size_type = std::size_t;

 public:
  /// @brief Публичный Дефолтный конструктор
  Validation() = default;

  /// @brief Публичный Конструктор с одним параметром
  /// @param input_str const std::string Входная строка с математическим
  /// выражением
  explicit Validation(const string &input_str);

  /// @brief Дефолтный деструктор
  ~Validation() = default;

  /// @brief Метод доступа к значению приватного поля output_
  /// @return std::queue<Lexem> выходная очередь с, проверенными на корректность
  /// и порядок следования, лексемами
  std::queue<Lexem> getQueueLexemes() { return output_; }

 private:
  /// @brief Метод подготавливаюций строку к парсингу, выбрасывает искючения
  void PreparingStringForParsing();

  /// @brief Метод разделяющий подготовленную строку на лексемы и проверка
  /// порядка следования лексем
  void ParsingAndCheckingSequenceLexsem();

  /// @brief Удаляет пробелы из входной строки
  void RemoveSpaces();

  /// @brief Переводит символы строки в нижний регистр
  void LowerCase();

  /// @brief Заменяет лексему "mod"  на "%"
  void ReplaceMod();

 private:
  std::string input_str_;
  std::queue<Lexem> output_;
};

}  // namespace calc
#endif  // SRC_MODEL_VALIDATION_H_
