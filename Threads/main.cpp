#include "LeetCode.h"

class A {
	vector<map<string, string>> v;
};

class B: public A{
	//virtual void f() {}
};

class C : public A {
	//virtual void f() {}
};

class D :public C, public B{

};

int main()
{
	D d;
	C c;
	return 0;
}