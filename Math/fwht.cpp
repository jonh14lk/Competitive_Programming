#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1025
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

vector<modint> fwht(char op, vector<modint> f, bool inv = 0)
{
  int n = f.size();
  for (int k = 0; (n - 1) >> k; k++)
  {
    for (int i = 0; i < n; i++)
    {
      if (i >> k & 1)
      {
        int j = i ^ (1 << k);
        if (op == '^')
          f[j] += f[i], f[i] = f[j] - modint(2) * f[i];
        if (op == '|')
          f[i] += modint(inv ? -1 : 1) * f[j];
        if (op == '&')
          f[j] += modint(inv ? -1 : 1) * f[i];
      }
    }
  }
  if (op == '^' and inv)
  {
    for (auto &i : f)
      i /= n;
  }
  return f;
}
vector<modint> conv(char op, vector<modint> a, vector<modint> b)
{
  a = fwht(op, a, 0);
  b = fwht(op, b, 0);
  for (int i = 0; i < a.size(); i++)
  {
    a[i] *= b[i];
  }
  return fwht(op, a, 1);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  n = 1 << n;
  vector<modint> a(n);
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    a[i] = x;
  }
  vector<modint> b(n);
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    b[i] = x;
  }
  vector<modint> c = conv('^', a, b); // convolucao de xor
  for (auto const &i : c)
    cout << i.val << " ";
  cout << endl;
  vector<modint> d = conv('&', a, b); // convolucao de and
  for (auto const &i : d)
    cout << i.val << " ";
  cout << endl;
  return 0;
}
// o tipo ta como modint, mas tem como mudar para qualquer um
// usar preferencialmente tamanho como potencia de 2

// faz a convolucao de a com b
// c[k] = ∑(a[i] * b[j]), com (i op j) = k
// op pode ser xor, and ou or

// para testar
// https://judge.yosupo.jp/problem/bitwise_xor_convolution
// https://judge.yosupo.jp/problem/bitwise_and_convolution