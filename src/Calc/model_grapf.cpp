// created by pizpotli
#include "model_grapf.h"

namespace s21 {

/*!
 * @brief высчитывает максимальное колличество итераций
 * \param x_min минимальный 'X'
 * \param x_max максимальный 'X'
 * \param res шаг
 * \return double результат
 */
double ModelGrapf::CalculateH(const double x_min, const double x_max,
                              const double res) noexcept {
  if (((x_min + x_max) / res) > 200000) return 10;
  return 0.001;
};

/*!
 * @brief записывает точки в 2 вектора
 * \param str выражение
 * \param vector каунт
 * \param h шаг
 * \param max_value максимальный 'X'
 * \return std::pair<std::vector<double>, std::vector<double>>
 */
std::pair<std::vector<double>, std::vector<double>> ModelGrapf::GrapfCalc(
    std::string str, double *vector, double h, double max_value) {
  s21::Model model;
  double res;
  std::string zero = "0";
  std::pair<std::vector<double>, std::vector<double>> xy;
  for (; *vector < max_value; *vector = *vector + h) {
    std::string vector_str = std::to_string(*vector);
    if (fabs(*vector) < 1e-3) {
      *vector = 0;
    }
    res = model.Parser(str, vector_str);
    if (isnan(res) || !isfinite(res) || fabs(res) < 1e-3) {
      while ((isnan(res) || !isfinite(res) || fabs(res) < 1e-3) &&
             *vector < max_value) {
        std::string vector_str1 = std::to_string(*vector);
        res = model.Parser(str, vector_str1);
        *vector = *vector + h;
      }
      break;
    }
    xy.first.push_back(*vector);
    xy.second.push_back(res);
  }
  return xy;
};
}  // namespace s21
