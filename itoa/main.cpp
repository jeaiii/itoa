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

void i32toa_jeaiii(int32_t i, char* b);
void u32toa_jeaiii(uint32_t i, char* b);

void itoa(char* b, int32_t i) { i32toa_jeaiii(i, b); }
void itoa(char* b, uint32_t i) { u32toa_jeaiii(i, b); }

bool check(const char* b, uint32_t n) {
    uint32_t u = 0;
    for (; *b; ++b) u = u * 10 + (*b - '0');
    return u == n;
}

void same(uint32_t n)
{
    char text[32];
    itoa(text, n);
    if (!check(text, n)) {
        std::cout << "FAILURE: " << text << " != " << n << "\n";
    }
}

template <typename T>
void show(T n) {
    char text[32];
    itoa(text, n);
    std::cout << text << "\n";
}

int main()
{
    uint64_t i = 0;
    do {
        uint32_t n = uint32_t(i);
        same(n);
        i += 1;
    } while (i < 1ULL << 32);

    show(0);
    show(1);
    show(9);
    show(10);
    show(99);
    show(100);
    show(999);
    show(1000);
    show(9999);
    show(10000);
    show(99999);
    show(100000);
    show(999999);
    show(1000000);
    show(9999999);
    show(10000000);
    show(99999999);
    show(100000000);
    show(123456789);
    show(999999999);
    show(1000000000);
    show(4294967295U);
    show(-1);
    show(1 << 31);
    show(0x7fffffff);
    show(-0x7fffffff - 1);

    return 0;
}
