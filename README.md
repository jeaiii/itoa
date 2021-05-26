# itoa - Fast integer to ascii / integer to string conversion
- 32 and 64 bit signed and unsigned versions
- fast - fasted tested on vs2017 in x86 and x64 for all digit lengths using https://github.com/miloyip/itoa-benchmark
- small - simple code that produces good compiled code even in debug builds
- 0 dependancy header version - [to_text_from_integer.h](itoa/to_text_from_integer.h)

## **Check it out vs. [{fmt}](https://github.com/fmtlib/fmt) on [godbolt.org](https://godbolt.org/z/jf8GMvz5Y)**

```
-----------------------------------------------------------
Benchmark                 Time             CPU   Iterations
-----------------------------------------------------------
BM_jea<uint32_t>       19.2 ns         11.5 ns     65908965
BM_fmt<uint32_t>       30.6 ns         17.7 ns     38902061
```

## **[Click for interactive performance charts](https://jeaiii.github.io/itoa/)**

[![u32toa_chart](https://github.com/jeaiii/itoa/blob/main/chart.png)](https://jeaiii.github.io/itoa/)
