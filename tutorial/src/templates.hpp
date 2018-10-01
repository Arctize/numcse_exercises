//-----------------------------
// Templates

int product(int a, int b) {
	int c = a*b;
	std::cout << "a*b= " << c << std::endl;
	return c;
}


// overloaded function
double product(double a, double b) {
	double c = a*b;
	std::cout << "a=" << a << ",\tb=" << b << ",\ta*b=" << c << "\n" << std::endl;
	return c;
}


// function template
template<typename T>
T productTemp1(T a, T b) {
	T c = a*b;
	std::cout << "a=" << a << ",\tb=" << b << ",\ta*b=" << c << "\n" << std::endl;
	return c;
}


// function template with multiple types
template<typename T1, typename T2, typename T3>
T3 productTemp2(T1 a, T2 b) {
	T3 c = a*b;
	std::cout << "a=" << a << ",\tb=" << b << ",\ta*b=" << c << "\n" << std::endl;
	return c;
}


// class template
template<typename T>
class System {

public:

	System(T inData) : data(inData) {}
	
	void setData (T inData) {
		data = inData;
	}

	T getData () {
		return data;
	}
	
	void processData() {
		if (data >= 1)
			std::cout << "Well, this system is wrecked." << std::endl;
	}
	
private:
	
	T data;
};

//--------------//
// Test routine //
//--------------//

// function templates
void test4() {

	int a1 = 9;
	int b1 = 7;
	
	double a2 = 2.5;
	double b2 = 3.5;
	
	productTemp1(a1,b1);
	productTemp1(a2,b2);

	productTemp1<int>(a1,b1);
	productTemp1<double>(a2,b2);
	productTemp1<double>(a1,b2);
	
	productTemp2<double,int,double>(a2,b1);

}

// class templates
void test5() {

	double x = 1.0;
	System<double> earth(x);
	earth.processData();

}

// end of header file
