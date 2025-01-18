## Manhattan and Chebyshev distances equivalences

It is well known that given points (x, y) and you need to calculate the Manhattan distances between them, instead of using: 
|x1-x2|+|y1-y2| 

you can first convert all points (x, y) into (x+y, x-y) (rotate 45 degrees) and the distances will become max(|x1-x2|, |y1-y2|) (also known as Chebyshev distance).

### Problems:

[Manhattan Triangle](https://codeforces.com/contest/1979/problem/E)
[https://atcoder.jp/contests/abc366/tasks/abc366_e](https://atcoder.jp/contests/abc366/tasks/abc366_e)
