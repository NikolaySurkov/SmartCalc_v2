#include "check_sequence.h"

void calc::CheckSequence::CheckingSequenseLexem(const std::list<Lexem> input) {
  std::list<calc::Lexem> input_list = input;
  auto position = input_list.begin();
  while (position != input_list.end()) {
    curr_ = position->getTypeInt();
    if (position->getType() == T_::OPEN_BRACKET) status_bracket_ += 1;
    if (position->getType() == T_::CLOSE_BRACKET) status_bracket_ -= 1;
    if (!matrix_bool_[prev_][curr_]) {
      throw std::logic_error("Incorrect sequence lexsem: " +
                             position->getName());
    }
    prev_ = curr_;
    ++position;
  }
  if (!matrix_bool_[prev_][0]) {
    --position;
    throw std::logic_error("Incorrect sequence lexsem: " + position->getName());
  }
}

void calc::CheckSequence::checkBracket() {
  if (status_bracket_ < 0) {
    throw std::logic_error("The opening bracket is missing");
  } else if (status_bracket_ > 0) {
    throw std::logic_error("The closing bracket is missing");
  }
}
