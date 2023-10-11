#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 300005
#define mod 998244353

struct modint
{
  int val;
  modint(int v = 0) { val = ((v % mod) + mod) % mod; }
  int pow(int y)
  {
    modint x = val;
    modint z = 1;
    while (y)
    {
      if (y & 1)
        z *= x;
      x *= x;
      y >>= 1;
    }
    return z.val;
  }
  int inv() { return pow(mod - 2); }
  void operator=(int o) { val = o % mod; }
  void operator=(modint o) { val = o.val % mod; }
  void operator+=(modint o) { *this = *this + o; }
  void operator-=(modint o) { *this = *this - o; }
  void operator*=(modint o) { *this = *this * o; }
  void operator/=(modint o) { *this = *this / o; }
  bool operator==(modint o) { return val == o.val; }
  bool operator!=(modint o) { return val != o.val; }
  int operator*(modint o) { return ((val * o.val) % mod); }
  int operator/(modint o) { return (val * o.inv()) % mod; }
  int operator+(modint o) { return (val + o.val) % mod; }
  int operator-(modint o) { return (val - o.val + mod) % mod; }
};
namespace fft
{
  int n;
  int root = -1;
  int root_1 = -1;
  int pw = __builtin_ctz(mod - 1);
  int root_pw = (1 << pw);

  void find_root()
  {
    if (root != -1)
      return;
    int r = 2;
    while (!(modint(r).pow((1 << pw)) == 1 && modint(r).pow((1 << (pw - 1))) != 1))
      r++;
    root = r;
    root_1 = modint(root).inv();
  }
  void ntt(vector<modint> &a, bool invert)
  {
    find_root();
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
      modint wlen = (invert) ? root_1 : root;
      for (int i = len; i < root_pw; i <<= 1)
        wlen *= wlen;
      for (int i = 0; i < n; i += len)
      {
        modint w = 1;
        for (int j = 0; j < len / 2; j++)
        {
          modint u = a[i + j];
          modint v = a[i + j + len / 2] * w;
          a[i + j] = u + v;
          a[i + j + len / 2] = u - v;
          w *= wlen;
        }
      }
    }
    if (invert)
    {
      modint n_1 = modint(n).inv();
      for (int i = 0; i < a.size(); i++)
        a[i] *= n_1;
    }
  }
  vector<modint> mul(vector<modint> a, vector<modint> b)
  {
    n = 1;
    while (n < 2 * max(a.size(), b.size()))
      n <<= 1;
    a.resize(n);
    b.resize(n);
    ntt(a, false);
    ntt(b, false);
    for (int i = 0; i < n; i++)
      a[i] *= b[i];
    ntt(a, true);
    return a;
  }
}

modint f[MAXN];
modint invfat[MAXN];

void calc()
{
  f[0] = 1;
  invfat[0] = 1;
  for (int i = 1; i < MAXN; i++)
  {
    f[i] = f[i - 1] * i;
    invfat[i] = f[i].inv();
  }
}
modint ncr(int n, int k)
{
  modint ans = f[n] * invfat[k];
  ans *= invfat[n - k];
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, y;
  cin >> n >> y;
  n++;
  vector<int> a(n);
  vector<int> b(n);
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++)
  {
    cin >> b[i];
  }
  if (y == 0)
  {
    for (int i = 0; i < n; i++)
    {
      cout << (a[i] + b[i]) % mod << " ";
    }
    cout << endl;
    return 0;
  }
  calc();
  vector<modint> c(n);
  {
    vector<modint> vx(n);
    vector<modint> vy(n);
    for (int i = 0; i < n; i++)
    {
      vx[i] = a[i];
      vx[i] *= f[i];
      vx[i] *= modint(y).pow(i);
      vy[i] = modint(1) / f[n - 1 - i];
    }
    vector<modint> result = fft::mul(vx, vy);
    for (int i = 0; i < n; i++)
    {
      modint aa = result[n + i - 1];
      aa /= f[i];
      aa /= modint(y).pow(i);
      c[i] += aa;
    }
  }
  {
    vector<modint> vx(n);
    vector<modint> vy(n);
    for (int i = 0; i < n; i++)
    {
      vx[i] = b[i];
      vx[i] *= f[i];
      vx[i] *= modint(-y).pow(i);
      vy[i] = modint(1) / f[n - 1 - i];
    }
    vector<modint> result = fft::mul(vx, vy);
    for (int i = 0; i < n; i++)
    {
      modint bb = result[n + i - 1];
      bb /= f[i];
      bb /= modint(-y).pow(i);
      c[i] += bb;
    }
  }
  for (auto const &i : c)
    cout << i.val << " ";
  cout << endl;
  return 0;
}