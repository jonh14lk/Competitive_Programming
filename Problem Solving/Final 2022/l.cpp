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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 1005
#define mod 1000000009

struct modint
{
  int val;
  modint(int v = 0) { val = v % mod; }
  int operator*(modint o) { return ((val * o.val) % mod); }
  int operator+(modint o) { return (val + o.val) % mod; }
  int operator-(modint o) { return (val - o.val + mod) % mod; }
};
struct string_hashing
{
  modint d;
  modint h;
  vector<modint> pref;
  vector<modint> pot;
  string_hashing() {}
  string_hashing(int base, string &s)
  {
    d = base;
    pref.resize(s.size() + 1);
    pref[0] = 0;
    for (int i = 0; i < s.size(); i++)
    {
      modint val = pref[i] * d;
      pref[i + 1] = val + s[i];
    }
    h = pref[s.size()];
    pot.resize(s.size() + 1);
    pot[0] = 1;
    for (int i = 1; i <= s.size(); i++)
      pot[i] = pot[i - 1] * d;
  }
  modint get(int l, int r)
  {
    return pref[r + 1] - (pref[l] * pot[r - l + 1]);
  }
  modint append(modint hh, modint hb, int blen)
  {
    hh = hb + (hh * pot[blen]);
    return hh;
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  int d;
  cin >> s >> d;
  string_hashing sh(256, s);
  int n = s.size();
  int ans = 0;
  int x = 0;
  while (x < n)
  {
    ans++;
    int nxt = x; // começando de x, vai o mais pra direita que eu conseguir
    for (int i = 1; i <= d; i++)
    {
      int l = x, r = n - 1;
      while (l < r)
      {
        int mid = (l + r + 1) >> 1;
        int len = mid - x + 1;
        if (len <= i)
        {
          l = mid;
          continue;
        }
        // checar se a substring [x, mid] eh periodica
        (sh.get(x, mid - i).val == sh.get(x + i, mid).val) ? l = mid : r = mid - 1;
      }
      nxt = max(nxt, l + 1);
    }
    x = nxt;
  }
  cout << ans << endl;
}
// checar se a string s eh periodica de t
// s[i] = t[i % m]

// no pior caso a resposta vai ser ceil(n / d)