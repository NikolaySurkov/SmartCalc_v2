#include "conversion.h"

#include "lexem.h"

calc::Conversion::Conversion(const queue &input) : input_(input) {
  while (!input_.empty()) {
    if (input_.front().getType() == T_::NUMBER) {
      AddOutputQueueDelInputQueue();
    } else if (input_.front().getType() == T_::OPEN_BRACKET) {
      AddStackDelInputQueue();
    } else if (input_.front().getType() == T_::BINARY_OPERATOR ||
               input_.front().getType() == T_::UNARY_FUNCTION ||
               input_.front().getType() == T_::UNARY_OPERATOR) {
      SortFunctionsAndUnaryBinaryOperands();
    } else if (input_.front().getType() == T_::CLOSE_BRACKET) {
      SortFunctionsIfCloseBracket();
    }
  }
  while (!stack_.empty()) {
    AddOutputQueueDelStack();
  }
}

std::string calc::Conversion::getFormatString() {
  queue copy_queue(output_ipn_);
  std::string format_str = "\0";
  while (copy_queue.size()) {
    format_str += copy_queue.front().getName();
    copy_queue.pop();
    format_str += " ";
  }
  return format_str;
}

void calc::Conversion::SortFunctionsAndUnaryBinaryOperands() {
  if (stack_.empty()) {
    AddStackDelInputQueue();
  } else if (stack_.top().getPrecedence() < input_.front().getPrecedence()) {
    AddStackDelInputQueue();
  } else if (stack_.top().getPrecedence() == input_.front().getPrecedence() &&
             stack_.top().getAssociative() == A_::RIGHT) {
    AddStackDelInputQueue();
  } else {
    AddStackOrAddOutputEqLeftAssociative();
  }
}

void calc::Conversion::SortFunctionsIfCloseBracket() {
  bool status = true;
  while (status) {
    if (stack_.top().getType() == T_::OPEN_BRACKET) {
      DelBracketsFromStackAndInputQueue();
      status = false;
    } else {
      AddOutputQueueDelStack();
    }
  }
}

void calc::Conversion::AddStackOrAddOutputEqLeftAssociative() {
  bool status = true;
  while (status) {
    if (stack_.empty()) {
      AddStackDelInputQueue();
      status = false;
    } else if (stack_.top().getPrecedence() < input_.front().getPrecedence()) {
      AddStackDelInputQueue();
      status = false;
    } else {
      AddOutputQueueDelStack();
    }
  }
}

void calc::Conversion::AddStackDelInputQueue() {
  info_.push_back("[" + input_.front().getName() + "] - поместить в стек\n");

  stack_.push(input_.front());
  input_.pop();
}

void calc::Conversion::AddOutputQueueDelStack() {
  info_.push_back("[" + stack_.top().getName() +
                  "] - переместить из стека в выходную строку\n");

  output_ipn_.push(stack_.top());
  stack_.pop();
}

void calc::Conversion::AddOutputQueueDelInputQueue() {
  info_.push_back("[" + input_.front().getName() +
                  "] - переместить из входной строки в выходную строку\n");

  output_ipn_.push(input_.front());
  input_.pop();
}

void calc::Conversion::DelBracketsFromStackAndInputQueue() {
  info_.push_back("[" + stack_.top().getName() + "] - удалить из стека\n");

  stack_.pop();
  info_.push_back("[" + input_.front().getName() +
                  "] - удалить из входной строки\n");

  input_.pop();
}
