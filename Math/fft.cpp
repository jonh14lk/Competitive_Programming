#include <bits/stdc++.h>

using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 125001
#define mod 1000000007
#define cd complex<double>

namespace fft
{
  int n;

  void fft(vector<cd> &a, bool invert)
  {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++)
    {
      int bit = n >> 1;
      for (; j & bit; bit >>= 1)
        j ^= bit;
      j ^= bit;
      if (i < j)
        swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1)
    {
      double ang = 2 * PI / len * (invert ? -1 : 1);
      cd wlen(cos(ang), sin(ang));
      for (int i = 0; i < n; i += len)
      {
        cd w(1);
        for (int j = 0; j < len / 2; j++)
        {
          cd u = a[i + j], v = a[i + j + len / 2] * w;
          a[i + j] = u + v;
          a[i + j + len / 2] = u - v;
          w *= wlen;
        }
      }
    }
    if (invert)
      for (cd &x : a)
        x /= n;
  }
  vector<int> mul(vector<int> a, vector<int> b)
  {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    n = 1;
    while (n < a.size() + b.size())
      n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
      fa[i] *= fb[i];
    fft(fa, true);
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
      ans[i] = round(fa[i].real());
    return ans;
  }
}
signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  int m = n + n;
  vector<int> a(m, 0);
  vector<int> aa(m, 0);
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
    aa[i] = (a[i] == 47) ? 1 : 0;
    a[i + n] = a[i];
    aa[i + n] = aa[i];
  }
  vector<int> b(m, 0);
  vector<int> bb(m, 0);
  for (int i = n - 1; i >= 0; i--)
  {
    cin >> b[i + n];
    bb[i + n] = (b[i + n] == 47) ? 1 : 0;
  }
  vector<int> ans1 = fft::mul(a, b);
  vector<int> ans2 = fft::mul(aa, bb);
  int ans = 0;
  for (int i = (m - 1); i < (m - 1) + n; i++)
  {
    if (ans2[i] > 0)
      continue;
    ans = max(ans1[i], ans); // produto escalar de algum cyclic shift
  }
  cout << ans << endl;
  return 0;
}
// https://algo.sk/br24/problem.php?problem=d3-badsquare
// exemplo do all possible scalar products
// dados dois arrays a e b de tamanho n
// quero computar o scalar product de todos os cyclics shifts de a com b
// duplicar o array a
// dar reverse no array b e adicionar n zeros no inicio