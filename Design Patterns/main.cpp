#include "Builder.h"

enum class colour {red,black,green};
enum class size {small,medium,large};

class Item 
{
	std::string _name;
	colour _c;
	size _s;
public:
	Item(std::string n, colour c, size s)
		:_name{ n }, _c(c), _s(s){}
};

using namespace html;

template<int N>
class factorial {
public:
	static const int result = N * factorial<N - 1>::result;
};

template<>
class factorial<0> {
public:
	static const int result = 1;
};

int main() {
	int a = factorial<5>::result;
	std::cout << a << std::endl;
}