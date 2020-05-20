#include <iostream.h>

////////////////
// foo2: now I've added a derived class, A1

class A {
protected:
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
	x=0;
}

//////////////////
// Now I've added a derived class with constructor, destructor
// and three virtual function overrides.
//
class A1 : public A {
public:
	A1();
	~A1();
	virtual void func1() { cout<<4; }
	virtual void func2() { cout<<5; }
	virtual void func3() { cout<<6; }
};

A1::A1()
{
	x=10;
}

A1::~A1()
{
	x=10;
}

void main()
{
	// Note: Need to use ptr to A (pa) since if you write a.func1()
	// the compiler is too smart and generates a direct (static) fn call.
	A1 a1;
	A* pa = &a1;
	pa->func1();
	pa->func2();
	pa->func3();
}
