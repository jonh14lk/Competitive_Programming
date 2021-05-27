#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define mp make_pair
#define pi pair<int, int>
#define pii pair<pi, int>
#define pci pair<char, int>
#define fir first
#define sec second
#define DEBUG 0
#define MAXN 150001
#define mod 1000000007
#define d 31

string s;
vector<int> v;

vector<int> get_suf(string s)
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
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++)
      p[i] = v[i].sec;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++)
      (v[i].fir == v[i - 1].fir) ? c[p[i]] = c[p[i - 1]] : c[p[i]] = c[p[i - 1]] + 1;
    k++;
  }
  return p;
}
bool ok(string t)
{
  int i = 0, f = s.size(), m;
  while (i <= f)
  {
    m = (i + f) >> 1;
    if (s.substr(v[m], t.size()) == t)
      return true;
    if (s.substr(v[m], t.size()) < t)
      i = m + 1;
    if (s.substr(v[m], t.size()) > t)
      f = m - 1;
  }
  return false;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> s;
  v = get_suf(s);
  int q;
  cin >> q;
  while (q--)
  {
    string t;
    cin >> t;
    int m = t.size(), ans = 1;
    for (int l = 0, r = 0; r < m;)
    {
      if (ok(t.substr(l, (r - l) + 1)))
      {
        r++;
      }
      else if (!(r - l))
      {
        ans = -1;
        break;
      }
      else
      {
        ans++;
        l = r;
        r = r;
      }
    }
    cout << ans << endl;
  }
  return 0;
}