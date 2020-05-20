#include <iostream.h>

//////////////////
// foo5: Now A implements the virtual functions, and is concrete--but I
// can still use __declspec(novtable) because instances of A are never
// created and A's constructor/destructor don't call any virtual fns.
//
class __declspec(novtable) A {
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
// A1 inherits all virtual fns from A.
//
class A1 : public A {
public:
	A1();
	~A1();
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
	// Need to use ptr to A (pa) since if you write a.func1()
	// the compiler is too smart and generates a direct (static) fn call.
	A1 a1;
	A* pa = &a1;
	pa->func1();
	pa->func2();
	pa->func3();
}
