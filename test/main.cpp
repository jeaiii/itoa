/*
MIT License

Copyright (c) 2017 James Edward Anhalt III - https://github.com/jeaiii/itoa

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <random>

#include "../include/itoa/jeaiii_to_text.h"

void to_string(char* str, bool n) { *jeaiii::to_text_from_integer(str, n) = '\0'; }

void to_string(char* str, char n) { *jeaiii::to_text_from_integer(str, n) = '\0'; }
void to_string(char* str, signed char n) { *jeaiii::to_text_from_integer(str, n) = '\0'; }
void to_string(char* str, unsigned char n) { *jeaiii::to_text_from_integer(str, n) = '\0'; }

void to_string(char* str, int n) { *jeaiii::to_text_from_integer(str, n) = '\0'; }
void to_string(char* str, short n) { *jeaiii::to_text_from_integer(str, n) = '\0'; }
void to_string(char* str, long n) { *jeaiii::to_text_from_integer(str, n) = '\0'; }
void to_string(char* str, long long n) { *jeaiii::to_text_from_integer(str, n) = '\0'; }

void to_string(char* str, unsigned int n) { *jeaiii::to_text_from_integer(str, n) = '\0'; }
void to_string(char* str, unsigned short n) { *jeaiii::to_text_from_integer(str, n) = '\0'; }
void to_string(char* str, unsigned long n) { *jeaiii::to_text_from_integer(str, n) = '\0'; }
void to_string(char* str, unsigned long long n) { *jeaiii::to_text_from_integer(str, n) = '\0'; }

bool check(const char* b, uint64_t n) {
    uint64_t u = 0;
    for (; *b; ++b) u = u * 10 + (*b - '0');
    return u == n;
}

int failure = 0;

void same(uint64_t n)
{
    char text[32];
    to_string(text, n);
    if (!check(text, n)) {
        std::cout << "FAILURE: " << text << " != " << n << "\n";
        failure = 1;
    }
}

template <typename T>
void show(T n) {
    char text[32];
    to_string(text, n);
    std::cout << text << "\n";
}

template<class T>
void test(T n)
{
    show(n);
    same(n);
}

int main()
{
#if 0
    uint64_t i = 0;
    do {
        uint32_t n = uint32_t(i);
        same(n);
        i += 1;
    } while (i < 1ULL << 32);
#endif

#if 0
    // Eausted tests for 64bits are impossible,
    // so test upper 32bits only
    // TODO: fill lower 32bits with random value
    uint64_t i = 0;
    uint64_t tick = 1024*1024*16;
    do {
        uint64_t n = (i << 32);
        same(n);
        if ((i % tick) == 0) {
           std::cout << n << " ";
           show(n);
          
           std::cout << "tested " << i << " of " << (1ull << 32ull) << "\n";
        }
        i += 1;
    } while (i < 1ULL << 32);
#endif

    // test all powers of 2 and 10, -1, +1, +5
    for (int b : { 2, 10 })
        for (uint64_t u = 1, p = u; u >= p; p = u, u *= b)
        {
            test(u - 1);
            test(u);
            test(u + 1);
            test(u + 5);
        }

    uint32_t tests[] = {
        4294967294,
        4294967295,
    };

    for (auto u : tests)
        test(u), test(u);

    test(-1);
    test(1 << 31);
    test(0x7fffffff);
    test(-0x7fffffff - 1);

    test(1000000000900000000ULL);
    test(1000000000800000001ULL);
    test(1000000000700000002ULL);
    test(1000000000600000003ULL);
    test(1000000000500000004ULL);
    test(1000000000400000005ULL);
    test(1000000000300000006ULL);
    test(1000000000200000007ULL);
    test(1000000000100000008ULL);
    test(1000000000000000009ULL);

    test(999010000000ULL);
    test(999010000001ULL);
    test(999010000009ULL);

    test(99909000000ULL);
    test(99909000001ULL);
    test(99909000009ULL);

    test(99909000009LL);
    test(-99909000009LL);

    test(17999999999999999999ULL);

    test(5999999999999999999LL);
    test(-5999999999999999999LL);

    return failure + 1;
}
