SHELL := /bin/bash
CXX = clang++
CXXFLAGS = -O3 -Ivendor/magic_enum/include/
CXXVERSION = -std=c++17
SRC = main.cpp
OUTPUT_DIR = output


clean:
	-rm output/*

all: clean
	${CXX} -o ${OUTPUT_DIR}/main tests/${SRC} ${CXXFLAGS} ${CXXVERSION}

test: all
	./${OUTPUT_DIR}/main

.PHONY = clean all test