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
#define pci pair<char, int>
#define fir first
#define sec second
#define MAXN 500001
#define mod 1000000007

struct suffix_array
{
  int n, k;
  string s;
  vector<int> p, c, lcp;
  vector<pci> a;

  void radix(vector<pii> &v)
  {
    {
      int n = v.size();
      vector<int> cnt(n);
      for (auto const &i : v)
        cnt[i.fir.sec]++;
      vector<pii> ans(n);
      vector<int> pos(n);
      pos[0] = 0;
      for (int i = 1; i < n; i++)
        pos[i] = pos[i - 1] + cnt[i - 1];
      for (auto const &i : v)
      {
        int k = i.fir.sec;
        ans[pos[k]] = i;
        pos[k]++;
      }
      v = ans;
    }
    {
      int n = v.size();
      vector<int> cnt(n);
      for (auto const &i : v)
        cnt[i.fir.fir]++;
      vector<pii> ans(n);
      vector<int> pos(n);
      pos[0] = 0;
      for (int i = 1; i < n; i++)
        pos[i] = pos[i - 1] + cnt[i - 1];
      for (auto const &i : v)
      {
        int k = i.fir.fir;
        ans[pos[k]] = i;
        pos[k]++;
      }
      v = ans;
    }
  }
  suffix_array(string &st)
  {
    s = st;
    s += '$'; // menor do que todos os chars da string st
    n = s.size();
    p.resize(n);
    c.resize(n);
    a.resize(n);
    for (int i = 0; i < n; i++)
      a[i] = {s[i], i};
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++)
      p[i] = a[i].sec;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++)
      (a[i].fir == a[i - 1].fir) ? c[p[i]] = c[p[i - 1]] : c[p[i]] = c[p[i - 1]] + 1;
    k = 0;
    while ((1 << k) < n)
    {
      vector<pii> v(n);
      for (int i = 0; i < n; i++)
        v[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
      radix(v); // pode usar std::sort()
      for (int i = 0; i < n; i++)
        p[i] = v[i].sec;
      c[p[0]] = 0;
      for (int i = 1; i < n; i++)
        (v[i].fir == v[i - 1].fir) ? c[p[i]] = c[p[i - 1]] : c[p[i]] = c[p[i - 1]] + 1;
      k++;
    }
  }
  void build_lcp()
  {
    lcp.resize(n);
    k = 0;
    for (int i = 0; i < n - 1; i++)
    {
      int idx = c[i], j = p[idx - 1];
      while (s[i + k] == s[j + k])
        k++;
      lcp[idx] = k;
      k = max(k - 1, 0ll);
    }
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  int n = s.size();
  suffix_array sa(s);
  for (int i = 0; i <= s.size(); i++) // sufix array
    cout << sa.p[i] << " ";
  cout << endl;
  sa.build_lcp();
  for (int i = 1; i <= s.size(); i++) // lcp entre 2 suffixos adjacentes no suffix array
    cout << sa.lcp[i] << " ";
  cout << endl;
  // queries de dada uma string t, diga quantas occorrencias tem de t como substring em s
  int q;
  cin >> q;
  while (q--)
  {
    string t;
    cin >> t;
    int i = 0, f = n, m, lb, ub;
    while (i < f)
    {
      m = (i + f) / 2;
      (t <= s.substr(sa.p[m], t.size())) ? f = m : i = m + 1;
    }
    ub = i, i = 0, f = n;
    while (i < f)
    {
      m = (i + f) / 2;
      (t >= s.substr(sa.p[m], t.size())) ? i = m + 1 : f = m;
    }
    lb = i;
    if (s.substr(sa.p[lb], t.size()) == t)
      lb++;
    cout << lb - ub << endl;
  }
  return 0;
}
