#include "Experimental.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

class Customer {
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

template<int N, typename = std::enable_if_t< N >= 0>>
struct factorial 
{
	static const int value = N * factorial<N - 1>::value;	
};

template<>
struct factorial<7> {
	static const int value = 1;
};

int main()
{
	const Customer c("Edo");
	Customer f(c);

	std::cout << factorial<8>::value << std::endl;
}