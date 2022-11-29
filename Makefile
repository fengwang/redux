CXX = g++
all: test.cpp
	$(CXX) -o test test.cpp -std=c++20 -Wall -Wextra -Ofast -flto=auto  -funroll-all-loops -pipe -march=native

