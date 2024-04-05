#include "parser.h"

#include <cmath>

#include "lexem.h"

calc::Parser::Parser(const string &input_str) : Parser() {  // NOLINT
  CreateMapLexem();
  ParseringInputString(input_str);
}

std::list<calc::Lexem> calc::Parser::getInputList() {
  std::list<Lexem> output_list;
  queue copy_queue{lexemes_queue_};
  while (copy_queue.size()) {
    output_list.insert(output_list.end(), copy_queue.front());
    copy_queue.pop();
  }
  return output_list;
}

calc::Parser::string calc::Parser::getFormatString() {
  queue copy_queue(lexemes_queue_);
  string format_str = "\0";
  while (copy_queue.size()) {
    format_str += copy_queue.front().getName();
    copy_queue.pop();
    format_str += " ";
  }
  return format_str;
}

calc::Parser::Parser() {
  starting_index_ = 0U;
  regx_letters_ = "([a-z]+)";
  regx_numbers_ = "\\d+([.]\\d+)?(e([+-])?\\d+)?";
}

void calc::Parser::ParseringInputString(const string &input_str) {
  string input_string{input_str};
  while (starting_index_ < input_string.size()) {
    if (isalpha(*(input_string.begin() + starting_index_))) {
      ParsingLettersLexem(input_string);
    } else if (isdigit(*(input_string.begin() + starting_index_))) {
      ParsingNumbersLexem(input_string);
    } else {
      ParsingCharLexem(input_string);
    }
    starting_index_ += lexem_.size();
  }
}

void calc::Parser::ParsingLettersLexem(string &input_string) {
  lexem_ = ReadingLetters(input_string);
  CheckAndPushLexem(lexem_);
}

void calc::Parser::ParsingNumbersLexem(string &input_string) {
  lexem_ = ReadingNumbers(input_string);
  if (lexem_ != "") {
    Lexem number_lexem{};
    number_lexem.ToNumber(lexem_, std::stold(lexem_));
    lexemes_queue_.push(number_lexem);
  }
}

void calc::Parser::ParsingCharLexem(string &input_string) {
  lexem_ = *(input_string.begin() + starting_index_);
  CheckUnoOperator(lexem_);
  CheckAndPushLexem(lexem_);
}

calc::Parser::string calc::Parser::ReadingLetters(
    string &input_string) {  // NOLINT
  regex lexem_regex(regx_letters_);
  auto iterator_regex = sregex_iterator(input_string.begin() + starting_index_,
                                        input_string.end(), lexem_regex);
  smatch lexem = *iterator_regex;
  return lexem.str();
}

calc::Parser::string calc::Parser::ReadingNumbers(
    const string &input_string) {  // NOLINT
  regex lexem_regex(regx_numbers_);
  std::sregex_iterator iterator_regex = std::sregex_iterator(
      input_string.begin() + starting_index_, input_string.end(), lexem_regex);
  smatch lexem = *iterator_regex;
  return lexem.str();
}

void calc::Parser::CheckAndPushLexem(const string &lexem_) {  // NOLINT
  if (lexem_ == " ") return;
  auto lexem_map_it = list_correct_lexemes_.find(lexem_);
  if (lexem_map_it == list_correct_lexemes_.end()) {
    throw std::logic_error("Incorrect lexsem: " + lexem_);
  }
  lexemes_queue_.push(lexem_map_it->second);
}

void calc::Parser::CheckUnoOperator(string &char_lexem) {  // NOLINT
  if (char_lexem == "+" || char_lexem == "-") {
    if ((lexemes_queue_.size() &&
         check_type_uno_[lexemes_queue_.back().getTypeInt()]) ||
        !lexemes_queue_.size()) {
      char_lexem = char_lexem == "-" ? "~" : " ";
    }
  }
}

void calc::Parser::CreateMapLexem() {
  std::initializer_list<std::pair<const string, Lexem>> list = {
      {"(", Lexem("(", P_::DEFAULT, A_::NONE, T_::OPEN_BRACKET, nullptr)},
      {")", Lexem(")", P_::DEFAULT, A_::NONE, T_::CLOSE_BRACKET, nullptr)},
      {"~", Lexem("-", P_::UNARY_OPERATOR, A_::RIGHT, T_::UNARY_OPERATOR,
                  std::negate<double>())},
      {"x", Lexem("x", P_::DEFAULT, A_::NONE, T_::NUMBER, nullptr)},
      {"+",
       Lexem("+", P_::LOW, A_::LEFT, T_::BINARY_OPERATOR, std::plus<double>())},
      {"-", Lexem("-", P_::LOW, A_::LEFT, T_::BINARY_OPERATOR,
                  std::minus<double>())},
      {"*", Lexem("*", P_::MEDIUM, A_::LEFT, T_::BINARY_OPERATOR,
                  std::multiplies<double>())},
      {"/", Lexem("/", P_::MEDIUM, A_::LEFT, T_::BINARY_OPERATOR,
                  std::divides<double>())},
      {"%", Lexem("%", P_::MEDIUM, A_::LEFT, T_::BINARY_OPERATOR, fmodl)},
      {"^", Lexem("^", P_::HIGH, A_::RIGHT, T_::BINARY_OPERATOR, powl)},
      {"sqrt",
       Lexem("sqrt", P_::FUNCTION, A_::RIGHT, T_::UNARY_FUNCTION, sqrtl)},
      {"sin", Lexem("sin", P_::FUNCTION, A_::RIGHT, T_::UNARY_FUNCTION, sinl)},
      {"cos", Lexem("cos", P_::FUNCTION, A_::RIGHT, T_::UNARY_FUNCTION, cosl)},
      {"tan", Lexem("tan", P_::FUNCTION, A_::RIGHT, T_::UNARY_FUNCTION, tanl)},
      {"asin",
       Lexem("asin", P_::FUNCTION, A_::RIGHT, T_::UNARY_FUNCTION, asinl)},
      {"acos",
       Lexem("acos", P_::FUNCTION, A_::RIGHT, T_::UNARY_FUNCTION, acosl)},
      {"atan",
       Lexem("atan", P_::FUNCTION, A_::RIGHT, T_::UNARY_FUNCTION, atanl)},
      {"log",
       Lexem("log", P_::FUNCTION, A_::RIGHT, T_::UNARY_FUNCTION, log10l)},
      {"ln", Lexem("ln", P_::FUNCTION, A_::RIGHT, T_::UNARY_FUNCTION, logl)},
  };
  list_correct_lexemes_.insert(list);
}
