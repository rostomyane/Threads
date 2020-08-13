#include "Experimental.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <tuple>

struct Customer {
	std::string first;
	std::string second;
	int id;
public:
	template<typename S1, typename S2 = std::string,
		typename = std::enable_if_t<!std::is_constructible_v<std::decay_t<S1>,Customer>>>
	Customer(S1&& s1, S2&& s2 = "", int i = 0)
		:first(std::forward<S1>(s1)), second(std::forward<S2>(s2)),id(i)
	{}
};




int main()
{

}