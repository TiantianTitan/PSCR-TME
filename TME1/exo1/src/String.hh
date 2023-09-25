// String.hh 
// Question 10: Implanter la classe String conformément aux instructions du TD 1.

#pragma once

#include <cstdio>

namespace pr{
    class String{
        const char* str;
        public:
            String(const char* ori = "");
            size_t length() const;
    };
}