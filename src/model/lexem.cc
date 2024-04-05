#include "lexem.h"

void calc::Lexem::ToNumber(string name, double val) {
  Lexem number(name, P_::DEFAULT, A_::RIGHT, T_::NUMBER, val);
  *this = number;
}

calc::Lexem::Lexem(const string &name, P_ precedence, A_ associative, T_ type,
                   function_variant func) {
  name_ = name;
  precedence_ = precedence;
  associative_ = associative;
  type_ = type;
  function_ = func;
}

calc::Lexem::Lexem() {
  name_ = "";
  precedence_ = P_::DEFAULT;
  associative_ = A_::NONE;
  type_ = T_::NUMBER;
  function_ = nullptr;
}
