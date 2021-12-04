#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 998244353
#define cd complex<double>
#define PI acos(-1)

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
    while (n < 2 * max(a.size(), b.size()))
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
      ans[i] = (int)round(fa[i].real()) % mod;
    return ans;
  }
} // namespace fft

vector<int> p1;
vector<int> p2;

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  int n = s.size();
  vector<int> pref(1, 0);
  for (int i = 0; i < n; i++)
  {
    int x = s[i] - 'a' + 1;
    pref.pb(pref.back() + x);
  }
  int lim = pref.back();
  p1.resize(2 * lim + 1);
  p2.resize(2 * lim + 1);
  for (auto const &i : pref)
  {
    p1[lim + i] = 1; // numero positivo
    p2[lim - i] = 1; // numero negativo
  }
  vector<int> merge = fft::mul(p1, p2); // todas as somas de p1[i] + p2[j]
  int ans = 0;
  for (int i = lim + 1; i < merge.size(); i++)
  {
    if (merge[i] > 0)
      ans++;
  }
  cout << ans / 2 << endl;
  return 0;
}
// sum = pref[r] - pref[l]
// se souber calcular todas as subtrações ao inves
// de todas as somas, eh gg

// mapear os expoentes do polinomio
// 0 -> -n
// 1 -> -n + 1
// 2 -> -n + 2
// ...
// n - 1 -> -1
// n  -> 0
// n + 1 -> 1
// n + 2 -> 2
// ...
// n + n -> n

// dai da pra fazer o all possible sums nisso
// um polinomio contem todos os prefixos
// o outro contem todos os prefixos * -1
// com uma unica multiplicação posso pegar os
// positivos que tem coeficiente > 0 e contar