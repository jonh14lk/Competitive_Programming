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
#define DEBUG 0
#define MAXN 1000001
#define mod 1000000007
#define mod2 8675309
#define d 619
#define d2 257

vector<int> pot(MAXN);
vector<int> pot2(MAXN);
set<pi> sufs, prefs;
map<pi, vector<pi>> appeared;
map<int, int> idx, idx2;

int modpow(int x, int y)
{
  int z = 1;
  while (y)
  {
    if (y & 1)
      z = (z * x) % mod;
    x = (x * x) % mod;
    y >>= 1;
  }
  return z;
}
int inverse(int x)
{
  return modpow(x, mod - 2);
}
int divide(int x, int y)
{
  return (x * inverse(y)) % mod;
}
int subtract(int x, int y)
{
  return ((x + mod) - y) % mod;
}
int multiplicate(int x, int y)
{
  return (x * y) % mod;
}
int sum(int x, int y)
{
  return (x + y) % mod;
}
void calc()
{
  pot[0] = 1, pot2[0] = 1;
  for (int i = 1; i < MAXN; i++)
  {
    pot[i] = multiplicate(pot[i - 1], d);
    pot2[i] = multiplicate(pot2[i - 1], d2);
  }
}
int rem(int complete, int pref, int l, int r)
{
  return divide(subtract(complete, pref), pot[l]);
}
int rem2(int complete, int pref, int l, int r)
{
  return divide(subtract(complete, pref), pot2[l]);
}
bool cmp(string a, string b)
{
  return a.size() < b.size();
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  calc();
  int n, m;
  cin >> n >> m;
  vector<string> v(n);
  vector<string> k(m);
  vector<bool> ansv(n, true);
  vector<bool> ansk(m, true);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  for (int i = 0; i < m; i++)
    cin >> k[i];
  sort(v.begin(), v.end(), cmp);
  sort(k.begin(), k.end(), cmp);
  for (int i = 0; i < n; i++)
  {
    int curr = 0, curr2 = 0, comp = 0, comp2 = 0, val;
    for (int j = 0; j < v[i].size(); j++) // hashing of complete word
    {
      val = multiplicate(v[i][j], pot[j]);
      comp = sum(comp, val);
      val = multiplicate(v[i][j], pot2[j]);
      comp2 = sum(comp2, val);
    }
    for (int j = 0; j < v[i].size(); j++) // hashing of prefixes
    {
      val = multiplicate(v[i][j], pot[j]);
      curr = sum(curr, val);
      val = multiplicate(v[i][j], pot2[j]);
      curr2 = sum(curr2, val);
      if (prefs.find({curr, curr2}) != prefs.end())
      {
        int a = rem(comp, curr, j + 1, v[i].size() - 1);
        int b = rem2(comp2, curr2, j + 1, v[i].size() - 1);
        appeared[{a, b}].pb({idx[curr], i});
      }
    }
    prefs.insert({comp, comp2});
    idx[comp] = i;
  }
  for (int i = 0; i < m; i++)
  {
    int pref = 0, pref2 = 0, curr = 0, curr2 = 0;
    int val, sz = k[i].size();
    for (int j = 0; j < k[i].size(); j++) // prefix hash
    {
      val = multiplicate(k[i][j], pot[j]);
      pref = sum(pref, val);
      val = multiplicate(k[i][j], pot2[j]);
      pref2 = sum(pref2, val);
    }
    for (int j = 0; j < k[i].size(); j++) // hashing of suffixes
    {
      val = multiplicate(k[i][sz - j - 1], pot[j]);
      curr = sum(curr, val);
      val = multiplicate(k[i][sz - j - 1], pot2[j]);
      curr2 = sum(curr2, val);
      val = multiplicate(k[i][sz - j - 1], pot[sz - j - 1]);
      pref = subtract(pref, val);
      val = multiplicate(k[i][sz - j - 1], pot2[sz - j - 1]);
      pref2 = subtract(pref2, val);
      if (sufs.find({curr, curr2}) != sufs.end())
      {
        pi back = {-1, -1};
        for (auto const &f : appeared[{pref, pref2}])
        {
          ansv[f.fir] = false;
          ansv[f.sec] = false;
          ansk[i] = false;
          ansk[idx2[curr]] = false;
          back = f;
        }
        if (back.fir != -1)
        {
          appeared[{pref, pref2}].clear();
          appeared[{pref, pref2}].pb(back);
        }
      }
    }
    sufs.insert({curr, curr2});
    idx2[curr] = i;
  }
  int ans = 0, ans2 = 0;
  for (auto const &i : ansv)
    ans += i;
  for (auto const &i : ansk)
    ans2 += i;
  cout << ans << " " << ans2 << endl;
  return 0;
}
