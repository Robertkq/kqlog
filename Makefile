SHELL := /bin/bash
CXX = clang++
CXXFLAGS = -O3 -Ivendor/magic_enum/include/ -Ivendor/fmt/include
CXXVERSION = -std=c++20
SRC = main.cpp
OUTPUT_DIR = output

install:
	-mkdir vendor
	-mkdir vendor/magic_enum
	git clone https://github.com/Neargye/magic_enum.git vendor/magic_enum/
	-mkdir vendor/fmt
	git clone https://github.com/fmtlib/fmt.git vendor/fmt/

clean:
	-rm output/*

all: clean
	${CXX} -o ${OUTPUT_DIR}/main tests/${SRC} ${CXXFLAGS} ${CXXVERSION}

test: all
	./${OUTPUT_DIR}/main

.PHONY = clean all test