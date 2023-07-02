// created by pizpotli
#ifndef CPP3_SMARTCALC_CALC_S21_MODEL_H
#define CPP3_SMARTCALC_CALC_S21_MODEL_H
#include <cmath>
#include <iostream>
#include <map>
#include <stack>
#include <vector>

namespace s21 {

/*!
 * @brief класс конвертации в обратную польскую нотацию и подсчета выражения
 */
class Model {
 public:
  Model() {
    Geometric();
    CheckCase();
  };
  ~Model(){};
  double Parser(std::string str, std::string str_x);
  std::pair<std::pair<double, double>, double> Calckredit(double sum,
                                                          double srok,
                                                          double proc);
  std::pair<std::pair<double, double>, std::pair<double, double>> CalckreditDif(
      double sum, double srok, double proc);

 private:
  size_t own_count_ = 0;
  std::map<std::string, char> geometric_;
  std::map<std::string, char> geom_;
  std::map<std::string, char>::iterator iter_;
  std::stack<char> stack_;
  std::stack<double> double_stack_;
  char prior_ = '0';

  void Geometric();
  void Minus(std::string &own_str_);
  void CheckStr(std::string str, std::string &own_str_);
  void Polish(std::string &own_str_);
  void CheckCase();
  void NumberWrite(std::string &own_str_, std::string &numbers_);
  void ParserZnak(std::string &own_str_, std::string &numbers_);
  void OutputInStack(std::string &own_str_, std::string &numbers_);
  void Calculate(std::string &numbers_);
  void Convertation(std::string &numbers_);
  double SCos(double other);
  double SSin(double other);
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_CALC_S21_MODEL_H