#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define pb push_back
#define int long long int
#define mp make_pair
#define pi pair<int, int>
#define pii pair<pi, int>
#define pci pair<char, int>
#define fir first
#define sec second
#define MAXN 100001
#define MAXL 20
#define mod 1000000007

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
void get_suf(string s)
{
  s += '$';
  int n = s.size();
  vector<int> p(n), c(n);
  vector<pci> a(n);
  for (int i = 0; i < n; i++)
    a[i] = mp(s[i], i);
  sort(a.begin(), a.end());
  for (int i = 0; i < n; i++)
    p[i] = a[i].sec;
  c[p[0]] = 0;
  for (int i = 1; i < n; i++)
    (a[i].fir == a[i - 1].fir) ? c[p[i]] = c[p[i - 1]] : c[p[i]] = c[p[i - 1]] + 1;
  int k = 0;
  while ((1 << k) < n)
  {
    vector<pii> v(n);
    for (int i = 0; i < n; i++)
      v[i] = mp(mp(c[i], c[(i + (1 << k)) % n]), i);
    radix(v);
    for (int i = 0; i < n; i++)
      p[i] = v[i].sec;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++)
      (v[i].fir == v[i - 1].fir) ? c[p[i]] = c[p[i - 1]] : c[p[i]] = c[p[i - 1]] + 1;
    k++;
  }
  for (int i = 0; i < n; i++)
    cout << p[i] << " ";
  cout << endl;
}
signed main()
{
  string s;
  cin >> s;
  get_suf(s);
  return 0;
}
