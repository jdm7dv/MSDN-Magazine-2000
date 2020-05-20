#include <iostream.h>

//////////////////
// Typical class with constructor, destructor and three virtual functions.
//
class A {
	int x;
public:
	A();
	~A();
	virtual void func1() { cout<<1; }
	virtual void func2() { cout<<2; }
	virtual void func3() { cout<<3; }
};

A::A()
{
	x=0;
}

A::~A()
{
}

void main()
{
	// Note: Need to use ptr to A (pa) since if you write a.func1()
	// the compiler is too smart and generates a direct (static) fn call.
	A a;
	A* pa = &a;
	pa->func1();
	pa->func2();
	pa->func3();
}
