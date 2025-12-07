## Antiperiod of the Decimal Part

We call the *antiperiod* of a decimal number the part that comes **before** its repeating cycle.  
For example, in the number  `12.321559559...`,  the antiperiod is everything before the cycle begins, in that case is `321`.

To figure out the length of the antiperiod of a number written as a fraction x / y, we first need to make sure that x and y are coprime. Assuming they are, we have:

- Let A be the number of prime factors 2 in y  
- Let B be the number of prime factors 5 in y  

Then the antiperiod length is simply:

max(A, B)

## Period of the Decimal Part

Now for the repeating part of the decimal expansion.  
Using the same example `12.321559559...` the repeating cycle is `559`.

Again, for a fraction x / y, the first step is to ensure x and y are coprime. Assuming that, we define:

Let y' be the number obtained from y after removing all prime factors 2 and 5.  
For example, if  y = 420 = 2 * 2 * 5 * 3 * 7, then  y' = 21 = 3 * 7.

So, the period length is:

- 0, if y' = 1  
- Otherwise, it's the smallest positive integer x such that  10^x ≡ 1 (mod y'). This value of x can be found using the [baby-step giant-step algorithm](https://cp-algorithms.com/algebra/discrete-log.html).

## Motivation

My motivation for writing this came from solving the problem [Displaying Decimals](https://codeforces.com/gym/106178/problem/D), which is a really fun problem, but requires knowing all the ideas above. Once you know these things, the problem becomes very funny to solve.
