TARGET_LIB  = smartcalc.a
CC          = g++ -std=c++17 -g
CFLAGS      = -Wall -Werror -Wextra  -fno-stack-protector -lm

TEST_DIR    = tests/
MODEL_DIR   = model/
OS         := $(shell uname)
WAY_OBJ     = ./object_files/
TESTS       =  $(wildcard ${TEST_DIR}*.cc)
TEST_OBJ    =  $(patsubst ${TEST_DIR}%.cc, $(WAY_OBJ)%.o, $(TESTS))
SRC			=  $(wildcard ${MODEL_DIR}*.cc)
OBJ			=  $(patsubst ${MODEL_DIR}%.cc, $(WAY_OBJ)%.o, $(SRC))
GFLAGS      = -fprofile-arcs -ftest-coverage
TEST_FLAGS  = $(shell pkg-config --cflags --libs gtest)

SKIP_D      = '*/testdemo.cpp' '*/pointer_traits.h' '*/compressed_pair.h' '*/allocator.h'\
			'*/iomanip' '*/istream' '*/stdlib.h' '*/exception' '*/sstream' '*/locale' '*/__locale'\
			'*/streambuf' '*/ios' '*/string' '*/__debug' '*/ostream' '*/cstring' '*/__iterator/ostreambuf_iterator.h'\
			'*/__memory/allocator.h''*/__memory/pointer_traits.h''*/__memory/compressed_pair.h'\
			'*/__string/char_traits.h' '*/__utility/swap.h' '*/Library/*'

all: clean_all install gcov_report leak

smartcalc.a : $(OBJ)
	@ar rc ${TARGET_LIB} $(OBJ)

$(WAY_OBJ)%.o : ${MODEL_DIR}%.cc $(WAY_OBJ)%.o
	$(CC) $(CFLAGS) -c  $<   -o  $@ 


test: test_all
	./test

test_all: ${TARGET_LIB} $(TEST_OBJ)
	${CC} ${CFLAGS}  $(TEST_OBJ) ${TARGET_LIB} -o test ${TEST_FLAGS} -lm


$(WAY_OBJ)%.o : ${TEST_DIR}%.cc $(WAY_OBJ)%.o
	$(CC) $(CFLAGS) -c  $<   -o  $@ 


install:  clean uninstall
	mkdir ../build_SmartCalc
	cd ../build_SmartCalc && cmake ../src/CMakeLists.txt && make


uninstall: clean
	rm -rf ../build_SmartCalc

dist:
	rm -rf Archive_SmartCalc21_v2.0/
	mkdir Archive_SmartCalc21_v2.0/
	mkdir Archive_SmartCalc21_v2.0/src
	cp  -r controller  Archive_SmartCalc21_v2.0/src/
	cp  -r view  Archive_SmartCalc21_v2.0/src/
	cp  -r model  Archive_SmartCalc21_v2.0/src/
	cp  -r resources  Archive_SmartCalc21_v2.0/src/
	cp  -r CMakeLists.txt  Archive_SmartCalc21_v2.0/src/
	cp  -r main.cc  Archive_SmartCalc21_v2.0/src/
	cp  -r info  Archive_SmartCalc21_v2.0/src/
	cp  Makefile  Archive_SmartCalc21_v2.0/src/
	# cp  -r tests  Archive_SmartCalc21_v2.0/src/
	tar cvzf Archive_SmartCalc21_v2.0.tgz Archive_SmartCalc21_v2.0/
	rm -rf Archive_SmartCalc21_v2.0/

dist_clean:
	rm -rf Archive_SmartCalc21_v2.0*

dvi:
ifeq ($(OS),Darwin)
	rm -rf info/doxygen
	doxygen info/configure_doc
	open -a "Google Chrome" info/doxygen/html/index.html

else
	#sudo apt install doxygen
	doxygen info/configure_doc
	xdg-open info/doxygen/html/index.html
endif



leak: 
ifeq ($(OS),Darwin)
	CK_FORK=no leaks -atExit -- ./test
else
	CK_FORK=no valgrind --leak-check=full -s --track-origins=yes --log-file=leak.log ./test
endif	

clean:
	@rm -f $(WAY_OBJ)*.o $(TARGET_LIB ) *.out *.gc* test test.c  tests/*.info  tests/gcov* *.log   *.tex *.o *.a *.user
	@rm -rf report *.dSYM info/doxygen build


gcov_report: 
	$(CC) -o test ${MODEL_DIR}*.cc tests/*.cc $(TEST_FLAGS) $(GFLAGS)
	./test
	make lcov

lcov: 
	lcov --quiet --no-recursion --capture --directory . --output-file test.info
	@lcov --quiet --no-recursion -r test.info '/usr/*' '*/v1/*'  ${SKIP_D}   -o test.info
	genhtml -o ./report/ test.info
	@rm -f *.gcda  *.gcno 
	@rm -f  test.info


open:
ifeq ($(OS),Darwin)
	open -a "Google Chrome" report/index.html
else
	xdg-open report/index.html
endif

clean_all: clean uninstall dist_clean


clang:
	clang-format -n -style=google *.cc
	clang-format -n -style=google tests/*.h
	clang-format -n -style=google tests/*.cc 
	clang-format -n -style=google model/*.h
	clang-format -n -style=google model/*.cc
	clang-format -n -style=google controller/*.h


clangI:
	clang-format -i -style=google *.cc
	clang-format -i -style=google tests/*.h
	clang-format -i -style=google tests/*.cc 
	clang-format -i -style=google model/*.h
	clang-format -i -style=google model/*.cc
	clang-format -i -style=google controller/*.h
	