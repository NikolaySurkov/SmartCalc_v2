#include "test.h"

TEST(TEST_MATH, test_1) {
  calc::Controller A;
  std::string input =
      "ln ( 4 ) ^ 5 ^ 2 - 2 ^ 4 ^ 2 * 0.2 * ( - 0.3 ) * 0.1 * 0.1 * 0.6 / 456 ";
  A.CalcMath(input, 4);
  EXPECT_DOUBLE_EQ(A.getAnswer(), 3518.7855793679746);
}

TEST(TEST_MATH, test_2) {
  calc::Controller A;
  std::string input = "55-Sin(23+4)/(45-2^2^2-Ln(6)+Log(6))/78";
  A.CalcMath(input, 4);
  EXPECT_DOUBLE_EQ(A.getAnswer(), 54.999561886007058);
}

TEST(TEST_MATH, test_3) {
  calc::Controller A;
  std::string input = "45 - 45";
  A.CalcMath(input, 4);
  EXPECT_DOUBLE_EQ(A.getAnswer(), 0.0);
}

TEST(TEST_MATH, test_4) {
  calc::Controller A;
  std::string input = "x^x-1";
  A.CalcMath(input, 4);
  EXPECT_DOUBLE_EQ(A.getAnswer(), 255.0);
}

TEST(TEST_MATH, test_5) {
  calc::Controller A;
  std::string input2 = "x^x";
  // A.GraphCreate(input2, -500000, 500002, -10, 10);
  std::string input = "x^1";
  //   A.GraphCreate(input2,1000000,1000111,-10,10);
  A.GraphCreate(input2, 10, 1011, -10, 10);
  A.GraphCreate(input, 1, 2, -1, 1);
  std::vector<double> Y = A.getVectorY();
  std::vector<double> X = A.getVectorX();
  for (std::size_t i = 0; i < Y.size(); ++i) {
    EXPECT_DOUBLE_EQ(Y.at(i), X.at(i));
  }
}

TEST(TEST_MATH, test_6) {
  calc::Controller A;
  std::string input = "tan(1)-sin(13)*2^3+sin(3)";
  A.CalcMath(input, 4);
  EXPECT_DOUBLE_EQ(A.getAnswer(), -1.6628085618983581);
}