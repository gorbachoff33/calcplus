#include <gtest/gtest.h>

#include "Calc/controller.h"

TEST(Model, simple) {
  s21::Controller tmp;
  std::string str = "1+(-2)-6*8/3";
  double x = tmp.Calculate(str);
  double y = 1 - 6 * 8 / 3 - 2;
  ASSERT_DOUBLE_EQ(x, y);
}

TEST(Model, iks) {
  s21::Controller tmp;
  std::string str = "cos(x)";
  std::string str1 = "45";
  double x = tmp.Calculate(str, str1);
  double y = cos(45);
  ASSERT_DOUBLE_EQ(x, y);
}

TEST(Model, exp) {
  s21::Controller tmp;
  std::string str = "125+1e+3";
  double x = tmp.Calculate(str);
  double y = 125 + 1e+3;
  ASSERT_DOUBLE_EQ(x, y);
}

TEST(Model, trigenometry) {
  s21::Controller tmp;
  std::string str = "cos(sin(tan(45)))";
  double x = tmp.Calculate(str);
  double y = cos(sin(tan(45)));
  ASSERT_DOUBLE_EQ(x, y);
}

TEST(Model, trigenometry2) {
  s21::Controller tmp;
  std::string str = "acos(0.6)+asin(0.9)-atan(0.3)";
  double x = tmp.Calculate(str);
  double y = acos(0.6) + asin(0.9) - atan(0.3);
  ASSERT_DOUBLE_EQ(x, y);
}

TEST(Model, trigenometry3) {
  s21::Controller tmp;
  std::string str = "ln(30)/log10(10)-8^2+sqrt(16)";
  double x = tmp.Calculate(str);
  double y = log(30) / log10(10) - pow(8, 2) + sqrt(16);
  ASSERT_DOUBLE_EQ(x, y);
}

TEST(Model, mod) {
  s21::Controller tmp;
  std::string str = "5mod3";
  double x = tmp.Calculate(str);
  double y = fmod(5, 3);
  ASSERT_DOUBLE_EQ(x, y);
}

TEST(Model, aut) {
  s21::Controller tmp;
  double sum = 1600000;
  double srok = 360;
  double proc = 11.9;
  std::pair<std::pair<double, double>, double> res =
      tmp.Calckredit(sum, srok, proc);
  ASSERT_FLOAT_EQ(res.first.first, 16334.744586);
  ASSERT_FLOAT_EQ(res.first.second, 5880508.050985);
  ASSERT_FLOAT_EQ(res.second, 4280508);
}

TEST(Model, dif) {
  s21::Controller tmp;
  double sum = 1600000;
  double srok = 360;
  double proc = 11.9;
  std::pair<std::pair<double, double>, std::pair<double, double>> res =
      tmp.CalckreditDif(sum, srok, proc);
  ASSERT_FLOAT_EQ(res.first.first, 20311.111);
  ASSERT_FLOAT_EQ(res.first.second, 4488.5186);
  ASSERT_FLOAT_EQ(res.second.first, 2863933.2);
  ASSERT_FLOAT_EQ(res.second.second, 4463933.5);
}

TEST(grapf, test_grapf) {
  s21::Controller tmp;
  double vector = -10;
  double h = 0.001;
  double max_size = 10;
  h = tmp.HCalculate(vector, max_size, h);
  std::string str = "1/cos(x)";
  while(vector < max_size){
  std::pair<std::vector<double>, std::vector<double>> res =
      tmp.GrapfCalc(str, &vector, h, max_size);
  ASSERT_EQ(res.first.size(), res.second.size());
  }
}

TEST(grapf, test_grapf2) {
  s21::Controller tmp;
  double vector = -500000;
  double h = 0.001;
  double max_size = 500000;
  h = tmp.HCalculate(fabs(vector), fabs(max_size), h);
  std::string str = "1/cos(x)";
  while(vector < max_size){
  std::pair<std::vector<double>, std::vector<double>> res =
      tmp.GrapfCalc(str, &vector, h, max_size);
  ASSERT_EQ(res.first.size(), res.second.size());
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
