# itoa - Fast integer to ascii / integer to string conversion
![windows](https://github.com/jeaiii/itoa/actions/workflows/msbuild.yml/badge.svg)
- newest version: [jeaiii_to_text.h](include/itoa/jeaiii_to_text.h)
- **0 dependency** header only - as in absolutely no dependencies on ANY other headers
- **fast** - fasted tested on vs2019 in x86 and x64 for all digit lengths, uniform random bits, and uniform random digit lengths (latest version is even **25%** faster than before) using https://github.com/jeaiii/itoa-benchmark
- **small** - simple code that produces good compiled code even in debug builds (no nested functions)
- compiles on clang, msvc, and gcc as **C++11** or later
- written to specialize well based on integer type (size, signed, unsigned) and possible values determined at compile time
- Thanks to [Junekey Jeon](https://github.com/jk-jeon) for the great write-up [here](https://jk-jeon.github.io/posts/2022/02/jeaiii-algorithm/), providing better insight into more rigorous mathematical foundations which eliminated an unneeded addition, and renewing my interest into making an even faster version

## **Check it out vs. [{fmt}](https://github.com/fmtlib/fmt) on [godbolt.org](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAzFykAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn4JdpgO6bX1BIVhkdFxrXUNTdlD3b3FpYMAlLaoXsTI7BzmscHI3lgA1CaxblEMyAgs9QDWAPSHx6fEZwB0CHvYJhoAghcX29qYTHj/F0IqCY2wAbgptlQWARXh8vggCAREgoQJ9gIQEF4Ivc0CwLj8/gCgUxYaSzOsjltMLt9lCCBdcYk6JhHs8yRTNl4duYzAikSjPsQmAB3e7ogiYiJeJRLWSMAg41B4gn/PCAohMC6nYKAylczDq4H436qgD6RHNmFUCqeZjMpPeaAYCgIVsSxG2XmCBAAbJJzdsWIsg8Q/RAvYI/QGEDNSQB2KzvbbJ7YIXYAVhesQAIqmaVnsNtYrE9om3im8wAqPa5jSqKhUdNcJhUdBxzDodPpgAcyGQ6ACpdhFbTJkzNbzbNiheLQ6TKbT1Zz2zryEkywiAE4qJhm930%2B107FB7EyyOM1nc6Pp88iyXT8OU8RMARFgxU3O3iY49mHXDtkKDDoEq2xcNsRCgRo2z4OK2wMP0xAQhAAB%2BXAaOY6bbKgVDbL8xyxu8rosIkBiunsbibEwCgQgAKqQnrOngwAhOg2yhLeLrEF4DhgmIXiYAo8ZnimLpMI4yDbE6Lpuh6qQAF6YAG8nUhO7EPvOyY0dBYkkumFjKWOv7qV%2BGmSQI0mqO6vHeAJEAEeWKbfsJFbJhGvr%2BgQ2x4DStaqN2cY%2BumkixGYXCtlucZHlwn4uSm/AehATBeEQ5g%2BtB2wgNpdQzLsCaPrFFZJRBHoTiGIZhtY1h4LGxkFS5RWoNs9DvhOJVmJhaExXVKYNdsEQ%2BQB2xfJ1xn5d1CjCoQxzbBAzX2d1jl5aZdWiEoK6ZaxE79RhkGln1z5MGcXULat1JcBtA3be12yblB1i7ae%2B2/EdtULZJVHUmYF1bbs123XdliQehj0RAdL3Od1p1Ft9y5XZh/0AxYQPA0joPPcdkMfdskgw7mcM3RohOI8jKNPYdGMrVj6a431v3w0ThO/UjaEM3taPk69J1Yz6NP4wjRNMyThNs2DFMFVDca83TBMM4z90s7LIvo5zmNrd2Us7fzDOCwrisg6LKuU2tm4a9dsSy9r35uELrP68rEN1d%2Bv7LYtzsOcmTvxkZZawlJrqWR6oJ8QJ5FuSF5r0ZIGibj6t6AcBLCmkHNmCXlP6fmsWA0CE2zZm8NHlvHSpJ8HCj3OgOljhYeCVYDO1F4nyf8WXBnpm7vsIPU4FWjCekhYZGfvKJ4lgqgeCsRYACypoEhA1wnOcIAgF0ZFmGlw%2BYPZTljcpAbeROKNjfFM29aaGXbBv82LQ7KYqv8S8Wv7BCmlQxDF96mDANEEBP/RecFzVG%2ByZ563DOEvbMqBQioAIAAeUSI4FgeAFIQA0IAsant3gYJMm8YeeAJKgjHhPaedI56MBuIvZedRV7ryoZvISO8kGKU8vvZch9TLH0SslRqZ9MqX3QUtd2Lk6RL3iqcZ%2BRAf493ogAMUnjRU0bgYGT2UAASQCNgCAPJt7pztHMXO%2Bc3hoJdsAshC87jgMgdAuBCDGEoKMYIrBjj3gWGwKENwAAJSebwABKABpCAU8X7QnsS4txnifH%2BMCQSEJriPFeL8aaLxKjQh2U/BwOYtBODpl4H4DgWhSCoE4G4WuSMFALCWCpckPBSAEE0OkuYYDJBxnuJIJscYNCSG7BoMwm5JBSG7PoTgkgcl1IKZwXgKINA1LqXMOAsAYCIBQEqJk9AyAUAgIyZkMRgAKGYMiBA0C%2BB0FdIhSgERRkRGCPUAAnpwapuI2CCBgQwWgty8m8CwKcIw4h3mkHwM%2BDooIBKjKtO0ZKKx8kf0yb82geBQY3I8FgO5vACDEDwCwZFcwqAGB2QANTwJgYUcDGDIpkIIEQYh2BSDJfIJQahRm6ASAYIwKASn6DhSiWAzA2AgBAecUgQKYjcB9DwWZ3L2B0gFQMDg3YuCirmKgeB6QUQcAALQunQDWUwlhrBmCgqqmBsRtiqvgQgA66AJmVHaNUFwQFRgtFIIEYIfQSgDASLkNIAh7U5BSJ6hgkwEJ6DaB0AQXQRieGaEGq1IaajDB6M6qYbrbBxu9eMBoAbXUxC4HMMpixlh6FRZgFYorBkcGyaQXJ%2BTCkcD8j6VVfptjAD7DNVFXgGBnByhAYpOrLD0VwECNq5RtgeGIls368QZgopmQ0kAPT7hcB9GvSQUcNAiu7GYLpZhS3DNIBi9MUzK28GrRMkAUzanvNmQsiASAFhImSuQFw%2BAiBovQHofg5LRDiGpe%2B2lKh1C/MZaQYUQpEiYtLeWw9YyOAwOSokZKWEcK1vrZIRtzaf5cXbZ2kdKzojjuzVOi9cwEC/CwDEOy27eB7oPaM49thT3TMI6QMB6YzD3CCuuzcTZNztJ7E2UtsQRm/No%2BerQMwMmcDMIJqt4yGOibmIK1IzhJBAA%3D%3D)**
Disclaimer: This is not a good way to benchmark. It's not very repeatable and google benchmark is compiled in debug, although fmt being mostly header is optimized and inlined well. The performance charts below are much more accurate.

```
-----------------------------------------------------
Benchmark           Time             CPU   Iterations
-----------------------------------------------------
BM_fmt           16.6 ns         10.5 ns     75504520
BM_jea           10.2 ns         4.13 ns    159688774
```

## **[Click for interactive performance charts](https://jeaiii.github.io/itoa/)**

The last column is uniform random length numbers from 1 to N digits - worst case for branch prediction based on number of digits

[![u32toa_chart](https://github.com/jeaiii/itoa/blob/main/chart.png)](https://jeaiii.github.io/itoa/)

[![jeaiii vs. fmt](https://github.com/jeaiii/itoa/blob/main/vs-fmt.png)](https://jeaiii.github.io/itoa/)
