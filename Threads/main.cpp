#include "Experimental.h"

int main()
{
	std::future<void> f = std::async(std::launch::deferred | std::launch::async, e);
//	f.get();
	return 0;
}