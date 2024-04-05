#pragma once
#include <cmath>
#include <iostream>
#include <vector>

namespace calc {
/// @brief Месяц или Год, enum для улучшения читаемости кода
enum PeriodType : bool {
  MONTH,
  YEAR,
};

/// @brief Тип платежа, enum для улучшения читаемости кода
enum TypePay : bool {
  ANNUITIES,
  DIFFERENTIATED,
};

/// @brief Класс для подсчета переплаты по кредиту с Аннуитетными и
/// Дифференцированными платежами
class Credit {
 private:
  /// @brief приватный конструктор по-умолчанию
  Credit();

 public:
  /// @brief Публичный конструктор
  /// @param amount Сумма кредита
  /// @param period Период кредитования
  /// @param interest_rate Процент
  /// @param period_type Месяц или Год
  /// @param type_pay Тип платежа, Аннуитетный или Дифференцированный
  Credit(double amount, int period, double interest_rate, bool period_type,
         bool type_pay);

  double getMonthlyPayment() { return monthly_payment_; }
  double getOverpayment() { return overpayment_; }
  double getFullAmountPayments() { return full_amount_of_payments_; }
  double getMainArrearsDiffCalc() { return main_arrears_; }
  std::vector<double> getVectorMonthyPayments() { return monthly_payments_; }
  double roundNumberTwoDigits(double a);

 private:
  /// @brief Метод подсчета Ежемесечного аннуитетного платежа, начисленных
  /// процентов, основного долга + проценты
  void calculateAmountAnnuityPayment();

  /// @brief Метод подсчета Ежемесечного диффенцированного платежа, начисленных
  /// процентов, основного долга + проценты
  void calculateAmountDifferentPayment();

  /// @brief Функция подсчета основного стабильного ежемесячного платежа
  /// (диффенцированный тип)
  /// @return double основной ежемесячный платеж (диффенцированный тип)
  double calculateMainArrears();

  /// @brief подсчет месячного платежа
  /// @param count_month количество месяцев
  /// @param rate_month процентная ставка за месяц
  /// @return double Платеж за месяц
  double calculateAmountMonth(int count_month, double rate_month);

  /// @brief подсчет месячной процентной ставки
  /// @return double процентная ставка за месяц
  double calculateMonthlyPercentage();

 private:
  double amount_of_credit_;
  int period_;
  double interest_rate_;
  bool type_payment_;
  double monthly_payment_;
  double overpayment_;
  double full_amount_of_payments_;
  double main_arrears_;
  std::vector<double> monthly_payments_;
};

}  // namespace calc
