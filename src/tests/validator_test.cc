#include "test.h"

TEST(TEST_VALIDATOR, test_1) {
  std::string input1 = "sin(x-1)%cos(2^4)";
  calc::Parser Parser{input1};
  EXPECT_EQ(Parser.getFormatString(), "sin ( x - 1 ) % cos ( 2 ^ 4 ) ");
  calc::CheckSequence CheckSequence{Parser.getInputList()};
  EXPECT_NO_THROW(calc::CheckSequence CheckSequence{Parser.getInputList()});
}

TEST(TEST_VALIDATOR, test_2) {
  std::string input1 = "";
  calc::Parser Parser{input1};
  EXPECT_EQ(Parser.getFormatString(), "");
}

TEST(TEST_VALIDATOR, test_3) {
  EXPECT_THROW(calc::Parser Parser{"hello"}, std::exception);
  EXPECT_THROW(calc::Parser Parser{"(sin(x-4.5))/23.3s"}, std::exception);
  EXPECT_THROW(calc::Validation Validator{"(sin(x-4.5))/23.3)"},
               std::exception);
  EXPECT_THROW(calc::Validation Validator{"(((sin(x-4.5))/23.3)"},
               std::exception);
  EXPECT_THROW(calc::Validation Validator{"(((sin(x-)4.5))/23.3)"},
               std::exception);
  EXPECT_THROW(calc::Validation Validator{"*"}, std::exception);
  EXPECT_THROW(calc::Validation Validator{"*"}, std::exception);
  EXPECT_THROW(calc::Validation Validator{"-"}, std::exception);
  EXPECT_THROW(calc::Validation Validator{"sin()"}, std::exception);
  EXPECT_THROW(calc::Validation Validator{"cos"}, std::exception);
  EXPECT_THROW(calc::Validation Validator{"cos(mod)"}, std::exception);
  EXPECT_THROW(calc::Validation Validator{"cos-(x)"}, std::exception);
  EXPECT_THROW(calc::Validation Validator{"cos(tan(1)*32^-2-)"},
               std::exception);
  EXPECT_THROW(calc::Validation Validator{"cos(tan(1)*32^-2mod)"},
               std::exception);
  EXPECT_THROW(calc::Validation Validator{"cos(tan(1)*32^-2-)"},
               std::exception);
  EXPECT_THROW(calc::Validation Validator{"cos(tan(1)*32^-2%3,5)"},
               std::exception);
  EXPECT_THROW(calc::Validation Validator{"                "}, std::exception);
  EXPECT_THROW(calc::Validation Validator{" 2324587.2345.23452"},
               std::exception);
  EXPECT_NO_THROW(calc::Validation Validator{" 2.2300e-12"});
}

TEST(TEST_VALIDATOR, test_4) {
  std::string input1 = "34%sin(x-1^4)%cos(2^4)--5";
  calc::Parser Parser{input1};
  EXPECT_EQ(Parser.getFormatString(),
            "34 % sin ( x - 1 ^ 4 ) % cos ( 2 ^ 4 ) - - 5 ");
  calc::CheckSequence CheckSequence{Parser.getInputList()};
  EXPECT_NO_THROW(calc::CheckSequence CheckSequence{Parser.getInputList()});
}
