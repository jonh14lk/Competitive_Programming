#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 100005
#define mod 1000000007
#define cd complex<double>

const double eps = 1e-12;
const int alphabet_size = 26;

namespace fft
{
  void dft(vector<cd> &a)
  {
    int n = a.size();
    if (n == 1)
      return;
    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++)
    {
      a0[i] = a[2 * i];
      a1[i] = a[2 * i + 1];
    }
    dft(a0);
    dft(a1);
    double ang = 2 * PI / n;
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++)
    {
      a[i] = a0[i] + w * a1[i];
      a[i + n / 2] = a0[i] - w * a1[i];
      w *= wn;
    }
  }
  void inverse_dft(vector<cd> &a)
  {
    int n = a.size();
    if (n == 1)
      return;
    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++)
    {
      a0[i] = a[2 * i];
      a1[i] = a[2 * i + 1];
    }
    inverse_dft(a0);
    inverse_dft(a1);
    double ang = 2 * PI / n * -1;
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++)
    {
      a[i] = a0[i] + w * a1[i];
      a[i + n / 2] = a0[i] - w * a1[i];
      a[i] /= 2;
      a[i + n / 2] /= 2;
      w *= wn;
    }
  }
  vector<double> mul(vector<cd> a, vector<cd> b)
  {
    int n = 1;
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    while (n < a.size() + b.size())
      n <<= 1;
    fa.resize(n);
    fb.resize(n);
    dft(fa);
    dft(fb);
    for (int i = 0; i < n; i++)
      fa[i] *= fb[i];
    inverse_dft(fa);
    vector<double> ans(n);
    for (int i = 0; i < n; i++)
      ans[i] = fa[i].real();
    return ans;
  }
} // namespace fft
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s, t;
  cin >> s >> t;
  int n = s.size(), m = t.size();
  reverse(t.begin(), t.end());
  vector<cd> a(n);
  vector<cd> b(m);
  for (int i = 0; i < n; i++)
  {
    int ch = s[i] - 'a';
    double ang = (2 * PI * ch) / alphabet_size;
    a[i] = cd(cos(ang), sin(ang));
  }
  for (int i = 0; i < m; i++)
  {
    int ch = t[i] - 'a';
    double ang = (2 * PI * ch) / alphabet_size;
    b[i] = cd(cos(ang), -sin(ang));
  }
  vector<double> ans = fft::mul(a, b);
  int matches = 0;
  for (int i = m - 1; i < n; i++)
    matches += (abs(ans[i] - m) <= eps);
  cout << matches << endl;
  return 0;
}
// number of matches of a pattern in string
// using fft
