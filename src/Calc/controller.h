// created by pizpotli
#ifndef CPP3_SMARTCALC_CALC_S21_CONTROLLER_H
#define CPP3_SMARTCALC_CALC_S21_CONTROLLER_H

#include "model.h"
#include "model_grapf.h"

namespace s21 {

/*!
 * @brief контроллер, перенаправляет данные из view в model
 */
class Controller {
 public:
  Controller(){};
  ~Controller(){};
  std::pair<std::pair<double, double>, double> Calckredit(double sum,
                                                          double srok,
                                                          double proc);
  std::pair<std::pair<double, double>, std::pair<double, double>> CalckreditDif(
      double sum, double srok, double proc);
  double Calculate(std::string str, std::string str_x);
  double Calculate(std::string str);
  std::pair<std::vector<double>, std::vector<double>> GrapfCalc(
      std::string str, double *vector, double h, double max_value);
  double HCalculate(const double x_min, const double x_max, const double res);
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_CALC_S21_CONTROLLER_H
