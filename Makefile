PROJECT_ROOT=$(CURDIR)

SRC_DIR := $(PROJECT_ROOT)/src

SRCS := $(wildcard $(SRC_DIR)/*.cpp)

MAIN_FILE := $(PROJECT_ROOT)/main.cpp
MAINC_FILE := $(PROJECT_ROOT)/main_check.cpp
MAINC10_FILE := $(PROJECT_ROOT)/main_check10.cpp
MAINT_FILE := $(PROJECT_ROOT)/main_try.cpp

SRCS1 := $(SRCS) $(MAIN_FILE)
SRCS2 := $(SRCS) $(MAINC_FILE)
SRCS3 := $(SRCS) $(MAINC10_FILE)
SRCS4 := $(SRCS) $(MAINT_FILE)

CPPFLAGS = -I $(SRC_DIR)

CXX=g++
CC=$(CXX)
CXXFLAGS=-O2 -Wall -std=c++17

help:
	@echo "Options:"


.PHONY : distclean
distclean:
		$(RM) main main_check main_check10 main_try
		$(RM) *.o

main: $(SRCS1)
		$(CXX) $(CXXFLAGS) $(SRCS1) -o main $(CPPFLAGS)
		
mainc: $(SRCS2)
		$(CXX) $(CXXFLAGS) $(SRCS2) -o main_check $(CPPFLAGS)
		
mainc10: $(SRCS3)
		$(CXX) $(CXXFLAGS) $(SRCS3) -o main_check10 $(CPPFLAGS)
		
maintry: $(SRCS4)
		$(CXX) $(CXXFLAGS) $(SRCS4) -o main_try $(CPPFLAGS)
run: main
	./main

runc: mainc
	./main_check
	
runc10: mainc10
	./main_check10
	
runtry: maintry
	./main_try

%:
	@:
