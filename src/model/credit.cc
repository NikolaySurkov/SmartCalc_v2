#include "credit.h"

#include "../controller/controller_credit_calc.h"

calc::Credit::Credit() {
  amount_of_credit_ = 0.0;
  period_ = 0;
  interest_rate_ = 0.0;
  type_payment_ = ANNUITIES;
  monthly_payment_ = 0.0;
  overpayment_ = 0.0;
  full_amount_of_payments_ = 0.0;
  main_arrears_ = 0.0;
}

calc::Credit::Credit(double amount, int period, double interest_rate,
                     bool period_type, bool type_pay)
    : Credit() {
  amount_of_credit_ = amount;
  period_ = period_type == MONTH ? period : period * 12;
  interest_rate_ = interest_rate;
  type_payment_ = type_pay;
  if (type_payment_ == ANNUITIES) {
    calculateAmountAnnuityPayment();
  } else {
    calculateAmountDifferentPayment();
  }
}

double calc::Credit::roundNumberTwoDigits(double a) {
  double res = a;
  res = a * 100.0;
  res = roundl(res);
  res = res / 100.0;
  return res;
}

void calc::Credit::calculateAmountAnnuityPayment() {
  double month_interest_rate = calculateMonthlyPercentage();
  double mid = powl((1 + month_interest_rate), period_);
  double coefficient = (month_interest_rate * mid) / (mid - 1);
  monthly_payment_ = roundNumberTwoDigits(amount_of_credit_ * coefficient);
  full_amount_of_payments_ = period_ * monthly_payment_;
  overpayment_ = full_amount_of_payments_ - amount_of_credit_;
}

void calc::Credit::calculateAmountDifferentPayment() {
  int count_month = 1;
  double rate_month = calculateMonthlyPercentage();
  main_arrears_ = calculateMainArrears();
  double procent_month = 0.0;
  while (count_month <= period_) {
    procent_month = calculateAmountMonth(count_month, rate_month);
    monthly_payments_.push_back((main_arrears_ + procent_month));
    overpayment_ += procent_month;
    count_month++;
  }
  full_amount_of_payments_ =
      roundNumberTwoDigits(amount_of_credit_ + overpayment_);
  overpayment_ = roundNumberTwoDigits(overpayment_);
}

double calc::Credit::calculateMainArrears() {
  return amount_of_credit_ / period_;
}

double calc::Credit::calculateAmountMonth(int count_month, double rate_month) {
  double prev = ((count_month - 1) * (amount_of_credit_ / period_));
  return ((amount_of_credit_ - prev) * rate_month);
}

double calc::Credit::calculateMonthlyPercentage() {
  return interest_rate_ / (100.0 * 12.0);
}
