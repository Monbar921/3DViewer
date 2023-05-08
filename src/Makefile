CC = g++
CCFLAGS = -Wall -Werror -Wextra -std=c++17 -fsanitize=address
GCOVFLAGS = --coverage
TESTFLAGS = -lgtest
VALGRINDFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
OS = $(shell uname -s)
OPEN = open
ifeq ($(OS), Linux)
	TESTFLAGS += -lm -lpthread -lrt -lsubunit
	OPEN = xdg-open
endif

PROJECT_NAME = 3DViewer

APP_NAME = $(PROJECT_NAME)
ifeq ($(OS), Darwin)
	APP_NAME = $(PROJECT_NAME).app
endif

QMAKE = qmake
# QMAKE = $(shell find ~ /usr -type f -name "qmake" -perm /a=x | sort | head -1)
QT_INSTALL_PREFIX = $(shell $(QMAKE) -query QT_INSTALL_PREFIX)

CORE_NAME = viewercore
SRC_DIR = .
TEST_DIR = ./tests
REPORT_DIR = ./report
BUILD_DIR = ../build
APP_DIR = ../app
DIST_DIR = ../dist

RUN = $(APP_DIR)/$(APP_NAME)
ifeq ($(OS), Darwin)
	RUN = open $(APP_DIR)/$(APP_NAME)
endif

SOURCE = $(wildcard $(SRC_DIR)/model/*.cc $(SRC_DIR)/controller/*.cc $(SRC_DIR)/common/*.cc)
INCLUDE_LIBS=-I./model -I./controller -I./common	
TESTCC = $(TEST_DIR)/tests.cc
TEST = $(TEST_DIR)/tests

default: all

all: build

build:
	mkdir -p $(BUILD_DIR)
	# cmake $(SRC_DIR)/CMakeLists.txt -B $(BUILD_DIR)
	cmake -DCMAKE_PREFIX_PATH=$(QT_INSTALL_PREFIX) $(SRC_DIR)/CMakeLists.txt -B $(BUILD_DIR)
	make -C $(BUILD_DIR)

install: build
	mkdir -p $(APP_DIR)
	cp -r $(BUILD_DIR)/$(APP_NAME) $(APP_DIR)/$(APP_NAME)

uninstall:
	rm -rf $(APP_DIR)

rebuild: clean all

run: install
	$(RUN)

dvi:
	mkdir -p $(APP_DIR)
	texi2dvi $(SRC_DIR)/manual.tex -c -o $(APP_DIR)/manual.dvi

dist:
	mkdir -p $(DIST_DIR)
	tar -cvf $(DIST_DIR)/Viewer.2.0.tar $(SRC_DIR)

style:
	clang-format -n --verbose --style=google $(SRC_DIR)/*/*.cc
	clang-format -n --verbose --style=google $(SRC_DIR)/*/*.h

cppcheck:
	cppcheck --enable=all --suppress=missingInclude --suppress=unusedFunction --suppress=noExplicitConstructor $(SRC_DIR)/*/*.cc

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(TEST_DIR)/$(CORE_NAME).*
	rm -rf $(TEST_DIR)/*.o
	rm -rf $(TEST_DIR)/*.gcno $(TEST_DIR)/*.info  $(TEST_DIR)/*.gcda
	rm -rf *.gcno *.info  *.gcda
	rm -rf $(TEST_DIR)/test_cov
	rm -rf $(TEST_DIR)/tests
	rm -rf leaks_report.txt valgrind_report.txt
	rm -rf $(REPORT_DIR)

tests: $(SOURCE) $(TESTCC)
	$(CC) $(CCFLAGS) $(SOURCE) $(TESTCC) $(TESTFLAGS) $(INCLUDE_LIBS) -o $(TEST) 
	$(TEST)

valgrind: tests
	valgrind $(VALGRINDFLAGS) --log-file=valgrind_report.txt $(TEST)

leaks: tests
	leaks -atExit -- $(TEST) > leaks_report.txt

gcov_report: $(SOURCE) $(TESTCC)
	rm -rf $(REPORT_DIR)
	$(CC) $(SOURCE) $(TESTCC) $(GCOVFLAGS) $(TESTFLAGS) $(INCLUDE_LIBS) -o $(TEST_DIR)/test_cov
	$(TEST_DIR)/test_cov
	rm -rf tests.gcda $(TEST_DIR)/*tests.gcda
	lcov --no-external -t "test_$(CORE_NAME)" -o $(TEST_DIR)/test_$(CORE_NAME).info -c -d .
	genhtml -o $(REPORT_DIR) $(TEST_DIR)/test_$(CORE_NAME).info
	$(OPEN) $(REPORT_DIR)/index.html

.PHONY: all clean tests gcov_report default style cppcheck valgrind leaks build install uninstall rebuild run dvi dist my_test