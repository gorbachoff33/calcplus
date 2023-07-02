#include "calc.h"

#include "ui_calc.h"

Calc::Calc(QWidget *parent) : QMainWindow(parent), ui(new Ui::Calc) {
  ui->setupUi(this);

  connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(ClickedE()));
  connect(ui->pushButton_toch, SIGNAL(clicked()), this, SLOT(OnTochClicked()));
  connect(ui->pushButton_iks, SIGNAL(clicked()), this, SLOT(DigitNumbers()));
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(DigitNumbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(DigitNumbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(DigitNumbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(DigitNumbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(DigitNumbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(DigitNumbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(DigitNumbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(DigitNumbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(DigitNumbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(DigitNumbers()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(MathOperations()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(MathOperations()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(MathOperations()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(MathOperations()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(MathOperations()));
  connect(ui->pushButton_invers, SIGNAL(clicked()), this, SLOT(Inversion()));
  connect(ui->pushButton_skob, SIGNAL(clicked()), this, SLOT(SkobLeft()));
  connect(ui->pushButton_skob_2, SIGNAL(clicked()), this, SLOT(SkobRight()));
  connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(GrapfArrow()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(MathSimple()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(MathSimple()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(MathSimple()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(MathSimple()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(MathSimple()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(MathOperations()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(MathOperations()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(MathOperations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(MathSimple()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(MathOperations()));
  connect(ui->pushButton_equel, SIGNAL(clicked()), this, SLOT(EquelClicked()));
  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(ACClicked()));
  connect(ui->itog_aut, SIGNAL(clicked()), this, SLOT(AutCalculate()));
  connect(ui->itog_dif, SIGNAL(clicked()), this, SLOT(DifCalculate()));

  ui->pushButton_toch->setCheckable(true);
  ui->pushButton_plus->setCheckable(true);
  ui->pushButton_minus->setCheckable(true);
  ui->pushButton_mul->setCheckable(true);
  ui->pushButton_div->setCheckable(true);
  ui->pushButton_mod->setCheckable(true);
  ui->pushButton_pow->setCheckable(true);
  ui->pushButton_cos->setCheckable(true);
  ui->pushButton_sin->setCheckable(true);
  ui->pushButton_tan->setCheckable(true);
  ui->pushButton_acos->setCheckable(true);
  ui->pushButton_asin->setCheckable(true);
  ui->pushButton_atan->setCheckable(true);
  ui->pushButton_sqrt->setCheckable(true);
  ui->pushButton_ln->setCheckable(true);
  ui->pushButton_log->setCheckable(true);
  ui->pushButton_iks->setCheckable(true);
  ui->pushButton_equel->setCheckable(true);
};

/**
 * @brief Destroy the Calc:: Calc object
 *
 */
Calc::~Calc() { delete ui; };

/**
 * @brief валидация численного ввода
 *
 */
void Calc::DigitNumbers() {
  QPushButton *button = (QPushButton *)sender();
  LenSrez();
  count_invert_ = 0;
  invert_ = "";
  if (!(ui->result_show->text().contains('e'))) {
    if (!(ui->result_show->text().contains('x')) &&
        !(ui->result_show->text().contains(')'))) {
      if (ui->pushButton_iks->isChecked()) {
        flag_x_ = 1;
      }
      if (count_skob_1_ || count_skob_2_) {
        ui->result_show_2->setText(ui->result_show_2->text() +
                                   ui->result_show->text());
        ui->result_show->setText("");
        count_skob_1_ = count_skob_2_ = 0;
        tmp = "";
      }
      if (flag_znak_ && !flag_math_) {
        ui->result_show_2->setText(ui->result_show_2->text() + tmp);
        tmp = "";
        ui->result_show->setText("");
      }
      if (flag_math_) {
        count_skob_ = 1;
        ui->result_show_2->setText(ui->result_show_2->text() +
                                   ui->result_show->text());
        ui->result_show->setText("");
        flag_math_ = 0;
      }
      DigitNumbers2();
      ui->pushButton_iks->setChecked(false);
    }
  } else {
    if (ui->result_show->text().size() == 3 && button->text() != "0" &&
        button->text() != "x" && !ui->result_show->text().contains(')')) {
      ui->result_show->setText(ui->result_show->text() + button->text());
      flag_e_ = 0;
    } else if (ui->result_show->text().size() > 3 && button->text() != "x" &&
               !ui->result_show->text().contains(')')) {
      ui->result_show->setText(ui->result_show->text() + button->text());
    }
  }
};

/**
 * @brief обрабатывает числовой ввод
 *
 */
void Calc::DigitNumbers2() {
  QPushButton *button = (QPushButton *)sender();
  flag_znak_ = 0;
  count_start_ = 1;
  flag_number_ = 1;
  if (ui->result_show->text().contains(".") && button->text() == "0") {
    ui->result_show->setText(ui->result_show->text() + button->text());
  } else if (button->text() == "0" && ui->result_show->text() == "0") {
  } else {
    if (ui->result_show->text() == "0") {
      ui->result_show->setText(button->text());
    } else {
      if (button->text() != "x") {
        ui->result_show->setText(ui->result_show->text() + button->text());
      } else {
        if (ui->result_show->text() == "") {
          ui->result_show->setText(ui->result_show->text() + button->text());
        }
      }
    }
  }
};

/**
 * @brief проверяет длинну строки
 *
 */
void Calc::LenSrez() {
  int len = ui->result_show_2->text().size();
  int len2 = ui->result_show->text().size();
  if ((len + len2) > 80 * x_count_) {
    x_count_++;
    ui->result_show_2->setText(ui->result_show_2->text() + "\n");
  }
};

/**
 * @brief ввод и валидация '.'
 *
 */
void Calc::OnTochClicked() {
  if (flag_number_ && !(ui->result_show->text().contains(')')) &&
      !(ui->result_show->text().contains('x')) &&
      !(ui->result_show->text().contains('e'))) {
    if (!(ui->result_show->text().contains('.')))
      ui->result_show->setText(ui->result_show->text() + ".");
  }
};

/**
 * @brief +/- ввод и валидация инверсии
 *
 */
void Calc::Inversion() {
  LenSrez();
  if (flag_number_ && !flag_e_) {
    if (!count_invert_) {
      invert_ = ui->result_show->text();
      ui->result_show->setText("(-" + ui->result_show->text() + ")");
      count_invert_ = 1;
    } else {
      ui->result_show->setText(invert_);
      count_invert_ = 0;
    }
  }
};

/**
 * @brief валидация и обработка простых математических операций
 *
 */
void Calc::MathSimple() {
  QPushButton *button = (QPushButton *)sender();
  button->setChecked(true);
  tmp = button->text();
  LenSrez();
  count_invert_ = 0;
  invert_ = "";
  if (!flag_e_) {
    if (flag_number_ && !stop_flag_) {
      if (!flag_znak_ && count_start_) {
        if (ui->pushButton_plus->isChecked()) {
          ui->result_show_2->setText(ui->result_show_2->text() +
                                     ui->result_show->text());
          ui->result_show->setText(button->text());
          ui->pushButton_plus->setChecked(false);
        } else if (ui->pushButton_minus->isChecked()) {
          ui->result_show_2->setText(ui->result_show_2->text() +
                                     ui->result_show->text());
          ui->result_show->setText(button->text());
          ui->pushButton_minus->setChecked(false);
        } else if (ui->pushButton_mul->isChecked()) {
          ui->result_show_2->setText(ui->result_show_2->text() +
                                     ui->result_show->text());
          ui->result_show->setText(button->text());
          ui->pushButton_mul->setChecked(false);
        } else if (ui->pushButton_div->isChecked()) {
          ui->result_show_2->setText(ui->result_show_2->text() +
                                     ui->result_show->text());
          ui->result_show->setText(button->text());
          ui->pushButton_div->setChecked(false);
        } else if (ui->pushButton_mod->isChecked()) {
          ui->result_show_2->setText(ui->result_show_2->text() +
                                     ui->result_show->text());
          ui->result_show->setText(button->text());
          ui->pushButton_mod->setChecked(false);
        } else if (ui->pushButton_pow->isChecked()) {
          ui->result_show_2->setText(ui->result_show_2->text() +
                                     ui->result_show->text());
          ui->result_show->setText(button->text());
          ui->pushButton_pow->setChecked(false);
        }
        flag_znak_ = skob_two_ = 1;
      }
      flag_math_ = flag_number_ = 0;
    }
    if (count_start_ && !flag_math_ && !count_skob_1_ && !stop_flag_) {
      ui->result_show->setText(button->text());
    }
  } else {
    if (ui->result_show->text().contains('e') &&
        !ui->result_show->text().contains('-') &&
        !ui->result_show->text().contains('+')) {
      if (ui->pushButton_plus->isChecked()) {
        ui->result_show->setText(ui->result_show->text() + "+");
        ui->pushButton_plus->setChecked(false);
      } else if (ui->pushButton_minus->isChecked()) {
        ui->result_show->setText(ui->result_show->text() + "-");
        ui->pushButton_minus->setChecked(false);
      }
      flag_e_ = 2;
    }
  }
};

/**
 * @brief валидация сложных математических операций
 *
 */
void Calc::MathOperations() {
  QPushButton *button = (QPushButton *)sender();
  LenSrez();
  count_invert_ = 0;
  invert_ = "";
  if (!stop_flag_) {
    if (!count_start_) {
      count_skob_ = 1;
      if (x_zero_ || count_skob_1_) {
        ui->result_show_2->setText(ui->result_show_2->text() +
                                   ui->result_show->text());
      }
      ui->result_show->setText(button->text() + "(");
      main_count_++;
      x_zero_ = 1;
      count_skob_1_ = 0;
      count_skob_two_ = 1;
    }
    if ((flag_znak_ || count_start_) && !flag_number_) {
      MathOperations2();
    }
    flag_math_ = 1;
    if (flag_znak_) {
      flag_math_ = 1;
      operation_ = button->text();
      ui->result_show->setText(button->text() + "(");
    }
  }
};

/**
 * @brief обработка сложных математических операций
 *
 */
void Calc::MathOperations2() {
  QPushButton *button = (QPushButton *)sender();
  button->setChecked(true);
  operation_ = button->text();
  if (!stop_flag_) {
    if (ui->pushButton_cos->isChecked()) {
      ui->result_show_2->setText(ui->result_show_2->text() +
                                 ui->result_show->text());
      ui->result_show->setText(button->text());
      ui->pushButton_cos->setChecked(false);
    } else if (ui->pushButton_sin->isChecked()) {
      ui->result_show_2->setText(ui->result_show_2->text() +
                                 ui->result_show->text());
      ui->result_show->setText(button->text());
      ui->pushButton_sin->setChecked(false);
    } else if (ui->pushButton_tan->isChecked()) {
      ui->result_show_2->setText(ui->result_show_2->text() +
                                 ui->result_show->text());
      ui->result_show->setText(button->text());
      ui->pushButton_tan->setChecked(false);
    } else if (ui->pushButton_acos->isChecked()) {
      ui->result_show_2->setText(ui->result_show_2->text() +
                                 ui->result_show->text());
      ui->result_show->setText(button->text());
      ui->pushButton_acos->setChecked(false);
    } else if (ui->pushButton_asin->isChecked()) {
      ui->result_show_2->setText(ui->result_show_2->text() +
                                 ui->result_show->text());
      ui->result_show->setText(button->text());
      ui->pushButton_asin->setChecked(false);
    } else if (ui->pushButton_atan->isChecked()) {
      ui->result_show_2->setText(ui->result_show_2->text() +
                                 ui->result_show->text());
      ui->result_show->setText(button->text());
      ui->pushButton_atan->setChecked(false);
    } else if (ui->pushButton_sqrt->isChecked()) {
      ui->result_show_2->setText(ui->result_show_2->text() +
                                 ui->result_show->text());
      ui->result_show->setText(button->text());
      ui->pushButton_sqrt->setChecked(false);
    } else if (ui->pushButton_ln->isChecked()) {
      ui->result_show_2->setText(ui->result_show_2->text() +
                                 ui->result_show->text());
      ui->result_show->setText(button->text());
      ui->pushButton_ln->setChecked(false);
    } else if (ui->pushButton_log->isChecked()) {
      ui->result_show_2->setText(ui->result_show_2->text() +
                                 ui->result_show->text());
      ui->result_show->setText(button->text());
      ui->pushButton_log->setChecked(false);
    }
    count_skob_ = 1;
    main_count_++;
  }
};

/**
 * @brief ввод и валидация левой скобки
 *
 */
void Calc::SkobLeft() {
  QPushButton *button = (QPushButton *)sender();
  button->setChecked(true);
  LenSrez();
  count_invert_ = skob_two_ = count_skob_two_ = 0;
  invert_ = "";
  if (!stop_flag_ && !flag_e_) {
    if (!flag_znak_ && !flag_number_ && !count_start_ && !count_zero_skob_ &&
        !flag_math_) {
      ui->result_show->setText("");
      count_zero_skob_ = 1;
    }
    if ((flag_znak_ && !flag_number_) || !count_start_ || flag_math_) {
      ui->result_show_2->setText(ui->result_show_2->text() +
                                 ui->result_show->text());
      ui->result_show->setText("");
      ui->result_show->setText(button->text());
      count_skob_1_ = 1;
      main_count_++;
    }
  }
  ui->pushButton_skob->setChecked(false);
};

/**
 * @brief ввод и валидация правой скобки
 *
 */
void Calc::SkobRight() {
  QPushButton *button = (QPushButton *)sender();
  button->setChecked(true);
  LenSrez();
  count_invert_ = 0;
  invert_ = "";
  if (main_count_ > 0 && !flag_e_) {
    if (flag_number_ && (skob_two_ || count_skob_two_ || count_skob_2_)) {
      ui->result_show_2->setText(ui->result_show_2->text() +
                                 ui->result_show->text());
      ui->result_show->setText(button->text());
      ui->result_show->setText(")");
      main_count_--;
      count_skob_2_ = 1;
      skob_two_ = count_skob_two_ = 0;
    }
  }
  ui->pushButton_skob_2->setChecked(false);
};

/**
 * @brief записывает число при вводе 'Х'
 *
 */
void Calc::EquelX() {
  s21::Controller controller;
  if (ui->pushButton_equel->isChecked()) {
    if (ui->result_show->text() != "") {
      if (ui->result_show->text().contains('x')) {
        ui->result_show->setText("");
      } else {
        std::string str1 = ui->result_show_2->text().toUtf8().data();
        std::string vector_str = ui->result_show->text().toUtf8().data();
        ui->result_show->setText(
            QString ::number(controller.Calculate(str1, vector_str)));
      }
    }
  }
  ui->pushButton_equel->setChecked(false);
};

/**
 * @brief инфиксный ввод
 *
 */
void Calc::ClickedE() {
  if (ui->result_show->text().size() == 1 && flag_number_ &&
      !ui->result_show->text().contains("e") &&
      !ui->result_show->text().contains(')')) {
    ui->result_show->setText(ui->result_show->text() + "e");
    flag_e_ = 1;
  }
};

/**
 * @brief кнопка '=', проверяет валидацию при нажатии
 *
 */
void Calc::EquelClicked() {
  s21::Controller controller;
  if ((ui->pushButton_equel->isChecked() || count_equel_ == 2) && !stop_flag_) {
    if ((flag_number_ || count_skob_2_) &&
        (ui->result_show_2->text().length() +
         ui->result_show->text().length()) > ui->result_show->text().length() &&
        !flag_e_) {
      QString tmp_tmp = ui->result_show->text();
      ui->result_show->setText("");
      ui->result_show_2->setText(ui->result_show_2->text() + tmp_tmp);
      while (main_count_ > 0) {
        ui->result_show_2->setText(ui->result_show_2->text() + ")");
        main_count_--;
      }
      if (flag_x_) {
        stop_flag_ = 1;
        flag_number_ = 0;
      } else if (!flag_x_ && !count_equel_) {
        std::string str1 = ui->result_show_2->text().toUtf8().data();
        ui->result_show->setText(QString ::number(controller.Calculate(str1)));
      }
      count_equel_ = 1;
    }
  } else {
    EquelX();
  }
  ui->pushButton_equel->setChecked(false);
};

/**
 * @brief запускает функцию отрисовки
 *
 */
void Calc::GrapfArrow() {
  if (flag_x_) {
    count_equel_ = 2;
    EquelClicked();
    if (count_equel_ == 1) {
      GrapfMain();
    }
  }
};

/**
 * @brief отрисовка графика
 *
 */
void Calc::GrapfMain() {
  s21::Controller controller;
  double tmp_vector = ui->oc_x_min->value(), h = 0.001;
  int grapf_f = 0;
  ui->widget->xAxis->setRange(ui->oc_x_min->value(), ui->oc_x_max->value());
  ui->widget->yAxis->setRange(ui->oc_y_min->value(), ui->oc_y_max->value());
  std::string str1 = ui->result_show_2->text().toUtf8().data();
  h = controller.HCalculate(fabs(ui->oc_x_min->value()),
                            fabs(ui->oc_x_max->value()), h);
  for (; tmp_vector < ui->oc_x_max->value(); grapf_f++) {
    std::pair<std::vector<double>, std::vector<double>> tmp;
    tmp = controller.GrapfCalc(str1, &tmp_vector, h, ui->oc_x_max->value());
    ui->widget->addGraph();
    ui->widget->graph(grapf_f)->addData(
        QVector<double>(tmp.first.begin(), tmp.first.end()),
        QVector<double>(tmp.second.begin(), tmp.second.end()));
  }
  ui->result_show->setText("GRAPH BUILT");
  ui->widget->replot();
  flag_x_ = 0;
}

/**
 * @brief аутентный калькулятор
 *
 */
void Calc::AutCalculate() {
  s21::Controller controller;
  std::pair<std::pair<double, double>, double> result =
      controller.Calckredit(ui->sum_kred_aut->value(),
                            ui->srok_kred_aut->value(), ui->proc_aut->value());
  ui->sum_mes_aut->setText(QString("%1").arg(result.first.first, 0, 'f', 2));
  ui->dolg_aut->setText(QString("%1").arg(result.first.second, 0, 'f', 2));
  ui->nach_proc_aut->setText(QString("%1").arg(result.second, 0, 'f', 2));
};

/**
 * @brief диффирентный калькулятор
 *
 */
void Calc::DifCalculate() {
  s21::Controller controller;
  std::pair<std::pair<double, double>, std::pair<double, double>> result =
      controller.CalckreditDif(ui->sum_kred_dif->value(),
                               ui->srok_kred_dif->value(),
                               ui->proc_dif->value());
  ui->sum_mes_dif->setText(QString("%1").arg(result.first.first, 0, 'f', 2) +
                           " ... " +
                           QString("%1").arg(result.first.second, 0, 'f', 2));
  ui->nach_proc_dif->setText(QString("%1").arg(result.second.first, 0, 'f', 2));
  ui->dolg_dif->setText(QString("%1").arg(result.second.second, 0, 'f', 2));
};

/**
 * @brief очищает кнопки и каунты
 *
 */
void Calc::ACClicked() {
  ui->widget->addGraph()->data()->clear();
  while (acc_f_ >= 0) {
    ui->widget->graph(acc_f_)->data()->clear();
    ui->widget->replot();
    acc_f_--;
  }
  ui->pushButton_plus->setChecked(false);
  ui->pushButton_minus->setChecked(false);
  ui->pushButton_mul->setChecked(false);
  ui->pushButton_div->setChecked(false);
  ui->pushButton_mod->setChecked(false);
  ui->pushButton_pow->setChecked(false);
  ui->pushButton_cos->setChecked(false);
  ui->pushButton_sin->setChecked(false);
  ui->pushButton_tan->setChecked(false);
  ui->pushButton_acos->setChecked(false);
  ui->pushButton_asin->setChecked(false);
  ui->pushButton_atan->setChecked(false);
  ui->pushButton_sqrt->setChecked(false);
  ui->pushButton_ln->setChecked(false);
  ui->pushButton_log->setChecked(false);
  ui->pushButton_equel->setChecked(false);

  tmp = "";
  count_start_ = count_skob_ = count_skob_1_ = count_skob_2_ = count_skob_two_ =
      0;
  skob_two_ = main_count_ = count_zero_skob_ = flag_math_ = flag_number_ = 0;
  flag_znak_ = x_zero_ = count_invert_, flag_e_ = 0;
  flag_x_ = acc_f_ = stop_flag_ = count_equel_ = 0;
  x_count_ = 1;
  invert_ = "";
  operation_ = "";
  ui->result_show->setText("0");
  ui->result_show_2->setText("");
  ui->widget->replot();
};
