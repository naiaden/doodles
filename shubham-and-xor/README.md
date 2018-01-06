This file is my (not submitted) submission for

https://www.hackerearth.com/practice/algorithms/sorting/bubble-sort/practice-problems/algorithm/shubham-and-xor-8526868e/

Extract the input files, and then run
```
for f in ./*.clean.txt; do echo $f; time cat $f | ./a.out; done
```

These are the results on my not so blazingly fast machine:
```
Intel(R) Core(TM) i5-4690T CPU @ 2.50GHz
```

The results are verified to be correct.

```
alixerhoe% for f in ./*.clean.txt; do echo $f; time cat $f | ./a.out; done
./851cc5e6ef0111e7.txt.clean.txt
125
cat $f  0.00s user 0.00s system 4% cpu 0.071 total
./a.out  0.65s user 0.02s system 99% cpu 0.675 total
./85280442ef0111e7.txt.clean.txt
473
cat $f  0.00s user 0.01s system 4% cpu 0.138 total
./a.out  1.35s user 0.02s system 92% cpu 1.472 total
./8530f8e0ef0111e7.txt.clean.txt
334
cat $f  0.00s user 0.00s system 2% cpu 0.194 total
./a.out  1.09s user 0.02s system 91% cpu 1.222 total
./853a8cc0ef0111e7.txt.clean.txt
216
cat $f  0.00s user 0.00s system 3% cpu 0.096 total
./a.out  0.85s user 0.01s system 97% cpu 0.891 total
./8543632cef0111e7.txt.clean.txt
42
cat $f  0.00s user 0.00s system 4% cpu 0.036 total
./a.out  0.33s user 0.01s system 99% cpu 0.336 total
./854ef980ef0111e7.txt.clean.txt
165
cat $f  0.00s user 0.00s system 3% cpu 0.082 total
./a.out  0.76s user 0.02s system 98% cpu 0.788 total
./8557ce5cef0111e7.txt.clean.txt
213
cat $f  0.00s user 0.00s system 3% cpu 0.093 total
./a.out  0.83s user 0.03s system 99% cpu 0.864 total
./8561842eef0111e7.txt.clean.txt
119708468404
cat $f  0.00s user 0.00s system 3% cpu 0.139 total
./a.out  0.87s user 0.02s system 96% cpu 0.927 total
./856a7700ef0111e7.txt.clean.txt
34976025398
cat $f  0.00s user 0.00s system 2% cpu 0.108 total
./a.out  0.45s user 0.01s system 92% cpu 0.494 total
./85733016ef0111e7.txt.clean.txt
33907855947
cat $f  0.00s user 0.00s system 3% cpu 0.072 total
./a.out  0.44s user 0.02s system 90% cpu 0.504 total
./858887a4ef0111e7.txt.clean.txt
68734640380
cat $f  0.00s user 0.00s system 3% cpu 0.108 total
./a.out  0.59s user 0.02s system 96% cpu 0.631 total
./8591a1d6ef0111e7.txt.clean.txt
32972734829
cat $f  0.00s user 0.00s system 2% cpu 0.107 total
./a.out  0.43s user 0.01s system 90% cpu 0.486 total
./859ab80cef0111e7.txt.clean.txt
54571672948
cat $f  0.00s user 0.00s system 3% cpu 0.093 total
./a.out  0.53s user 0.01s system 98% cpu 0.553 total
./85a8b43eef0111e7.txt.clean.txt
81868585778
cat $f  0.00s user 0.00s system 2% cpu 0.130 total
./a.out  0.63s user 0.03s system 96% cpu 0.682 total
./85bb1bceef0111e7.txt.clean.txt
45732406141
cat $f  0.00s user 0.00s system 3% cpu 0.086 total
./a.out  0.51s user 0.00s system 96% cpu 0.525 total
./85cc2e1eef0111e7.txt.clean.txt
100793540716
cat $f  0.00s user 0.00s system 3% cpu 0.123 total
./a.out  0.81s user 0.02s system 99% cpu 0.831 total
./85d4c830ef0111e7.txt.clean.txt
54571672948
cat $f  0.00s user 0.00s system 2% cpu 0.120 total
./a.out  0.53s user 0.01s system 93% cpu 0.581 total
./85e00f10ef0111e7.txt.clean.txt
0
cat $f  0.00s user 0.00s system 65% cpu 0.001 total
./a.out  0.00s user 0.00s system 66% cpu 0.002 total
./85e8b034ef0111e7.txt.clean.txt
0
cat $f  0.00s user 0.00s system 65% cpu 0.001 total
./a.out  0.00s user 0.00s system 66% cpu 0.002 total
./85f84f80ef0111e7.txt.clean.txt
0
cat $f  0.00s user 0.00s system 65% cpu 0.001 total
./a.out  0.00s user 0.00s system 67% cpu 0.002 total
```

Previous iterations were not so fast, because I followd the exercise a bit too literally. But when I poured it into an awk version, it suddenly became clear what the right direction was:
```
tail -n 1 851cc5e6ef0111e7.txt.clean.txt| tr ' ' '\n' | sort | uniq -c | sort -r | cut -f7 -d' ' | sort | uniq -c | awk '{if($2>1) print $1*($2*($2-1))/2}' | paste -s -d+ - | bc
```
