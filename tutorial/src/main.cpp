// This code should be used along with tutorial presentation to explain basic concepts in C++

#include <iostream>
#include "classes.hpp"
#include "virtualFn.hpp"
#include "templates.hpp"

// Values, pointers and references

void f1(int x) {
	x = 10;
}

void f2(int& x) {
	x = 15;
}

void f3(int *x) {
	*x = 20;
}

void test1 () {

	int x = 5;
	f1(x); std::cout << x << std::endl;
	f2(x); std::cout << x << std::endl;
	f3(&x); std::cout << x << std::endl;

}

int main(int argc, char **argv) {

	if(argc==1 || argc>2) return 0;
	int n = std::stoi(argv[1]);
	
	if (n==1) test1();
	else if (n==2) test2(); // classes and inheritance
	else if (n==3) test3(); // virtual functions
	else if (n==4) test4(); // function templates
	else if (n==5) test5(); // class templates
	
	return 1;
}

// end of file
