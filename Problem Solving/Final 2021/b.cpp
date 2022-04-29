#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pbc push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500001
#define mod 1000000007
#define double long double
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
    int n = 1;
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
bool cmp(int a, int b)
{
  return abs(a) < abs(b);
}
vector<int> solve(vector<int> &a, vector<int> &b)
{
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  vector<int> pa, na, pb, nb;
  for (auto const &i : a)
    (i >= 0) ? pa.pbc(i) : na.pbc(i);
  for (auto const &i : b)
    (i >= 0) ? pb.pbc(i) : nb.pbc(i);
  sort(pa.begin(), pa.end(), cmp);
  sort(pb.begin(), pb.end(), cmp);
  sort(na.begin(), na.end(), cmp);
  sort(nb.begin(), nb.end(), cmp);
  int i, j;
  vector<int> ans, rem, rem2;
  i = pa.size() - 1, j = pb.size() - 1;
  while (i >= 0 && j >= 0)
  {
    ans.pbc(pa[i] * pb[j]);
    i--, j--;
  }
  while (i >= 0 || j >= 0)
  {
    if (i >= 0)
      rem.pbc(pa[i]);
    else
      rem.pbc(pb[j]);
    i--, j--;
  }
  i = na.size() - 1, j = nb.size() - 1;
  while (i >= 0 && j >= 0)
  {
    ans.pbc(na[i] * nb[j]);
    i--, j--;
  }
  while (i >= 0 || j >= 0)
  {
    if (i >= 0)
      rem2.pbc(na[i]);
    else
      rem2.pbc(nb[j]);
    i--, j--;
  }
  sort(ans.rbegin(), ans.rend());
  for (int i = 1; i < ans.size(); i++)
    ans[i] += ans[i - 1];
  sort(rem.begin(), rem.end(), cmp);
  sort(rem2.begin(), rem2.end(), cmp);
  vector<int> conv = fft::mul(rem, rem2);
  int prv = (!ans.size()) ? 0 : ans.back();
  for (int i = 0; i < rem.size(); i++)
  {
    ans.pbc(prv + conv[i]);
  }
  ans.pop_back();
  int fim = 0;
  for (int i = 0; i < a.size(); i++)
    fim += (a[i] * b[i]);
  ans.pbc(fim);
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> a(n);
  vector<int> b(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];
  vector<int> mx = solve(a, b);
  for (int i = 0; i < n; i++)
    b[i] = -b[i];
  vector<int> mn = solve(a, b);
  for (int i = 0; i < n; i++)
    cout << -mn[i] << " " << mx[i] << endl;
  return 0;
}