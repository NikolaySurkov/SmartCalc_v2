#include "test.h"

TEST(TEST_CONVERSION, test_1) {
  calc::Validation C{
      "1 - 3 + 5 - 11 * 0.12 ^ 2 / 33 - sin ( 2.1 ) + cos ( 2 ^ 4 ) / 11 + 22 "
      "- tan ( 4 ) ^ 3 + 1 + 2 + ( ~ 3 ) / 2 + 1 ^ 3 - log ( 12 ) / log ( 3.4 "
      ")"};
  calc::Conversion D{C.getQueueLexemes()};
  EXPECT_EQ(D.getFormatString(),
            "1 3 - 5 + 11 0.12 2 ^ * 33 / - 2.1 sin - 2 4 ^ cos 11 / + 22 + 4 "
            "tan 3 ^ - 1 + 2 + 3 - 2 / + 1 3 ^ + 12 log 3.4 log / - ");
}

TEST(TEST_CONVERSION, test_2) {
  calc::Validation C{
      "ln ( 4 ) ^ 5 ^ 2 - 2 ^ 4 ^ 2 * 0.2 * ( ~ 0.3 ) * 0.1 * 0.1 * 0.6 / "
      "456 "};
  calc::Conversion D{C.getQueueLexemes()};
  EXPECT_EQ(D.getFormatString(),
            "4 ln 5 2 ^ ^ 2 4 2 ^ ^ 0.2 * 0.3 - * 0.1 * 0.1 * 0.6 * 456 / - ");
}

TEST(TEST_CONVERSION, test_3) {
  calc::Validation C{"1"};
  calc::Conversion D{C.getQueueLexemes()};
  EXPECT_EQ(D.getFormatString(), "1 ");
}

TEST(TEST_CONVERSION, test_4) {
  calc::Validation C{"1+9modsin(16)^(45-4)"};
  calc::Conversion D{C.getQueueLexemes()};
  EXPECT_EQ(D.getFormatString(), "1 9 16 sin 45 4 - ^ % + ");
}

TEST(TEST_CONVERSION, test_5) {
  calc::Validation C{"atan(1^7^8)-9%45-43/34+acos(x) - 78^2"};
  calc::Conversion D{C.getQueueLexemes()};
  EXPECT_EQ(D.getFormatString(),
            "1 7 8 ^ ^ atan 9 45 % - 43 34 / - x acos + 78 2 ^ - ");
}

TEST(TEST_CONVERSION, test_6) {
  calc::Validation C{"2^2--sin(45) *13"};
  calc::Conversion D{C.getQueueLexemes()};
  EXPECT_EQ(D.getFormatString(), "2 2 ^ 45 sin - 13 * - ");
}

TEST(TEST_CONVERSION, test_7) {
  calc::Validation C{"-------5--7^23-6^(5.0/4.00000001)"};
  calc::Conversion D{C.getQueueLexemes()};
  EXPECT_EQ(D.getFormatString(),
            "5 - - - - - - - 7 - 23 ^ - 6 5.0 4.00000001 / ^ - ");
}