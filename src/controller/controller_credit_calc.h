///  Copyright [2023] ns <ns>
#ifndef SRC_CONTROLLER_CONTROLLER_CREDIT_CALC_H_
#define SRC_CONTROLLER_CONTROLLER_CREDIT_CALC_H_
#include <vector>

#include "../model/credit.h"
namespace calc {

class ControllerCreditCalc {
 public:
  ControllerCreditCalc() = default;
  ~ControllerCreditCalc() = default;
  void CreditCalculate(double amount, int period, double rate, bool period_type,
                       bool type_pay) {
    Credit credit_object(amount, period, rate, period_type, type_pay);
    monthly_payment_ = credit_object.getMonthlyPayment();
    overpayment_ = credit_object.getOverpayment();
    full_amount_of_payments_ = credit_object.getFullAmountPayments();
    main_arrears_ = credit_object.getMainArrearsDiffCalc();
    monthly_payments_ = credit_object.getVectorMonthyPayments();
  }

  double getMonthlyPayment() { return monthly_payment_; }
  double getOverpayment() { return overpayment_; }
  double getFullAmountPayments() { return full_amount_of_payments_; }
  double getMainArrearsDiffCalc() { return main_arrears_; }
  std::vector<double> getVectorMonthyPayments() { return monthly_payments_; }

 private:
  double monthly_payment_ = 0.0;
  double overpayment_ = 0.0;
  double full_amount_of_payments_ = 0.0;
  double main_arrears_ = 0.0;
  std::vector<double> monthly_payments_{};
};

}  // namespace calc
#endif  // SRC_CONTROLLER_CONTROLLER_CREDIT_CALC_H_
