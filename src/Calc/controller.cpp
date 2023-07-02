#include "controller.h"

namespace s21 {

/*!
 * @brief кредитный аутентный калькулятор
 *
 * \param sum сумма
 * \param srok срок в месяцах
 * \param proc процентная ставка
 * \return std::pair<std::pair<double, double>, double> возвращает 3 значения:
 * 1-е - ежемесячный платеж, 2-е начисленные проценты, 3-е - долг + проценты
 */
std::pair<std::pair<double, double>, double> Controller::Calckredit(
    double sum, double srok, double proc) {
  s21::Model tmp;
  return tmp.Calckredit(sum, srok, proc);
};

/*!
 * @brief кредитный диффирентный калькулятор
 *
 * \param sum сумма
 * \param srok срок в месяцах
 * \param proc процентная ставка
 * \return std::pair<std::pair<double, double>, std::pair<double, double>>
 * возвращает 4 значения: 1-е - максимальный платеж, 2-е - минимальный платеж,
 * 3-е проценты, 4-е - долг + проценты
 */
std::pair<std::pair<double, double>, std::pair<double, double>>
Controller::CalckreditDif(double sum, double srok, double proc) {
  s21::Model tmp;
  return tmp.CalckreditDif(sum, srok, proc);
};

/*!
 * @brief обычный калькулятор с переменной 'Х'
 *
 * \param str выражение
 * \param str_x 'Х' число
 * \return double результат подсчета
 */
double Controller::Calculate(std::string str, std::string str_x) {
  s21::Model tmp;
  return tmp.Parser(str, str_x);
};

/*!
 * @brief обычный калькулятор без переменной 'Х'
 *
 * \param str выражение
 * \return double результат подсчета
 */
double Controller::Calculate(std::string str) {
  s21::Model tmp;
  std::string str_x;
  return tmp.Parser(str, str_x);
};

/*!
 * @brief отрисовка графика
 *
 * \param str выражение
 * \param vector каунт
 * \param h шаг
 * \param max_value максимальное значение для каунта
 * \return std::pair<std::vector<double>, std::vector<double>> возвращает 2
 * вектора для отрисовки графика
 */
std::pair<std::vector<double>, std::vector<double>> Controller::GrapfCalc(
    std::string str, double *vector, double h, double max_value) {
  s21::ModelGrapf tmp;
  return tmp.GrapfCalc(str, vector, h, max_value);
};

/*!
 * @brief уменьшает колличество шагов
 *
 * \param x_min минимальный 'X'
 * \param x_max максимальный 'X'
 * \param res шаг
 * \return double результат
 */
double Controller::HCalculate(const double x_min, const double x_max,
                              const double res) {
  s21::ModelGrapf tmp;
  return tmp.CalculateH(x_min, x_max, res);
};
}  // namespace s21
