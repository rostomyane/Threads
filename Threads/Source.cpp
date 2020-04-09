#include "Experimental.h"

int main()
{
	std::thread t1(f);
	std::thread t2(g);

	t1.join();
	t2.join();

	return 0;
}