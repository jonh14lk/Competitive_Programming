## Chicken McNugget Theorem

For any two coprime numbers (n > 0, m > 0), the greatest integer that cannot be written in the form:

an + bm, (a >= 0, b >= 0)

is (n \* m) - n - m

## Consequence of the theorem

That there are exactly ((n - 1) \* (m - 1)) / 2 positive integers which cannot be expressed in the form an + bm, (a >= 0, b >= 0)

## Generalization

If n and m are not coprime, so all numbers that are not multiples of gcd(n, m) cannot be expressed in the form an + bm, (a >= 0, b >= 0)

in addition, you can consider n = (n / gcd(n, m)) and m = (m / gcd(n, m)), to find how many multiples of gcd(n, m) cannot be expressed, or to find the greatest multiple of gcd(n, m) that cannot be expressed

## Considering a > 0, b > 0

Considering (n > 0, m > 0), n and m are coprime:

let y = ((n \* m) + min(n, m)) - 1

The number of positive integers which cannot be expressed increases by (y / n)

The number of positive integers which cannot be expressed increases by (y / m)

you must not count the multiples of (n \* m) more than once, just decrease number of positive integers which cannot be expressed by (y / (n \* m))

## Problems

- [Forming Compounds](https://codeforces.com/group/XrhoJtxCjm/contest/422716/problem/I)
