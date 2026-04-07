CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wall

all: code

code: main.cpp
	$(CXX) $(CXXFLAGS) -o code main.cpp

clean:
	rm -f code
