#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 100005
#define mod 1000000007
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
  vector<int> mul(vector<int> &a, vector<int> &b)
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

const int MOD = (1ll << 61) - 1;
int P;
int mulmod(int a, int b)
{
  const static int LOWER = (1ll << 30) - 1, GET31 = (1ll << 31) - 1;
  int l1 = a & LOWER, h1 = a >> 30, l2 = b & LOWER, h2 = b >> 30;
  int m = l1 * h2 + l2 * h1, h = h1 * h2;
  int ans = l1 * l2 + (h >> 1) + ((h & 1) << 60) + (m >> 31) + ((m & GET31) << 30) + 1;
  ans = (ans & MOD) + (ans >> 61), ans = (ans & MOD) + (ans >> 61);
  return ans - 1;
}
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int uniform(int l, int r)
{
  uniform_int_distribution<int> uid(l, r);
  return uid(rng);
}
struct string_hashing
{
  vector<int> h, p;
  string_hashing() {}
  string_hashing(string s) : h(s.size()), p(s.size())
  {
    p[0] = 1, h[0] = s[0];
    for (int i = 1; i < s.size(); i++)
      p[i] = mulmod(p[i - 1], P), h[i] = (mulmod(h[i - 1], P) + s[i]) % MOD;
  }
  int get(int l, int r)
  {
    int hash = h[r] - (l ? mulmod(h[l - 1], p[r - l + 1]) : 0);
    return hash < 0 ? hash + MOD : hash;
  }
};
string adapt(string s)
{
  string_hashing sh(s + s);
  int n = s.size();
  for (int i = 1; i <= n; i++)
  {
    if (n % i == 0)
    {
      bool ok = 1;
      for (int j = 0; j < n; j += i)
        ok &= (sh.get(0, i - 1) == sh.get(j, j + i - 1));
      if (ok)
        return s.substr(0, i);
    }
  }
  return s;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  P = uniform(256, MOD - 1);
  string s;
  cin >> s;
  if (s.size() > 10000)
  {
    s = adapt(s); // a grande sacada ta aqui
    // com isso a gnt garante que poucos valores vao estar em valid1 ou valid2
    // dai nao precisa nem de convolucao, eh so olhar pra cada valor e contar quantos pares
    int n = s.size();
    string srev = s;
    reverse(srev.begin(), srev.end());
    string_hashing sh(s + s);
    string_hashing shrev(srev + srev);
    vector<bool> valid1(n, 0);
    vector<bool> valid2(n, 0);
    for (int i = 0; i < n; i++)
    {
      if (sh.get(0, n - 1) == sh.get(i, i + n - 1))
        valid1[i] = 1;
      if (sh.get(0, n - 1) == shrev.get(i, i + n - 1))
        valid2[i] = 1;
    }
    int k;
    cin >> k;
    int shifts = 0, is_rev = 0;
    vector<pi> v;
    v.pb({0, 0});
    for (int i = 0; i < k; i++)
    {
      char c;
      cin >> c;
      if (c == 'L')
      {
        int x;
        cin >> x;
        x %= n;
        shifts = (shifts + x) % n;
      }
      else if (c == 'R')
      {
        int x;
        cin >> x;
        x %= n;
        shifts = (shifts - x + n) % n;
      }
      else
      {
        is_rev ^= 1;
        shifts = (n - shifts) % n;
      }
      v.pb({is_rev, shifts});
    }
    int ans = 0;
    // caso (is_rev = false, is_rev = false)
    {
      for (int i = 0; i < n; i++)
      {
        if (valid1[i])
        {
          vector<int> cnt(n, 0);
          for (int j = 0; j <= k; j++)
          {
            if (v[j].fir == 0)
            {
              int x = (v[j].sec - i + n) % n;
              ans += cnt[x];
              cnt[v[j].sec]++;
            }
          }
        }
      }
    }
    // caso (is_rev = true, is_rev = true)
    {
      for (int i = 0; i < n; i++)
      {
        if (valid1[i])
        {
          vector<int> cnt(n, 0);
          for (int j = 0; j <= k; j++)
          {
            if (v[j].fir == 1)
            {
              int x = (v[j].sec - i + n) % n;
              ans += cnt[x];
              cnt[v[j].sec]++;
            }
          }
        }
      }
    }
    // caso (is_rev = false, is_rev = true)
    {
      for (int i = 0; i < n; i++)
      {
        if (valid2[i])
        {
          vector<int> cnt(n, 0);
          for (int j = 0; j <= k; j++)
          {
            if (v[j].fir == 0)
            {
              int x = (v[j].sec - i + n) % n;
              ans += cnt[x];
            }
            else
            {
              cnt[(n - v[j].sec) % n]++;
            }
          }
        }
      }
    }
    // caso (is_rev = true, is_rev = false)
    {
      for (int i = 0; i < n; i++)
      {
        if (valid2[i])
        {
          vector<int> cnt(n, 0);
          for (int j = 0; j <= k; j++)
          {
            if (v[j].fir == 1)
            {
              int x = (v[j].sec - i + n) % n;
              ans += cnt[x];
            }
            else
            {
              cnt[(n - v[j].sec) % n]++;
            }
          }
        }
      }
    }
    cout << ans << endl;
  }
  else // so pelo meme
  {
    int n = s.size();
    string srev = s;
    reverse(srev.begin(), srev.end());
    string_hashing sh(s + s);
    string_hashing shrev(srev + srev);
    vector<bool> valid1(n, 0);
    vector<bool> valid2(n, 0);
    for (int i = 0; i < n; i++)
    {
      if (sh.get(0, n - 1) == sh.get(i, i + n - 1))
        valid1[i] = 1;
      if (sh.get(0, n - 1) == shrev.get(i, i + n - 1))
        valid2[i] = 1;
    }
    int k;
    cin >> k;
    int shifts = 0, is_rev = 0;
    vector<pi> v;
    vector<int> p1(2 * n + 1);
    vector<int> p2(2 * n + 1);
    vector<int> p3(2 * n + 1);
    vector<int> p4(2 * n + 1);
    vector<int> p5(2 * n + 1);
    vector<int> p6(2 * n + 1);
    {
      v.pb({0, 0});
      p1[n]++;
      p2[n]++;
      p5[n]++;
    }
    for (int i = 0; i < k; i++)
    {
      char c;
      cin >> c;
      if (c == 'L')
      {
        int x;
        cin >> x;
        shifts = (shifts + x) % n;
      }
      else if (c == 'R')
      {
        int x;
        cin >> x;
        shifts = (shifts - x + n) % n;
      }
      else
      {
        is_rev ^= 1;
        shifts = (n - shifts) % n;
      }
      v.pb({is_rev, shifts});
      if (is_rev)
      {
        p3[n + shifts]++;
        p4[n - shifts]++;
        p6[n - ((n - shifts) % n)]++;
      }
      else
      {
        p1[n + shifts]++;
        p2[n - shifts]++;
        p5[n - ((n - shifts) % n)]++;
      }
    }
    int ans = 0;
    // caso (is_rev = false, is_rev = false)
    {
      vector<int> conv = fft::mul(p1, p2);
      for (int i = 0; i <= k; i++)
      {
        if (v[i].fir == 0)
          conv[(2 * n)]--;
      }
      for (int i = 0; i < conv.size(); i++)
      {
        int val = i - (2 * n);
        val = ((val % n) + n) % n;
        if (valid1[val])
          ans += conv[i];
      }
    }
    // caso (is_rev = true, is_rev = true)
    {
      vector<int> conv = fft::mul(p3, p4);
      for (int i = 0; i <= k; i++)
      {
        if (v[i].fir == 1)
          conv[(2 * n)]--;
      }
      for (int i = 0; i < conv.size(); i++)
      {
        int val = i - (2 * n);
        val = ((val % n) + n) % n;
        if (valid1[val])
          ans += conv[i];
      }
    }
    // caso (is_rev = false, is_rev = true)
    {
      vector<int> conv = fft::mul(p1, p6);
      for (int i = 0; i < conv.size(); i++)
      {
        int val = i - (2 * n);
        val = ((val % n) + n) % n;
        if (valid2[val])
          ans += conv[i];
      }
    }
    // caso (is_rev = true, is_rev = false)
    {
      vector<int> conv = fft::mul(p3, p5);
      for (int i = 0; i < conv.size(); i++)
      {
        int val = i - (2 * n);
        val = ((val % n) + n) % n;
        if (valid2[val])
          ans += conv[i];
      }
    }
    ans /= 2;
    cout << ans << endl;
  }
}