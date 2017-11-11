#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#if 0
#define D(N,B) { b += N; t = (1LL << (32 + B)) / uint32_t(1e##N) + 1; t *= i; (B) && (t += 1LL << (B)); i = uint32_t(t >> (32 + B)); n = uint32_t(t >> (B)); goto i##N; }

char* itoa(char *b, uint32_t i)
{
    uint32_t n;
    uint64_t t;

    if (i < 100) {
        if (i < 10) goto i0;
        D(1, 0)
    }

    if (i < 1000000)
    {
        if (i < 10000)
        {
            if (i < 1000)
                D(2, 0)
                D(3, 0)
        }
        if (i < 100000)
            D(4, 0)
            D(5, 15)
    }

    if (i < 100000000)
    {
        if (i < 10000000)
            D(6, 18)
            D(7, 21)
    }

    if (i < 1000000000)
        D(8, 24)

    {
        b += 9; t = (1LL << (32 + 29)) / uint32_t(1e9) + 0; t *= i; t += 1LL << (31); i = uint32_t(t >> (32 + 29)); n = uint32_t(t >> (29));
    }

#define T { t = 10; t *= n; i = uint32_t(t >> 32); n = uint32_t(t); }

    b[-9] = i + '0'; T
        i8 : b[-8] = i + '0'; T
        i7 : b[-7] = i + '0'; T
        i6 : b[-6] = i + '0'; T
        i5 : b[-5] = i + '0'; T
        i4 : b[-4] = i + '0'; T
        i3 : b[-3] = i + '0'; T
        i2 : b[-2] = i + '0'; T
        i1 : b[-1] = i + '0'; T
        i0 : b[0] = i + '0';
    b[1] = 0;

    return b + 1;
}

char* itoa(char* b, int32_t i)
{
    if (i < 0)
        *b++ = '-', i = -i;
    return itoa(b, uint32_t(i));
}
#endif

extern void i32toa_jeaiii(int32_t i, char* b);
extern void u32toa_jeaiii(uint32_t i, char* b);

void itoa(char* b, int32_t i) { return i32toa_jeaiii(i, b); }
void itoa(char* b, uint32_t i) { return u32toa_jeaiii(i, b); }

bool same(uint32_t i)
{
    char a[32];
    itoa(a, i);

    char b[32], *c=b+32;

    *--c = 0;
    do {
        *--c = i % 10 + '0';
    } while (i /= 10);

    if (strcmp(a, c)) {
        std::cout << a << "!=" << c << '\n';
        return false;
    }
    return true;

    //return std::to_string(i) == text;
}

void main()
{
    char text[32];

    uint64_t i = 0;
    do {
        uint32_t n = uint32_t(i);
        if (!same(n))
            itoa(text, n), std::cout << i << "!=" << text << "\n", __debugbreak();
        i += 1;
    } while (i < 1LL << 32);

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
