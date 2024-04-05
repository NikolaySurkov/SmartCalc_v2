#ifndef _MODEL_PARSER_H_
#define _MODEL_PARSER_H_
#include <functional>
#include <list>
#include <map>
#include <queue>
#include <regex>  // NOLINT
#include <string>
#include <utility>

#include "lexem.h"
namespace calc {

/// @brief Класс разделяющий строку на лексемы
class Parser {
 private:
  using string = std::string;
  using size_type = std::size_t;
  using regex = std::regex;
  using smatch = std::smatch;
  using queue = std::queue<Lexem>;
  using sregex_iterator = std::sregex_iterator;
  using P_ = Precedence;
  using A_ = Associative;
  using T_ = Type;
  using map = std::map<string, Lexem>;

 private:
  /// @brief Приватный конструктор
  Parser();

 public:
  /// @brief Публичный Конструктор принимающий подготовленную к парсингу строку
  /// @param input_str std::string Входная строка с математическим выражением
  explicit Parser(const string &input_str);

  /// @brief Метод доступа к значению приватного поля  lexemes_queue_
  /// @return std::queue<Lexem> Выходная очередь лексем
  queue getInputQueue() { return lexemes_queue_; }

  /// @brief Преобразует выодную очередь в std::list<Lexem>
  /// @return std::list<Lexem> выходной Список лексем
  std::list<Lexem> getInputList();

  /// @brief Преобразует выодную очередь в std::string
  /// @return std::string выходной Строка имен лексем
  string getFormatString();

 private:
  /// @brief Метод распределяющий, в цикле, по процедурам парсинга в зависимости
  /// от типа значения, добавление в выходную очередь
  /// @param input_str const std::string Входная строка с математическим
  /// выражением
  void ParseringInputString(const string &input_str);

  /// @brief Процедура вычленения и обработки буквенной лексемы
  /// @param input_string std::string копия входной константной строки созданная
  /// в ParseringInputString
  void ParsingLettersLexem(string &input_string);

  /// @brief Процедура вычленения и обработки числовой лексемы
  /// @param input_string std::string копия входной константной строки созданная
  /// в ParseringInputString
  void ParsingNumbersLexem(string &input_string);

  /// @brief Процедура вычленения и обработки односимвольной лексемы
  /// @param input_string std::string копия входной константной строки созданная
  /// в ParseringInputString
  void ParsingCharLexem(string &input_string);

  /// @brief Функция поиска и вычленения Буквенной лексемы регуляным выражением
  /// @param input_string std::string копия входной константной строки созданная
  /// в ParseringInputString
  /// @return std::string Найденная лексема
  string ReadingLetters(string &input_string);

  /// @brief Функция поиска и вычленения числовой лексемы регуляным выражением
  /// @param input_string std::string копия входной константной строки созданная
  /// в ParseringInputString
  /// @return std::string Найденная лексема
  string ReadingNumbers(const string &input_string);

  /// @brief Проверка лексемы на корректность и добаление в выходную очередь,
  /// выбрасывает искючение std::logic_error
  /// @param lexem_  std::string найденная лексема
  void CheckAndPushLexem(const string &lexem_);

  /// @brief Проверка лексемы на Унарность(-)
  /// @param char_lexem
  void CheckUnoOperator(string &char_lexem);

  /// @brief заполнение контейнера std::map<string, Lexem> list_correct_lexemes_
  /// допустимыми лексемами
  void CreateMapLexem();

 private:
  size_type starting_index_;
  std::regex regx_letters_;
  std::regex regx_numbers_;
  queue lexemes_queue_;
  std::map<string, Lexem> list_correct_lexemes_;
  string lexem_;
  static constexpr bool check_type_uno_[7]{1, 0, 1, 1, 0, 1, 0};
};

}  // namespace calc
#endif  // SRC_MODEL_PARSER_H_
