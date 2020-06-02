#pragma once
#include <type_traits>
#include <utility>
#include <string>

namespace experimental {

    template<typename T, typename U>
    std::common_type_t<T, U> max(T const& a, U const& b) {
        return b < a ? a : b;
    }

    template <typename T1, typename T2>
    inline std::pair<std::decay_t<T1>,std::decay_t<T2> >
        make_pair(T1&& x, T2&& y)
    {
        return std::pair<std::decay_t<T1>, std::decay_t<T2>> 
            (std::forward<T1>(x), std::forward<T2>(y));
    }

	class Customer {
		std::string first;
		std::string second;
		int id;
	public:
		template<typename S1, typename S2 = std::string,
			typename = std::enable_if_t<!std::is_constructible_v<std::decay_t<S1>, Customer>>>
			Customer(S1&& s1, S2&& s2 = "", int i = 0)
			:first(std::forward<S1>(s1)), second(std::forward<S2>(s2)), id(i)
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
}