#include "test.h"

TEST(TEST_CREDIT, test_1) {
  calc::ControllerCreditCalc A;
  double sum = 1900000;
  int period = 50;
  double rate = 13.3;
  bool type_period = calc::YEAR;
  bool type_pay = calc::ANNUITIES;
  A.CreditCalculate(sum, period, rate, type_period, type_pay);
  EXPECT_NEAR(A.getMonthlyPayment(), 21086.639999999999, EPS);
  EXPECT_NEAR(A.getOverpayment(), 10751984, EPS);
  EXPECT_NEAR(A.getFullAmountPayments(), 12651984, EPS);
}

TEST(TEST_CREDIT, test_2) {
  calc::ControllerCreditCalc A;
  double sum = 1900000;
  int period = 50;
  double rate = 13.3;
  bool type_period = calc::YEAR;
  bool type_pay = calc::DIFFERENTIATED;
  A.CreditCalculate(sum, period, rate, type_period, type_pay);
  EXPECT_NEAR(A.getVectorMonthyPayments().back(), 3201.7638888888896, EPS);
  EXPECT_NEAR(A.getVectorMonthyPayments().front(), 24225.00, EPS);
  EXPECT_NEAR(A.getOverpayment(), 6328029.17, EPS);
  EXPECT_NEAR(A.getFullAmountPayments(), 8228029.17, EPS);
}

TEST(TEST_CREDIT, test_3) {
  calc::ControllerCreditCalc A;
  double sum = 5201000;
  int period = 25;
  double rate = 8.4;
  bool type_period = calc::YEAR;
  bool type_pay = calc::ANNUITIES;
  A.CreditCalculate(sum, period, rate, type_period, type_pay);
  EXPECT_NEAR(A.getMonthlyPayment(), 41529.949999999997, EPS);
  EXPECT_NEAR(A.getOverpayment(), 7257985, EPS);
  EXPECT_NEAR(A.getFullAmountPayments(), 12458985, EPS);
}

TEST(TEST_CREDIT, test_4) {
  calc::ControllerCreditCalc A;
  double sum = 5201000;
  int period = 25;
  double rate = 8.4;
  bool type_period = calc::YEAR;
  bool type_pay = calc::DIFFERENTIATED;
  A.CreditCalculate(sum, period, rate, type_period, type_pay);
  EXPECT_NEAR(A.getVectorMonthyPayments().back(), 17458.02, 0.01);
  EXPECT_NEAR(A.getVectorMonthyPayments().front(), 53743.67, 0.01);
  EXPECT_NEAR(A.getOverpayment(), 5479253.50, 0.001);
  EXPECT_NEAR(A.getFullAmountPayments(), 10680253.50, 0.01);
}