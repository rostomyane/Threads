#include "FirstSecondThird.h"

int main()
{
	Foo t;

	std::thread t3{ &Foo::third, &t,th };
	std::thread t2{&Foo::second, &t,s};
	std::thread t1{ &Foo::first, &t ,f};

	t3.join();
	t2.join();
	t1.join();

	return 0;
}