#ifndef SRC_MODEL_CONVERSION_H_
#define SRC_MODEL_CONVERSION_H_
#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "lexem.h"
namespace calc {
/// @brief Класс перевода математического выражения в обратную польскую нотацию
class Conversion {
 private:
  using queue = std::queue<Lexem>;
  using string = std::string;
  using P_ = Precedence;
  using A_ = Associative;
  using T_ = Type;

 private:
  /// @brief Приватный конструктор по-умолчанию
  Conversion() = default;

 public:
  /// @brief Публичный конструктор принимающий проверенную очередь из лексем
  /// @param input std::queue<Lexem> очередь хранящая в себе последовательность
  /// лексем
  explicit Conversion(const queue &input);

  /// @brief Преобразует очередь в строку
  /// @return std::string строка переведенного математического выражения в
  /// обратную польскую нотацию
  std::string getFormatString();

  /// @brief Метод доступа к информации о действиях совершемых во время
  /// Conversion
  /// @return std::vector<string> со служебной информацией
  std::vector<string> getVectorInfo() { return info_; }

  /// @brief Метод доступа к результирующей очереди содержащей порядок лексем
  /// математического выражения в IPN
  /// @return std::queue<Lexem> Очередь с результатом перевода
  queue getQueueIpn() { return output_ipn_; }

 private:
  /// @brief Процедура распределения функций
  void SortFunctionsAndUnaryBinaryOperands();

  /// @brief Процедура распределения функций раскрутка стека прт лексеме ")"
  void SortFunctionsIfCloseBracket();

  /// процедура добавления лексемы в стек или выходную очередь и удаления из
  /// входной очереди
  void AddStackOrAddOutputEqLeftAssociative();

  /// @brief Процедура извлечения лексемы из входной очереди и помещение ее в
  /// стек
  void AddStackDelInputQueue();

  /// @brief Процедура удаления лексемы из стека и добавления в выходную очередь
  void AddOutputQueueDelStack();

  /// @brief Процедура удаления лексемы из входной очереди и добавления в
  /// выходную очередь
  void AddOutputQueueDelInputQueue();

  /// @brief Удаление Круглых скобок из стека и входной очереди
  void DelBracketsFromStackAndInputQueue();

 private:
  queue input_;
  queue output_ipn_;
  std::stack<Lexem, std::vector<Lexem>> stack_;
  std::vector<string> info_;
};
}  // namespace calc
#endif  // SRC_MODEL_CONVERSION_H_
