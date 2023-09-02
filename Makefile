PROJECT_ROOT=$(CURDIR)

SRC_DIR := $(PROJECT_ROOT)/src

SRCS := $(wildcard $(SRC_DIR)/*.cpp)

MAIN_FILE := $(PROJECT_ROOT)/main.cpp
MAINC_FILE := $(PROJECT_ROOT)/main_check.cpp

SRCS1 := $(SRCS) $(MAIN_FILE)
SRCS2 := $(SRCS) $(MAINC_FILE)

CPPFLAGS = -I $(SRC_DIR)

CXX=g++
CC=$(CXX)
CXXFLAGS=-O2 -Wall -std=c++17

help:
	@echo "Options:"


distclean:
		$(RM) main
		$(RM) *.o

main: $(SRCS1)
		$(CXX) $(CXXFLAGS) $(SRCS1) -o main $(CPPFLAGS)
		
mainc: $(SRCS2)
		$(CXX) $(CXXFLAGS) $(SRCS2) -o main_check $(CPPFLAGS)

run: main
	./main

runc: mainc
	./main_check

%:
	@:
