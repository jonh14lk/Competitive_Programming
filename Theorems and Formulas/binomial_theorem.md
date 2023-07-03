## Binomial Theorem

### Theorem

$$
(x + y)^n = \sum_{k = 0}^{n} {n \choose k} x^{n - k}y^{k}
$$

in addition, we have:

$$
(x - y)^n = \sum_{k = 0}^{n} (-1)^k {n \choose k} x^{n - k}y^{k}
$$

$$
(1 + x)^n = \sum_{k = 0}^{n} {n \choose k} x^{k}
$$

### Cool Problem

[Fibonacci Fever](https://codeforces.com/gym/104412/problem/F)

Given n and k you're asked to compute (mod $10^9 + 7$):

$$
\sum\_{i = 1}^{n}f_i^k
$$

where $f_n$ is the n-th fibonacci number.

Recall that:

$$
f_n = \frac{1}{\sqrt{5}} \left(\frac{1+\sqrt{5}}{2}\right)^n -  \frac{1}{\sqrt{5}} \left(\frac{1-\sqrt{5}}{2}\right)^n
$$

This is something like that:

$$
f_n = ca^n - cb^n
$$

In the end, we end up with something like:

$$
c^k (\sum_{j = 0}^{k} (-1)^{j} {k \choose j} \sum_{i = 1}^{n} (a^{k - j}b^{j})^{i} )
$$

PS: To handle $\sqrt{5}$ mod $10^9 + 7$, we need to store each number in the form $x = a + b\sqrt{5}$

[Code](https://github.com/jonh14lk/Competitive_Programming/blob/master/Math/binomial_theorem.cpp)
