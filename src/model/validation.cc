#include "validation.h"

calc::Validation::Validation(const string &input_str) : input_str_(input_str) {
  PreparingStringForParsing();
  ParsingAndCheckingSequenceLexsem();
}

void calc::Validation::ParsingAndCheckingSequenceLexsem() {
  Parser parser{input_str_};
  CheckSequence check{parser.getInputList()};
  output_ = parser.getInputQueue();
}

void calc::Validation::RemoveSpaces() {
  input_str_.erase(remove_if(input_str_.begin(), input_str_.end(), isspace),
                   input_str_.end());
  if (!input_str_.size()) {
    throw std::logic_error("An empty expression");
  }
}

void calc::Validation::LowerCase() {
  std::transform(input_str_.begin(), input_str_.end(), input_str_.begin(),
                 ::tolower);
}

void calc::Validation::ReplaceMod() {
  size_type position = input_str_.find("mod");
  while (position < input_str_.size()) {
    input_str_.replace(position, 3, "%");
    position = input_str_.find("mod");
  }
}

void calc::Validation::PreparingStringForParsing() {
  RemoveSpaces();
  LowerCase();
  ReplaceMod();
}
