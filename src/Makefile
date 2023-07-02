CC = g++ -g -Wall -Werror -Wextra -std=c++17

all:install test gcov_report dvi dist

install:
	mkdir build
	cd build && qmake ../Calc/calc.pro && make
	cd build && cp -r calc.app ~/Desktop
	rm -drf build

uninstall:
	rm -rf ~/Desktop/calc.app

dvi:
	open html/index.html

dist: install
	tar -czf calc.tar.gz ~/Desktop/calc.app
	rm -rf ~/Desktop/calc.app


test:
	$(CC) -lgtest test.cc Calc/model.cc Calc/controller.cc Calc/model_grapf.cc --coverage -o test
	./test

gcov_report: test
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report test.info    
	open ./report/index.html

clean:
	rm -rf *.o *.a *.out *gcda *.info test report *.dSYM *.gcno Calc/*.dSYM run_test