// created by pizpotli
#ifndef CPP3_SMARTCALC_CALC_S21_MODEL_GRAPF_H
#define CPP3_SMARTCALC_CALC_S21_MODEL_GRAPF_H

#include "model.h"

namespace s21 {

/*!
 * @brief model для графика
 */
class ModelGrapf {
 public:
  ModelGrapf(){};
  ~ModelGrapf(){};
  double CalculateH(const double x_min, const double x_max,
                    const double res) noexcept;
  std::pair<std::vector<double>, std::vector<double>> GrapfCalc(
      std::string str, double *vector, double h, double max_value);
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_CALC_S21_MODEL_GRAPF_H