#include <iostream.h>

////////////////
// foo4: Now A uses __declspec(novtable). The compiler does not generate
// a vtable for A, nor vtable initialization code in constructor/destructor.
//
class __declspec(novtable) A {
protected:
	int x;
public:
	A();
	~A();
	virtual void func1()=0; // base class fns are pure
	virtual void func2()=0;
	virtual void func3()=0;
};

A::A()
{
	x=0;
}

A::~A()
{
	x=0;
}

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
	// Need to use ptr to A (pa) since if you write a.func1()
	// the compiler is too smart and generates a direct (static) fn call.
	A1 a1;
	A* pa = &a1;
	pa->func1();
	pa->func2();
	pa->func3();
}
