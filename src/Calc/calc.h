#ifndef CPP3_SMARTCALC_CALC_CALC_H
#define CPP3_SMARTCALC_CALC_CALC_H

#include <QMainWindow>

#include "controller.h"
#include "model.h"
#include "model_grapf.h"

/*!
*@mainpage CPP3_SmartCalc_V2.0
* Реализация калькулятора:
    - Вычисляет тригенометрические функции
    - На вход программы могут подаваться как целые числа, так и вещественные
числа, записанные и через точку, и в экспоненциальной форме записи.
    - Вычисление должно производится после полного ввода вычисляемого выражения
и нажатия на символ =.
    - Вычисление произвольных скобочных арифметических выражений в инфиксной
нотации.
    - Вычисление произвольных скобочных арифметических выражений в инфиксной
нотации с подстановкой значения переменной x в виде числа.
    - Построение графика функции, заданной с помощью выражения в инфиксной
нотации с переменной x.
    - Область определения и область значения функций ограничиваются числами от
-1000000 до 1000000.
    - Возможность ввода до 255 символов.
*/

QT_BEGIN_NAMESPACE
namespace Ui {
class Calc;
}
QT_END_NAMESPACE

class Calc : public QMainWindow {
 public:
  Calc(QWidget *parent = nullptr);
  ~Calc();

 private:
  Ui::Calc *ui;
  double begin, end;
  Q_OBJECT
  int x_zero_ = 0;
  int flag_znak_ = 0;
  int count_start_ = 0;
  int flag_math_ = 0;
  int flag_number_ = 0;
  int count_skob_ = 0;
  int count_skob_1_ = 0;
  int count_zero_skob_ = 0;
  int main_count_ = 0;
  int count_skob_2_ = 0;
  int skob_two_ = 0;
  int count_skob_two_ = 0;
  int count_invert_ = 0;
  int x_count_ = 1;
  int acc_f_ = 0;
  int stop_flag_ = 0;
  int flag_x_ = 0;
  double result_ = 0;
  int count_equel_ = 0;
  int flag_e_ = 0;
  QString operation_;
  QString tmp;
  QString invert_;

 private slots:
  void DigitNumbers();
  void DigitNumbers2();
  void OnTochClicked();
  void Inversion();
  void EquelClicked();
  void ACClicked();
  void MathSimple();
  void MathOperations();
  void MathOperations2();
  void SkobLeft();
  void SkobRight();
  void LenSrez();
  void AutCalculate();
  void DifCalculate();
  void GrapfMain();
  void GrapfArrow();
  void EquelX();
  void ClickedE();
};
#endif  // CPP3_SMARTCALC_CALC_CALC_H
