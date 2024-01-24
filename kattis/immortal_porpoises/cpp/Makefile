CXX := clang++
CXXFLAGS := -std=c++2a -O3 -Wall -Wextra -Wpedantic

all:
	$(CXX) $(CXXFLAGS) main.cpp -o main

test:
	$(CXX) $(CXXFLAGS) main.cpp -o main
	$(shell echo ./../../../build/test main ../inputs ../outputs ../logs)
