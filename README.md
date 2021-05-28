# itoa - Fast integer to ascii / integer to string conversion
- 32 and 64 bit signed and unsigned versions
- fast - fasted tested on vs2017 in x86 and x64 for all digit lengths using https://github.com/miloyip/itoa-benchmark
- small - simple code that produces good compiled code even in debug builds
- 0 dependancy header version - [to_text_from_integer.h](itoa/to_text_from_integer.h)

## **Check it out vs. [{fmt}](https://github.com/fmtlib/fmt) on [godbolt.org](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,selection:(endColumn:1,endLineNumber:58,positionColumn:1,positionLineNumber:58,selectionStartColumn:1,selectionStartLineNumber:58,startColumn:1,startLineNumber:58),source:'%23include+%3Cbenchmark/benchmark.h%3E%0A%0A//+jeaiii/itoa+vs+fmt%0A//+https://github.com/jeaiii/itoa%0A%0A%23include+%3Cfmt/compile.h%3E%0A%23include+%22https://raw.githubusercontent.com/jeaiii/itoa/main/itoa/to_text_from_integer.h%22%0A%0A//+some+random+data...not+great,+most+numbers+will+have+10+digts...%0A%0Atemplate%3Cclass%3E+struct+values%3B%0Atemplate%3Csize_t...Is%3E+struct+values%3Cstd::index_sequence%3CIs...%3E%3E%0A%7B%0A++++static+constexpr+uint64_t+seed+%3D+0x87654321fdb97531%3B%0A%0A++++static+constexpr+uint64_t+murmur64(uint64_t+h)%0A++++%7B%0A++++++++h+%5E%3D+h+%3E%3E+33%3B%0A++++++++h+*%3D+0xff51afd7ed558ccdL%3B%0A++++++++h+%5E%3D+h+%3E%3E+33%3B%0A++++++++h+*%3D+0xc4ceb9fe1a85ec53L%3B%0A++++++++h+%5E%3D+h+%3E%3E+33%3B%0A++++++++return+h%3B%0A++++%7D%0A%0A++++static+constexpr+size_t+size+%3D+sizeof...(Is)%3B%0A++++static+constexpr+uint64_t+data%5Bsize%5D%7B+murmur64(seed+%2B+Is)...+%7D%3B%0A%7D%3B%0A%0Aconstexpr+values%3Cstd::make_index_sequence%3C4096%3E%3E+random_values%7B%7D%3B%0A%23define+DATA+uint32_t(random_values.data%5Bi%2B%2B+%25+random_values.size%5D)%0A%0Achar+text%5B32%5D%3B%0A%0Astatic+void+BM_jea(benchmark::State%26+state)%0A%7B%0A++++size_t+i+%3D+0%3B%0A++++for+(auto+_+:+state)%0A++++%7B%0A++++++++jeaiii::to_text_from_integer(text,+DATA)%3B%0A++++++++benchmark::DoNotOptimize(0)%3B%0A++++%7D%0A%7D%0A%0Astatic+void+BM_fmt(benchmark::State%26+state)%0A%7B%0A++++size_t+i+%3D+0%3B%0A++++for+(auto+_+:+state)%0A++++%7B%0A++++++++fmt::format_to(text,+FMT_COMPILE(%22%7B%7D%22),+DATA)%3B%0A++++++++benchmark::DoNotOptimize(0)%3B%0A++++%7D%0A%7D%0A%0ABENCHMARK(BM_jea)%3B%0ABENCHMARK(BM_fmt)%3B%0ABENCHMARK_MAIN()%3B%0A'),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0')),k:47.45170480294148,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((g:!((h:compiler,i:(compiler:clang_trunk,filters:(b:'0',binary:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'0',intel:'0',libraryCode:'1',trim:'1'),fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,libs:!((name:benchmark,ver:trunk),(name:fmt,ver:'713')),options:'-std%3Dc%2B%2B20+-O3+-pthread',selection:(endColumn:1,endLineNumber:1,positionColumn:1,positionLineNumber:1,selectionStartColumn:1,selectionStartLineNumber:1,startColumn:1,startLineNumber:1),source:1),l:'5',n:'0',o:'x86-64+clang+(trunk)+(Editor+%231,+Compiler+%231)+C%2B%2B',t:'0')),k:29.162644006182802,l:'4',m:50,n:'0',o:'',s:0,t:'0'),(g:!((h:output,i:(compiler:1,editor:1,fontScale:14,fontUsePx:'0',wrap:'1'),l:'5',n:'0',o:'%231+with+x86-64+clang+(trunk)',t:'0')),header:(),l:'4',m:50,n:'0',o:'',s:0,t:'0')),k:52.54829519705851,l:'3',n:'0',o:'',t:'0')),l:'2',n:'0',o:'',t:'0')),version:4)**

```
-----------------------------------------------------------
Benchmark                 Time             CPU   Iterations
-----------------------------------------------------------
BM_jea<uint32_t>       19.2 ns         11.5 ns     65908965
BM_fmt<uint32_t>       30.6 ns         17.7 ns     38902061
```

## **[Click for interactive performance charts](https://jeaiii.github.io/itoa/)**

The last column is uniform random length numbers from 1 to N digits

[![u32toa_chart](https://github.com/jeaiii/itoa/blob/main/chart.png)](https://jeaiii.github.io/itoa/)
