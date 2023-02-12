all: build

build:
	g++ -o cs424p1 -std=c++17 *.cpp *.cc *.C

test: build
	./cs424p1

clean:
	rm a.out
	rm cs424p1