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



int main() {
	HTMLBuilder builder{"ul"};
	builder.addChild("li", "hello");
	builder.addChild("li", "world");
	std::cout << builder.str();
}