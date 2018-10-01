// Classes and Inheritance

// Base class: Polygon
class Polygon {

public:
	
	Polygon() {} // default constructor
	
	Polygon (double w, double h) : width(w), height(h) {} // constructor 2
	
	//Polygon (double w, double h) {
	//	set(w,h);
	//}
	
	void set(double w, double h) {
		width = w;
		height = h;
	}

protected:
//private:
	
	double width, height;

};

// Derived Class: Triangle
class Triangle : public Polygon {

public:

	double area() {
		return (width*height/2);
	}

};

// Derived Class: Rectangle
class Rectangle : public Polygon {

public:
	
	double area() {
		return (width*height);
	}

};

//--------------//
// Test routine //
//--------------//

void test2 () {

	Triangle S1;	S1.set(3.0,4.0);
	Rectangle S2;	S2.set(3.0,4.0);
	std::cout << "Area of triangle S1: " << S1.area() << std::endl;
	std::cout << "Area of rectangle S2: " << S2.area() << std::endl;

}

// end of header file
