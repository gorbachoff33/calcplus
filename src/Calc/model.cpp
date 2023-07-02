// created by pizpotli
#include "model.h"

namespace s21 {

/*!
 * @brief обрабатывает строку и вызывает расчеты
 * \param str строка
 * \param str_x строка Х
 * \return double
 */
double Model::Parser(std::string str, std::string str_x) {
  int flag = 0;
  std::string own_str_;
  for (; own_count_ < str.length(); ++own_count_) {
    if ((str[own_count_] > 42 && str[own_count_] < 45) ||
        (str[own_count_] > 45 && str[own_count_] < 58) ||
        str[own_count_] == 41 || str[own_count_] == 92 ||
        str[own_count_] == 94) {
      own_str_.push_back(str[own_count_]);
      flag = 1;
    } else if (str[own_count_] == 40) {
      own_str_.push_back(str[own_count_]);
      flag = 0;
    } else if (str[own_count_] == '*') {
      own_str_.push_back('*');
      flag = 0;
    } else if (str[own_count_] == 'x') {
      int j = 0;
      if (str_x[j] == '(') {
        j++;
      }
      if (str_x[j] == '-') {
        Minus(own_str_);
        j++;
      }
      for (; str_x[j] != '\0'; j++) {
        if (str_x[j] != ')') {
          own_str_.push_back(str_x[j]);
        }
      }
    } else if (str[own_count_] == 45) {
      if (flag == 1) {
        own_str_.push_back('+');
      }
      Minus(own_str_);
    } else if (str[own_count_] == '\n' || str[own_count_] == ' ') {
    } else if (str[own_count_] == 'e') {
      own_str_.push_back(str[own_count_]);
      own_count_++;
      own_str_.push_back(str[own_count_]);
      own_count_++;
      while (str[own_count_] > 47 && str[own_count_] < 58) {
        own_str_.push_back(str[own_count_]);
        own_count_++;
      }
      own_count_--;
    } else {
      CheckStr(str, own_str_);
    }
  }
  Polish(own_str_);
  own_str_.clear();
  own_count_ = 0;
  double res = double_stack_.top();
  double_stack_.pop();
  return res;
}

/*!
 * @brief конвертация в читаемый вид
 */
void Model::Geometric() {
  geometric_.emplace("sin", 's');
  geometric_.emplace("cos", 'c');
  geometric_.emplace("tan", 't');
  geometric_.emplace("asin", 'S');
  geometric_.emplace("acos", 'C');
  geometric_.emplace("atan", 'T');
  geometric_.emplace("mod", '%');
  geometric_.emplace("sqrt", 'R');
  geometric_.emplace("ln", 'l');
  geometric_.emplace("log10", 'L');
  geometric_.emplace("*", '*');
  geometric_.emplace("/", '/');
  geometric_.emplace("+", '+');
};

/*!
 * @brief обработка знака "-"
 * \param own_str_
 */
void Model::Minus(std::string &own_str_) {
  own_str_.push_back('(');
  own_str_.push_back('-');
  own_str_.push_back('1');
  own_str_.push_back(')');
  own_str_.push_back('*');
};

/*!
 * @brief ищет соответствие по ключу
 * \param str
 * \param own_str_
 */
void Model::CheckStr(std::string str, std::string &own_str_) {
  std::string tmp;
  bool x = true;
  while (x) {
    tmp.push_back(str[own_count_]);
    iter_ = geometric_.find(tmp);
    if (iter_ != geometric_.end()) {
      own_str_.push_back(iter_->second);
      x = false;
    }
    own_count_++;
  }
  own_count_--;
};

/*!
 * @brief конвертирует строку в обратную польскую нотацию
 * \param own_str_
 */
void Model::Polish(std::string &own_str_) {
  own_count_ = 0;
  std::string numbers_;
  for (; own_count_ < own_str_.length(); ++own_count_) {
    std::string tmp;
    tmp.push_back(own_str_[own_count_]);
    iter_ = geom_.find(tmp);
    if (iter_ != geom_.end()) {
      if (iter_->second == 'N') {
        NumberWrite(own_str_, numbers_);
      } else {
        if (own_str_[own_count_] == '-') {
          NumberWrite(own_str_, numbers_);
        } else {
          ParserZnak(own_str_, numbers_);
        }
      }
    }
  }
  while (stack_.size()) {
    if (stack_.top() != '(') {
      numbers_.push_back(stack_.top());
      numbers_.push_back(' ');
    }
    stack_.pop();
  }
  Calculate(numbers_);
};

/*!
 * @brief записывает ключи и приоритеты
 */
void Model::CheckCase() {
  geom_.emplace("0", 'N');
  geom_.emplace("1", 'N');
  geom_.emplace("2", 'N');
  geom_.emplace("3", 'N');
  geom_.emplace("4", 'N');
  geom_.emplace("5", 'N');
  geom_.emplace("6", 'N');
  geom_.emplace("7", 'N');
  geom_.emplace("8", 'N');
  geom_.emplace("9", 'N');
  geom_.emplace("-", '1');
  geom_.emplace("+", '1');
  geom_.emplace("*", '2');
  geom_.emplace("/", '2');
  geom_.emplace("%", '2');
  geom_.emplace("^", '3');
  geom_.emplace("c", '3');
  geom_.emplace("s", '3');
  geom_.emplace("t", '3');
  geom_.emplace("C", '3');
  geom_.emplace("S", '3');
  geom_.emplace("T", '3');
  geom_.emplace("l", '3');
  geom_.emplace("L", '3');
  geom_.emplace("R", '3');
  geom_.emplace("(", '4');
  geom_.emplace(")", '0');
};

/*!
 * @brief записывает цифра
 * \param own_str_
 * \param numbers_
 */
void Model::NumberWrite(std::string &own_str_, std::string &numbers_) {
  while (own_str_[own_count_] == 46 || own_str_[own_count_] == 45 ||
         (own_str_[own_count_] > 47 && own_str_[own_count_] < 58)) {
    numbers_.push_back(own_str_[own_count_]);
    own_count_++;
  }
  if (own_str_[own_count_] == 'e') {
    numbers_.push_back(own_str_[own_count_]);
    own_count_++;
    numbers_.push_back(own_str_[own_count_]);
    own_count_++;
    while (own_str_[own_count_] > 47 && own_str_[own_count_] < 58) {
      numbers_.push_back(own_str_[own_count_]);
      own_count_++;
    }
  }
  own_count_--;
  numbers_.push_back(' ');
};

/*!
 * @brief смотрит знаки и скобки
 * \param own_str_
 * \param numbers_
 */
void Model::ParserZnak(std::string &own_str_, std::string &numbers_) {
  if (own_str_[own_count_] == ')') {
    OutputInStack(own_str_, numbers_);
  } else {
    if (iter_->second >= prior_) {
      stack_.push(own_str_[own_count_]);
      if (own_str_[own_count_] == '(') {
        prior_ = '0';
      } else {
        prior_ = iter_->second;
      }
    } else {
      OutputInStack(own_str_, numbers_);
    }
  }
};

/*!
 * @brief обрабатывает и записывает знаки в вид обратной польской нотации
 * \param own_str_
 * \param numbers_
 */
void Model::OutputInStack(std::string &own_str_, std::string &numbers_) {
  int count = 0;
  std::string tmp;
  prior_ = iter_->second;
  while (count == 0 && !stack_.empty() && stack_.top() != '(') {
    tmp.push_back(stack_.top());
    iter_ = geom_.find(tmp);
    if (prior_ <= iter_->second) {
      numbers_.push_back(stack_.top());
      numbers_.push_back(' ');
      stack_.pop();
    } else {
      count = 1;
    }
    tmp.clear();
  }
  if (own_str_[own_count_] == ')') {
    if (stack_.top() == '(') stack_.pop();
    if (stack_.size() == 0) {
      prior_ = 0;
    } else {
      std::string tmp1;
      tmp1.push_back(stack_.top());
      iter_ = geom_.find(tmp1);
      prior_ = iter_->second;
    }
  } else {
    stack_.push(own_str_[own_count_]);
    tmp.clear();
    tmp = own_str_[own_count_];
    iter_ = geom_.find(tmp);
    prior_ = iter_->second;
  }
};

/*!
 * @brief высчитывает результат строки
 * \param numbers_
 */
void Model::Calculate(std::string &numbers_) {
  own_count_ = 0;
  double tmp;
  for (; own_count_ < numbers_.length(); ++own_count_) {
    if (numbers_[own_count_] == '-') {
      double_stack_.push(-1);
      own_count_ += 2;
    } else if (numbers_[own_count_] == '+') {
      tmp = double_stack_.top();
      double_stack_.pop();
      double_stack_.top() = double_stack_.top() + tmp;
    } else if (numbers_[own_count_] == '*') {
      tmp = double_stack_.top();
      double_stack_.pop();
      double_stack_.top() = double_stack_.top() * tmp;
    } else if (numbers_[own_count_] == '/') {
      tmp = double_stack_.top();
      double_stack_.pop();
      double_stack_.top() = double_stack_.top() / tmp;
    } else if (numbers_[own_count_] == '%') {
      tmp = double_stack_.top();
      double_stack_.pop();
      double_stack_.top() = fmod(double_stack_.top(), tmp);
    } else if (numbers_[own_count_] == '^') {
      tmp = double_stack_.top();
      double_stack_.pop();
      double_stack_.top() = pow(double_stack_.top(), tmp);
    } else if (numbers_[own_count_] == 'c') {
      double_stack_.top() = SCos(double_stack_.top());
    } else if (numbers_[own_count_] == 's') {
      double_stack_.top() = SSin(double_stack_.top());
    } else if (numbers_[own_count_] == 't') {
      double_stack_.top() = tan(double_stack_.top());
    } else if (numbers_[own_count_] == 'C') {
      double_stack_.top() = acos(double_stack_.top());
    } else if (numbers_[own_count_] == 'S') {
      double_stack_.top() = asin(double_stack_.top());
    } else if (numbers_[own_count_] == 'T') {
      double_stack_.top() = atan(double_stack_.top());
    } else if (numbers_[own_count_] == 'l') {
      double_stack_.top() = log(double_stack_.top());
    } else if (numbers_[own_count_] == 'L') {
      double_stack_.top() = log10(double_stack_.top());
    } else if (numbers_[own_count_] == 'R') {
      double_stack_.top() = sqrt(double_stack_.top());
    } else if (numbers_[own_count_] == ' ' || numbers_[own_count_] == '\n') {
    } else {
      Convertation(numbers_);
    }
  }
};

/*!
 * @brief конвертирует цифры в число
 * \param numbers_
 */
void Model::Convertation(std::string &numbers_) {
  int count = 0, flag = 0;
  double tmp = 0;
  if (numbers_[own_count_ + 1] != 'e') {
    for (; numbers_[own_count_] != ' ' && numbers_[own_count_] != '\0';
         ++own_count_) {
      if (numbers_[own_count_] == '.') {
        flag = 1;
      } else {
        tmp = (tmp * 10) + (numbers_[own_count_] - '0');
        if (flag == 1) {
          count++;
        }
      }
    }
    while (count > 0) {
      tmp *= 0.1;
      count--;
    }
  } else {
    std::string str;
    while (numbers_[own_count_] != ' ' && numbers_[own_count_] != '\n' &&
           numbers_[own_count_] != '\0') {
      str.push_back(numbers_[own_count_]);
      own_count_++;
    }
    tmp = std::stof(str);
    own_count_--;
  }
  double_stack_.push(tmp);
};

/*!
 * @brief вычисляет косинус
 * \param result результат
 */
double Model::SCos(double other) {
  double result = cos(other);
  if (fabs(result) <= 1e-3) {
    result = 0;
  }
  return result;
};

/*!
 * @brief вычисляет синус
 * \param result результат
 */
double Model::SSin(double other) {
  double result = sin(other);
  if (fabs(result) <= 1e-3) {
    result = 0;
  }
  return result;
};

/*!
 * @brief кредитный аутентный калькулятор, возвращает 3 значения:
 * ежемесячный платеж, сумму процентов и сумму+проценты
 * \param sum сумма
 * \param srok срок
 * \param proc проценты
 * \return std::pair<std::pair<double, double>, double>
 */
std::pair<std::pair<double, double>, double> Model::Calckredit(double sum,
                                                               double srok,
                                                               double proc) {
  std::pair<std::pair<double, double>, double> result;
  result.first.first = proc / 1200;
  double tmp = result.first.first;
  result.first.first = pow(result.first.first + 1, srok);
  result.first.first =
      (sum * tmp * result.first.first) / (result.first.first - 1);
  result.first.second = result.first.first * srok;
  result.second = result.first.second - sum;
  return result;
};

/*!
 * @brief кредитный дифферентный калькулятор, возвращает 4 значения:
 * мин.ежемесячный платеж, макс ежемесячный платеж, сумму процентов,
 * сумма+проценты
 * \param sum сумма
 * \param srok срок
 * \param proc проценты
 * \return std::pair<std::pair<double, double>, std::pair<double, double>>
 */
std::pair<std::pair<double, double>, std::pair<double, double>>
Model::CalckreditDif(double sum, double srok, double proc) {
  std::pair<std::pair<double, double>, std::pair<double, double>> result;
  result.second.second = sum;
  double dolg = sum / srok;
  result.second.first = sum * proc / 1200;
  result.first.first = dolg + result.second.first;
  int count = srok;
  while (count > 1) {
    result.second.second = result.second.second - dolg;
    result.first.second = result.second.second * proc / 1200;
    result.second.first = result.second.first + result.first.second;
    count--;
  }
  result.first.second = result.first.second + dolg;
  result.second.second = result.second.first + sum;
  return result;
};
}  // namespace s21

// int main(){
//   s21::Model tmp;
//   std::string str = "sqrt(16)";
//   std::string str1;
//   std::cout << tmp.Parser(str, str1) << std::endl;
//   std::cout << sqrt(16);
// }