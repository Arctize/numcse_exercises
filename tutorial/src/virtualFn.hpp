//-----------------------------
// Virtual Functions

class Base1 { // Non-abstract Base Class

public:
	
	void nonVirtualFn() {
		std::cout << "Non-virtual function in Base1" << std::endl;
	}
	
	virtual void virtualFn() {
		std::cout << "Virtual function in Base1" << std::endl;
	}

};


class Base2 { // Abstract Base Class

public:

	virtual void pureVirtualFn() = 0;

};


class Derived : public Base1, public Base2 { // Derived from Base1, Base2
	
public:

	void nonVirtualFn() {
		std::cout << "Non-virtual function in Derived" << std::endl;
	}
	
	// overrides the virtual function from Base1 for an object of "Derived"
	void virtualFn() {
		std::cout << "Virtual function in Derived" << std::endl;
	}
	
	void pureVirtualFn () {
		std::cout << "Pure virtual function defined in Derived" << std::endl;
	}

};

//--------------//
// Test routine //
//--------------//

// working with derived classes using base class pointers
// non-virtual, virtual and pure virtual functions
void test3 () {

	Base1 *bBase = new Base1;
	Base1 *bDerived = new Derived;
	
	bBase->nonVirtualFn();
	bBase->virtualFn();
	std::cout << "\n";
	
	bDerived->nonVirtualFn();
	bDerived->virtualFn();
	
	delete bBase;
	delete bDerived;

}

// end of header file
