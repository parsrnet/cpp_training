CXX=clang++
CFLAGS=-std=c++17

matrix-multiplication: matrix-multiplication.cpp matrix.hpp
	$(CXX) $(CFLAGS) matrix-multiplication.cpp -o matrix-multiplication

.PHONY: clean

clean:
	rm -f matrix-multiplication
