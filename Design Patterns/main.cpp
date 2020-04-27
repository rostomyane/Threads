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

int main() {
	BuilderFacets::Person p = BuilderFacets::Person::create().lives().at("somewhere").withPostCode("e149ja").in("London").works().at("GS").asA("VP");
	int a;
}