#define MAXN 100000

int phi[MAXN];

void calc()
{
  for (int i = 0; i < MAXN; i++)
    phi[i] = i;
  for (int i = 2; i < MAXN; i++)
  {
    if (phi[i] == i)
    {
      for (int j = i; j < MAXN; j += i)
        phi[j] -= phi[j] / i;
    }
  }
}
int calc_phi(int n)
{
  int ans = n;
  for (int i = 2; i * i <= n; i++)
  {
    if (n % i == 0)
    {
      while (n % i == 0)
        n /= i;
      ans -= ans / i;
    }
  }
  if (n > 1)
    ans -= ans / n;
  return ans;
}