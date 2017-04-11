//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <unordered_set>

// template <class Value, class Hash = hash<Value>, class Pred = equal_to<Value>,
//           class Alloc = allocator<Value>>
// class unordered_set

// size_type count(const key_type& k) const;

#include <unordered_set>
#include <string>
#include <cassert>

#include "min_allocator.h"

int main()
{
    {
        typedef std::unordered_set<int> C;
        typedef int P;
        P a[] =
        {
            P(10),
            P(20),
            P(30),
            P(40),
            P(50),
            P(50),
            P(50),
            P(60),
            P(70),
            P(80)
        };
        const C c(std::begin(a), std::end(a));
        assert(c.count(30) == 1);
        assert(c.count(50) == 1);
        assert(c.count(5) == 0);
    }
#if TEST_STD_VER >= 11
    {
        typedef std::unordered_set<int, std::hash<int>, std::equal_to<int>, min_allocator<int>> C;
        typedef int P;
        P a[] =
        {
            P(10),
            P(20),
            P(30),
            P(40),
            P(50),
            P(50),
            P(50),
            P(60),
            P(70),
            P(80)
        };
        const C c(std::begin(a), std::end(a));
        assert(c.count(30) == 1);
        assert(c.count(50) == 1);
        assert(c.count(5) == 0);
    }
    {
        std::unordered_set<std::string, std::hash<>, std::equal_to<>> const s = {"one", "two", "three", "four"};
        std::string_view str_v = "three";
        assert(s.count(str_v) == 1);
        assert(s.count("three") == 1);
        char c1[] = "three";
        char c2[] = {'t','h','r','e','e','\0'};
        assert(s.count(c1) == 1);
        assert(s.count(c2) == 1);
        assert(s.count(std::string_view{"two"}) == 1);
        assert(s.count(std::string_view{"TWO"}) == 0);
    }
#endif
}
