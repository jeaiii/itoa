#include <stdint.h>

template <int N> __forceinline void digits(char *b, uint64_t t)
{
    b[0] = char(t >> 32) + '0';
    digits<N - 1>(++b, 10ULL * uint32_t(t));
}

#define Z(d) (void)(*(uint16_t*)b = uint16_t(d) + '0')

template <> __forceinline void digits<0>(char *b, uint64_t t)
{
    Z(t >> 32);
}

#define A(N) digits<N>(b, ((1ULL << 32) / uint32_t(1e##N) + 1) * i)
#define B(N) digits<N>(b, (((1ULL << (32+N*3)) / uint32_t(1e##N) + 1) * i + (1ULL << (N*3))) >> (N*3))

void xu32toa_jeaiii(uint32_t i, char *b)
{
    i < 100 ?
        i < 10 ? Z(i) : A(1) :
        i < 1000000 ?
            i < 10000 ?
                i < 1000 ? A(2) : A(3) :
                i < 100000 ? A(4) : B(5) :
            i < 100000000 ?
                i < 10000000 ? B(6) : B(7) :
                i < 1000000000 ? B(8) : digits<9>(b, ((1ULL << (32 + 29)) / uint32_t(1e9) * i + (1ULL << 31)) >> 29);
}

#define TX *b++ = char(t >> 32) + '0', t = 10ULL * uint32_t(t)
#define T0(I) *(uint16_t*)b++ = uint16_t(I) + '0', (void)0
#define T1 TX, T0(t >> 32)
#define T2 TX, T1
#define T3 TX, T2
#define T4 TX, T3
#define T5 TX, T4
#define T6 TX, T5
#define T7 TX, T6
#define T8 TX, T7
#define T9 TX, T8
#define T(N,B) (t = (1ULL << (32 + B)) / uint32_t(1e##N) + 1, t *= i, t += !!B << (B), t >>= B, T##N)

void u32toa_jeaiii(uint32_t i, char *b)
{
    uint64_t t;

    i < 100 ?
        i < 10 ? T0(i) : T(1, 0) :
        i < 1000000 ?
            i < 10000 ?
                i < 1000 ? T(2, 0) : T(3, 0) :
                i < 100000 ? T(4, 0) : T(5, 15) :
            i < 100000000 ?
                i < 10000000 ? T(6, 18) : T(7, 21) :
                i < 1000000000 ? T(8, 24) : (t = (1LL << (32 + 29)) / uint32_t(1e9) + 0, t *= i, t += 1ULL << 31, t >>= 29, T9);
}

void i32toa_jeaiii(int32_t i, char* b)
{
    if (i < 0)
        *b++ = '-', i = -i;
    u32toa_jeaiii(uint32_t(i), b);
}

void u64toa_jeaiii(uint64_t n, char* b)
{
    if (uint32_t(n >> 32) == 0)
        return u32toa_jeaiii(uint32_t(n), b);

    uint64_t t = n / 100000000;

    if (uint32_t(t >> 32) == 0)
    {
        u32toa_jeaiii(uint32_t(t), b);
        while (*++b);
    }
    else
    {
        u32toa_jeaiii(uint32_t(t / 100000000), b);
        while (*++b);
        uint32_t i = t % 100000000;
        T(7, 21);
    }

    uint32_t i = n % 100000000;
    T(7, 21);
}

void i64toa_jeaiii(int64_t i, char* b)
{
    if (i < 0)
        *b++ = '-', i = -i;
    u64toa_jeaiii(uint64_t(i), b);
}
