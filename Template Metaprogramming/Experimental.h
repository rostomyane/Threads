#pragma once
#include <type_traits>
#include <utility>

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
}