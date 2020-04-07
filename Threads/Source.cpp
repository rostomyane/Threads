#include "FirstSecondThird.h"

int main()
{
	Foo t;

	std::thread t3( &Foo::third, &t,f );
	std::thread t2{&Foo::second, &t,s};
	std::thread t1{ &Foo::first, &t,th };

	t3.join();
	t2.join();
	t1.join();

	return 0;
}