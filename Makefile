SHELL := /bin/bash
CXX = clang++
CXXFLAGS = -Ivendor/magic_enum/include/ -Ivendor/fmt/include
CXXVERSION = -std=c++17
SRC=tests/main.cpp
SRC_TESTS=tests/main_test.cpp tests/test1.cpp tests/test2.cpp
OUTPUT_DIR = output

install:
	-mkdir vendor
	-mkdir vendor/magic_enum
	git clone https://github.com/Neargye/magic_enum.git vendor/magic_enum/
	-mkdir vendor/fmt
	git clone https://github.com/fmtlib/fmt.git vendor/fmt/
	-mkdir vendor/Catch2
	git clone --branch Catch1.x https://github.com/catchorg/Catch2.git vendor/Catch2

clean:
	-rm output/*

compile_main: clean
	${CXX} -o ${OUTPUT_DIR}/main ${SRC} ${CXXFLAGS} ${CXXVERSION}

test: compile_main
	./${OUTPUT_DIR}/main

compile_main_test: clean
	${CXX} -o ${OUTPUT_DIR}/main_test ${SRC_TESTS} ${CXXFLAGS} -Ivendor/Catch2/include/ ${CXXVERSION}

all_tests: compile_main_test
	./${OUTPUT_DIR}/main_test

.PHONY = clean all test