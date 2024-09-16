#include <bits/stdc++.h>

using namespace std;

#define int long long int
#define pi pair<int, int>
#define fir first
#define sec second
#define pb push_back
#define MAXN 1000006
#define mod 1000000007

int lpf[MAXN];
int mobius[MAXN];
int mp[MAXN];
int f[MAXN];
int resp[MAXN];
int pot[MAXN];

void calc_lpf()
{
  for (int i = 2; i < MAXN; i++)
  {
    if (!lpf[i])
    {
      for (int j = i; j < MAXN; j += i)
      {
        if (!lpf[j])
          lpf[j] = i;
      }
    }
  }
}
void calc()
{
  calc_lpf();
  mobius[1] = 1;
  for (int i = 2; i < MAXN; i++)
  {
    if (lpf[i / lpf[i]] == lpf[i])
      mobius[i] = 0;
    else
      mobius[i] = -1 * mobius[i / lpf[i]];
  }
}
signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  calc();
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    f[x]++;
  }
  for (int i = 2; i < MAXN; i++)
  {
    for (int j = i; j < MAXN; j += i)
      mp[i] += f[j];
  }
  for (int i = 2; i < MAXN; i++)
  {
    for (int j = i; j < MAXN; j += i)
      resp[j] += (mobius[i] * -1 * mp[i]);
  }
  pot[0] = 1;
  for (int i = 1; i < MAXN; i++)
  {
    pot[i] = (pot[i - 1] * 2) % mod;
  }
  int q;
  cin >> q;
  while (q--)
  {
    int x;
    cin >> x;
    cout << pot[n - resp[x]] << endl;
  }
  return 0;
}