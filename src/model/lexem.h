#ifndef SRC_MODEL_LEXEM_H_
#define SRC_MODEL_LEXEM_H_
#include <functional>
#include <string>
#include <variant>

namespace calc {

/// @brief ТИП ДЛЯ СТАНЦИИ
enum class Type : int8_t {
  FIRST_END_STR,    // начало и конец строки
  NUMBER,           // числа и икс
  BINARY_OPERATOR,  // + - / * ^ mod
  UNARY_OPERATOR,   // - = ~; + = &
  UNARY_FUNCTION,   // sin cos ...
  OPEN_BRACKET,     // (
  CLOSE_BRACKET,    // )
  NUM_TYPES,        // max_types
};

/// @brief ПРИОРИТЕТ ОПЕРАЦИИ
enum class Precedence : int8_t {
  DEFAULT,
  LOW,
  MEDIUM,
  HIGH,
  UNARY_OPERATOR,
  FUNCTION,
};

/// @brief АССОЦИАТИВНОСТЬ ОПЕРАЦИИ
enum class Associative : int8_t {
  NONE,
  LEFT,
  RIGHT,
};

/// @brief класс хранящий  имя тексемы также ее тип, ассоциативность, приоритет
/// и значение
class Lexem {
 private:
  using string = std::string;
  using P_ = Precedence;
  using A_ = Associative;
  using T_ = Type;
  using function_unary = std::function<double(double)>;
  using function_binary = std::function<double(double, double)>;
  using function_variant =
      std::variant<double, function_unary, function_binary, nullptr_t>;

 public:
  /// @brief Публичный конструктор по-умолчанию
  Lexem();

  /// @brief Публичный конcтруктор
  /// @param name const std::string  Имя лексемы
  /// @param precedence enum class Precedence Приоритет лексемы
  /// @param associative enum class Ассоциативность лексемы
  /// @param type enum class Тип лексемы
  /// @param func function_variant = std::variant<double, function_unary,
  /// function_binary, nullptr_t>
  Lexem(const string &name, P_ precedence, A_ associative, T_ type,
        function_variant func);

  /// @brief Дефолтный деструктор
  ~Lexem() = default;

  /// @brief Метод доступа  извне к полю name_
  /// @return std::string Имя лексемы
  string &getName() { return name_; }

  /// @brief Метод доступа извне к значению поля precedence_
  /// @return enum class Precedence приоритет лексемы
  Precedence getPrecedence() { return precedence_; }

  /// @brief Метод доступа  извне к значению поля associative_
  /// @return class enum Associative Ассоциативность лексемы
  Associative getAssociative() { return associative_; }

  /// @brief  Метод доступа  извне к значению приватного поля type_
  /// @return class enum Type Тип лексемы
  Type getType() { return type_; }

  /// @brief  Метод доступа  извне к значению приватного поля function_
  /// @return function_variant = std::variant<double, function_unary,
  /// function_binary, nullptr_t>;
  function_variant &getFunc() { return function_; }

  /// @brief Метод доступа  извне к значению приватного поля type_ для матричной
  /// проверки последовательности лексем
  /// @return int Тип лексемы
  int getTypeInt() { return static_cast<int>(type_); }

  /// @brief Метод доступа  извне к значению приватного поля precedence_(для
  /// проверки последовательности лексем)
  /// @return int Приоритет лексемы
  int getPrecedenceInt() { return static_cast<int>(precedence_); }

  /// @brief Метод доступа  извне к значению приватного поля associative_(для
  /// проверки последовательности лексем)
  /// @return int Ассоциативность лексемы
  int getAssociativeInt() { return static_cast<int>(associative_); }

  /// @brief Метод добавления числа в поле func_
  /// @param name std::string Имя Лексемы
  /// @param val double Добавляемое число
  void ToNumber(string name, double value);

 private:
  void PushToResult(double val);

 private:
  string name_;
  Precedence precedence_;
  Associative associative_;
  Type type_;
  function_variant function_;
};

}  // namespace calc
#endif  // SRC_MODEL_LEXEM_H_
