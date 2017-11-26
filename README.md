# itoa - integer to ascii / integer to string conversion
- 32 and 64 bit signed and unsigned versions
- fast - fasted tested on vs2017 in x86 and x64 for all digit lengths using https://github.com/miloyip/itoa-benchmark
- small - simple code that produces good code even in debug builds

```
https://github.com/jeaiii/itoa-benchmark
https://github.com/miloyip/itoa-benchmark
sample results: win64 core i7 2.8Gz

u32toa
Benchmarking sequential branchlut            ... [   5.307ns,   12.626ns]
Benchmarking     random branchlut            ...   17.618ns
Benchmarking sequential branchlut2           ... [   3.411ns,   15.993ns]
Benchmarking     random branchlut2           ...   19.314ns
Benchmarking sequential countlut             ... [   4.776ns,   14.295ns]
Benchmarking     random countlut             ...   19.003ns

Benchmarking sequential jeaiii               ... [   3.071ns,    7.850ns]
Benchmarking     random jeaiii               ...   14.538ns

Benchmarking sequential sse2                 ... [   5.292ns,   10.716ns]
Benchmarking     random sse2                 ...   17.640ns
Benchmarking sequential unrolledlut          ... [   6.141ns,    8.739ns]
Benchmarking     random unrolledlut          ...   15.245ns
```
![u32toa_chart](https://user-images.githubusercontent.com/30875055/33234449-f52c4d22-d1db-11e7-8725-bd3439601608.png)
