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
#define MAXN 200001

const int d = 257, mod = 8675309;
const int d2 = 619, mod2 = 1000000007;
int n, m;
string ss;
string vv[MAXN];

struct sh
{
  vector<int> pref;
  vector<int> pot;
  vector<int> pref2;
  vector<int> pot2;

  int mul(int x, int y, int m)
  {
    return (x * y) % m;
  }
  int sub(int a, int b, int m)
  {
    return (a - b < 0) ? a - b + m : a - b;
  }
  int sum(int a, int b, int m)
  {
    return (a + b >= m) ? a + b - m : a + b;
  }
  sh(string &s)
  {
    pref.resize(s.size() + 1);
    pot.resize(s.size() + 1);
    pref2.resize(s.size() + 1);
    pot2.resize(s.size() + 1);
    pref[0] = 0, pref2[0] = 0;
    for (int i = 0; i < s.size(); i++)
    {
      int val = mul(pref[i], d, mod);
      pref[i + 1] = sum(s[i], val, mod);
      int val2 = mul(pref2[i], d2, mod2);
      pref2[i + 1] = sum(s[i], val2, mod2);
    }
    pot[0] = 1, pot2[0] = 1;
    for (int i = 1; i <= s.size(); i++)
    {
      pot[i] = mul(pot[i - 1], d, mod);
      pot2[i] = mul(pot2[i - 1], d2, mod2);
    }
  }
  sh() {}
  int get(int l, int r)
  {
    return sub(pref[r + 1], mul(pref[l], pot[r - l + 1], mod), mod) * sub(pref2[r + 1], mul(pref2[l], pot2[r - l + 1], mod2), mod2);
  }
};

sh s;
sh v[MAXN];

bool can(int k) // se todos os shifts possuem uma substring de tamanho k
{
  if (k == 0)
    return true;
  gp_hash_table<int, bool> has;
  vector<pi> inter;
  bool can = false;
  for (int i = 0; i < m; i++)
  {
    int l = 0, r = k - 1;
    while (r < vv[i].size())
    {
      can = 1;
      has[v[i].get(l, r)] = 1;
      l++, r++;
    }
  }
  if (!can)
    return false;
  int l = 0, r = k - 1, sz = n + k;
  while (r < sz)
  {
    if (has[s.get(l, r)])
    {
      int ll = l + 1, rr = r;
      ll -= (ll >= n) ? n : 0;
      rr -= (rr >= n) ? n : 0;
      if (ll <= rr && k > 1)
        inter.pb({0, ll - 1}), inter.pb({rr + 1, n - 1});
      else if (k > 1)
        inter.pb({rr + 1, ll - 1});
      else
        inter.pb({0, n - 1});
    }
    l++, r++;
  }
  sort(inter.begin(), inter.end());
  for (int i = 0, j = 0; i < n; i++)
  {
    pi curr = {i, 1e6};
    while (j < inter.size() && inter[j] <= curr)
      j++;
    if (j == 0)
      return false;
    j--;
    if (!(i >= inter[j].fir && i <= inter[j].sec))
      return false;
  }
  return true;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m >> ss;
  ss = ss + ss;
  s = sh(ss);
  for (int i = 0; i < m; i++)
  {
    cin >> vv[i];
    v[i] = sh(vv[i]);
  }
  int l = 0, r = n;
  while (l < r)
  {
    int mid = (l + r + 1) >> 1;
    (can(mid)) ? l = mid : r = mid - 1;
  }
  cout << l << endl;
  return 0;
}