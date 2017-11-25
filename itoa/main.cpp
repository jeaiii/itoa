/*
MIT License

Copyright (c) 2017 James Edward Anhalt III (jeaiii)
https://github.com/jeaiii/itoa

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

bool same(uint32_t i)
{
    char a[32];
    itoa(a, i);
#if 1
    char b[32], *c=b+32;

    *--c = 0;
    uint32_t n = i;
    do {
        *--c = i % 10 + '0';
    } while (i /= 10);
    i = n;

    if (strcmp(a, c)) {
#else
    std::string c = std::to_string(i);
    if (a != c) {
#endif
        std::cout << "FAILURE: " << a << " != " << i << " : " << c << "\n";
        __debugbreak();
        return false;
    }
    return true;
}

void main()
{
    char text[32];

    uint64_t i = 0;
    do {
        uint32_t n = uint32_t(i);
        same(n);
        i += 1;
    } while (i < 1ULL << 32);

    itoa(text, 0); std::cout << text << "\n";
    itoa(text, 1); std::cout << text << "\n";
    itoa(text, 9); std::cout << text << "\n";
    itoa(text, 10); std::cout << text << "\n";
    itoa(text, 99); std::cout << text << "\n";
    itoa(text, 100); std::cout << text << "\n";
    itoa(text, 999); std::cout << text << "\n";
    itoa(text, 1000); std::cout << text << "\n";
    itoa(text, 9999); std::cout << text << "\n";
    itoa(text, 10000); std::cout << text << "\n";
    itoa(text, 99999); std::cout << text << "\n";
    itoa(text, 100000); std::cout << text << "\n";
    itoa(text, 999999); std::cout << text << "\n";
    itoa(text, 1000000); std::cout << text << "\n";
    itoa(text, 9999999); std::cout << text << "\n";
    itoa(text, 10000000); std::cout << text << "\n";
    itoa(text, 99999999); std::cout << text << "\n";
    itoa(text, 100000000); std::cout << text << "\n";
    itoa(text, 123456789); std::cout << text << "\n";
    itoa(text, 999999999); std::cout << text << "\n";
    itoa(text, 1000000000); std::cout << text << "\n";
    itoa(text, 4294967295U); std::cout << text << "\n";
    itoa(text, -1); std::cout << text << "\n";
    itoa(text, 1 << 31); std::cout << text << "\n";
    itoa(text, 0x7fffffff); std::cout << text << "\n";
}
