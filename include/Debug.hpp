/**
 * Convenient debugging macros.
 * Especially useful for ACM-style programming.
 */

#ifndef ACM_DEBUG_HPP_INCLUDED
#define ACM_DEBUG_HPP_INCLUDED

#include <iostream>
#include <vector>

namespace acm {
    /**
     * Usually one should not use functions below directly,
     * but call them with DEBUG(...) and ADEBUG(a, n) macros.
     */
    inline void debug_out() {
        std::cerr << std::endl;
    } 

    template<typename T1, typename... T2> void debug_out(T1 x, T2... y) {
        std::cerr << ' ' << x;
        debug_out(y...);
    }

    template<typename T> void adebug_out(T* a, int n) {
        for (int i = 0; i < n; ++i)
            std::cerr << a[i] << ' ';
        std::cerr << std::endl;
    }
}

/**
 * DEBUG(...) prints the names and then the values of all given arguments to stderr.
 */
#define DEBUG(...) std::cerr << "[" << #__VA_ARGS__ << "]:", acm::debug_out(__VA_ARGS__)

/**
 * ADEBUG(a, n) prints the name and then the contents of an array, given its size.
 */
#define ADEBUG(a, n) std::cerr << #a << ": ", acm::adebug_out(a, n)

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& stream, const std::pair<T1, T2>& p) {
    return stream << p.first << ' ' << p.second;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& v) {
    for (auto& e : v)
        stream << e << ' ';
    return stream;
}

#endif // ACM_DEBUG_HPP_INCLUDED include guard
