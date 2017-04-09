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

// const_iterator find(const key_type& k) const;

#include <unordered_set>
#include <string>
#include <string_view>
#include <cassert>

#include "min_allocator.h"

struct dummy_int
{
    static size_t counter;
    int value;
    
    dummy_int(): value{0} { ++counter; }
    dummy_int(int v): value{v} { ++counter; }
    dummy_int(dummy_int const& other): value(other.value) { ++counter; }
    dummy_int(dummy_int&& other): value(other.value) { ++counter; }
    
    operator int () const { return value; }
};

size_t dummy_int::counter = 0;

namespace std
{

template<>
struct hash<dummy_int>
{
    size_t operator ()(dummy_int const& d) const {
        return std::hash<int>{}(d.value);
    }
};

}

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
            P(60),
            P(70),
            P(80)
        };
        const C c(std::begin(a), std::end(a));
        C::const_iterator i = c.find(30);
        assert(*i == 30);
        i = c.find(5);
        assert(i == c.cend());
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
            P(60),
            P(70),
            P(80)
        };
        const C c(std::begin(a), std::end(a));
        C::const_iterator i = c.find(30);
        assert(*i == 30);
        i = c.find(5);
        assert(i == c.cend());
    }
    {
        dummy_int a[] = {10}; // +1
        
        std::unordered_set<dummy_int> const c1{std::begin(a), std::end(a)}; // +1
        assert(dummy_int::counter == 2);
        auto i1 = c1.find(10); // +1
        assert(i1 != c1.end());
        assert(dummy_int::counter == 3);
        
        std::unordered_set<dummy_int, std::hash<>, std::equal_to<>> const c2{std::begin(a), std::end(a)}; // +1
        assert(dummy_int::counter == 4);
        auto i2 = c2.find(10); // +0
        assert(i2 != c2.end());
        assert(dummy_int::counter == 4);
    }
    {
        std::unordered_set<std::string, std::hash<>, std::equal_to<>> const s = {"one", "two", "three", "four"};
        std::string_view str_v = "three";
        std::string str3 = "three";
        std::string str2 = "two";
        assert(s.find(str_v) == s.find(str3));
        assert(s.find(std::string_view{"two"}) == s.find(str2));
        assert(s.find(std::string_view{"TWO"}) == s.end());
    }
#endif
}
