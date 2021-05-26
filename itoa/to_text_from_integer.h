#pragma once
/*
MIT License

Copyright(c) 2021 James Edward Anhalt III - https://github.com/jeaiii/itoa

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

// converting an integer to text quickly: i.e. division is bad, only do it once, and even then, do it with multiplication
// 
// 1. form a 7.32 bit fixed point numner: t = u * 2^32 / 10^log10(u)
// 2. convert 2 digits at a time [00, 99] by lookup from the integer portion of the fixed point number (the upper 32 bits)
// 3. multiply the fractional part (the lower 32 bits) by 100 and repeat until 1 or 0 digits left
// 4. if 1 digit left mulptipy by 10 and convert it (add '0')
// 
// N == log10(u)
// finding N by binary search for a 32bit number N = [0, 9]
// this is fast and selected such 1 & 2 digit numbers are faster (2 branches) than long numbers (4 branches) for the 10 cases
//          
//      /\____________
//     /  \______     \______
//    /\   \     \     \     \
//   0  1  /\    /\    /\    /\
//        2  3  4  5  6  7  8  9
//
// there are other possilities but this is a nice balance and beats out all the count trailing zero methods of computing log10(u)
// WHEN combined with actually converting the number to text (i.e. not tested in isolation without the random branch)

// fully unrolled code is generated to convert numbers for each length with no further branching
// there is a conditional trick for not branching on the final compare that reduces the cases from 10 to 5, but I could never make it faster
// 
// math details
// 
// if (log10(u) >= 5 we need extra precision so shift up and then down by log10(u) * log2(10) ~= N * 53 / 16
// expressions like `N / 5` below are shorthand for `N >= 5 ? 1 : 0` and allow all compilers to generate these constants at compile time even when unoptimized
// `N / 5 * N * 53 / 16` is read as: `N >= 5 ? N * 53 / 16 : 0`
// need to round up after multiplication: `+1`
// if N == 6 or 7 we need a little more help rounding so another +1: `+ N / 6 - N / 8` === `N >= 6 && N < 8 ? 1 : 0`
// for N >= 6 we need to round after the multiplication with a +4: `+= N / 6 * 4` === `+= n >= 6 ? 4 : 0`
//
// how fast is this? the fastest I've ever seen with accurate benchmarks
// 1. good benchmarks are hard
// 2. random 32bit binary data is not representative of real world data, ~3/4 of the numbers would haved 10 digits. still the fastest...
// 3. uniform random length decimal numbers (1 to 10 digits) aren't real world either, but are the worst case for binary search, still the fastest...
// 4. fixed length decimal numbers provide an insight into how fast each case is, but isn't realistic either, the fastest in every case...
// 5. unless you know you are converting only 10 digit numbers there is no reason to use anything else, except for code size (coming soon)
//
// the template nature of this code allows the compiler to further optimize based on the type
// for example 8bit numbers range from 0-255 so it optimizes down to 3 cases making it even faster
// so if you can "tell" your compiler the range it may optimize even better


namespace jeaiii
{

#ifdef JEAIII_USER_UINT32_T
	using u32 = JEAIII_USER_UINT32_T;
#else
	using u32 = decltype(0xffffffff);
#endif

#ifdef JEAIII_USER_UINT64_T
	using u64 = JEAIII_USER_UINT64_T;
#else
	using u64 = decltype(0xffffffffffffffff);
#endif

	static_assert(u32(-1) > 0, "u32 must be unsigned");
	static_assert(u32(0xffffffff) + u32(1) == u32(0), "u32 must be 32 bits");
	static_assert(u64(-1) > 0, "u64 must be unsigned");
	static_assert(u64(0xffffffffffffffff) + u32(1) == u32(0), "u64 must be 64 bits");

	constexpr auto digits_00_99 =
		"00010203040506070809" "10111213141516171819" "20212223242526272829" "30313233343536373839"	"40414243444546474849"
		"50515253545556575859" "60616263646566676869" "70717273747576777879" "80818283848586878889"	"90919293949596979899";

	struct pair { char t, o; };

#define JEAIII_W(I, U) *(pair*)&b[I] = *(pair*)&digits_00_99[(U) * 2]
#define JEAIII_A(I, N) t = (u64(1) << (32 + N / 5 * N * 53 / 16)) / u32(1e##N) + 1 + N / 6 - N / 8, t *= u, t >>= N / 5 * N * 53 / 16, t += N / 6 * 4, JEAIII_W(I, t >> 32)
#define JEAIII_S(I) b[I] = char(u64(10) * u32(t) >> 32) + '0'
#define JEAIII_D(I) t = u64(100) * u32(t), JEAIII_W(I, t >> 32)

#define JEAIII_C0(I) b[I] = char(u) + '0'
#define JEAIII_C1(I) JEAIII_W(I, u)
#define JEAIII_C2(I) JEAIII_A(I, 1), JEAIII_S(I + 2)
#define JEAIII_C3(I) JEAIII_A(I, 2), JEAIII_D(I + 2)
#define JEAIII_C4(I) JEAIII_A(I, 3), JEAIII_D(I + 2), JEAIII_S(I + 4)
#define JEAIII_C5(I) JEAIII_A(I, 4), JEAIII_D(I + 2), JEAIII_D(I + 4)
#define JEAIII_C6(I) JEAIII_A(I, 5), JEAIII_D(I + 2), JEAIII_D(I + 4), JEAIII_S(I + 6)
#define JEAIII_C7(I) JEAIII_A(I, 6), JEAIII_D(I + 2), JEAIII_D(I + 4), JEAIII_D(I + 6)
#define JEAIII_C8(I) JEAIII_A(I, 7), JEAIII_D(I + 2), JEAIII_D(I + 4), JEAIII_D(I + 6), JEAIII_S(I + 8)
#define JEAIII_C9(I) JEAIII_A(I, 8), JEAIII_D(I + 2), JEAIII_D(I + 4), JEAIII_D(I + 6), JEAIII_D(I + 8)

#define JEAIII_L(N, A, B) u < u32(1e##N) ? A : B
#define JEAIII_L09(F) JEAIII_L(2, JEAIII_L(1, F(0), F(1)), JEAIII_L(6, JEAIII_L(4, JEAIII_L(3, F(2), F(3)), JEAIII_L(5, F(4), F(5))), JEAIII_L(8, JEAIII_L(7, F(6), F(7)), JEAIII_L(9, F(8), F(9)))))
#define JEAIII_L03(F) JEAIII_L(2, JEAIII_L(1, F(0), F(1)), JEAIII_L(3, F(2), F(3)))

#define JEAIII_K(N) (JEAIII_C##N(0), b + N + 1)
#define JEAIII_KX(N) (JEAIII_C##N(0), u = x, JEAIII_C7(N + 1), b + N + 9)
#define JEAIII_KYX(N) (JEAIII_C##N(0), u = y, JEAIII_C7(N + 1), u = x, JEAIII_C7(N + 9), b + N + 17)

	template<bool B, class T, class F> struct _cond { using type = F; };
	template<class T, class F> struct _cond<true, T, F> { using type = T; };
	template<bool B, class T, class F> using cond = typename _cond<B, T, F>::type;

	template<class T> inline char* to_text_from_integer(char* b, T i)
	{
		u64 t = u64(i);

		if (i < T(0))
			t = u64(0) - t, b[0] = '-', ++b;

		u32 u = cond<T(1) != T(2), cond<sizeof(T) != 1, cond<sizeof(T) != sizeof(short), u32, unsigned short>, unsigned char>, bool>(t);

		// if our input type fits in 32bits, or its value does, ctreat as 32bit (the line above ensures the compiler can still know the range limits of the input type)
		// and optimize out cases for small integer types (if only c++ had a builtin way to get the unsigned type from a signed type)
		if (sizeof(i) <= sizeof(u) || u == t)
			return JEAIII_L09(JEAIII_K);

		// more than 32bits? break off chucks of 8 digits from end
		u32 x = t % 100000000u;
		u = u32(t /= 100000000u);

		// t / 10^8 (fits in 32 bit), t % 10^8 -> ~17.5 digits
		if (u == t)
			return JEAIII_L09(JEAIII_KX);

		// t / 10^16 (1-4 digits), t / 10^8 % 10^8, t % 10^8
		// actaully 2-4 digits since all ~17.5 digits numbers are handled above, future optimization...
		u32 y = t % 100000000u;
		u = u32(t / 100000000u);
		return JEAIII_L03(JEAIII_KYX);
	}

	inline char* to_text(char text[], signed char i) { return to_text_from_integer(text, i); }
	inline char* to_text(char text[], unsigned char i) { return to_text_from_integer(text, i); }
	inline char* to_text(char text[], short i) { return to_text_from_integer(text, i); }
	inline char* to_text(char text[], unsigned short i) { return to_text_from_integer(text, i); }
	inline char* to_text(char text[], int i) { return to_text_from_integer(text, i); }
	inline char* to_text(char text[], unsigned int i) { return to_text_from_integer(text, i); }
	inline char* to_text(char text[], long i) { return to_text_from_integer(text, i); }
	inline char* to_text(char text[], unsigned long i) { return to_text_from_integer(text, i); }
	inline char* to_text(char text[], long long i) { return to_text_from_integer(text, i); }
	inline char* to_text(char text[], unsigned long long i) { return to_text_from_integer(text, i); }
}

#undef JEAIII_W
#undef JEAIII_A
#undef JEAIII_S
#undef JEAIII_D
#undef JEAIII_C0
#undef JEAIII_C1
#undef JEAIII_C2
#undef JEAIII_C3
#undef JEAIII_C4
#undef JEAIII_C5
#undef JEAIII_C6
#undef JEAIII_C7
#undef JEAIII_C8
#undef JEAIII_C9
#undef JEAIII_L
#undef JEAIII_L09
#undef JEAIII_L03
#undef JEAIII_K
#undef JEAIII_KX
#undef JEAIII_KYX
