#include <bits/stdc++.h>
using namespace std;
 
#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 100001
#define mod 1000000007
 
int n, m, q;
map<string, int> vol;
vector<int> bit;
vector<string> vv;
vector<int> v;
 
int sum(int r)
{
  int ret = 0;
  for (; r >= 0; r = (r & (r + 1)) - 1)
    ret += bit[r];
  return ret;
}
void add(int idx, int delta)
{
  for (; idx < n; idx = idx | (idx + 1))
    bit[idx] += delta;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m >> q;
  vv.resize(n);
  v.resize(n);
  bit.assign(n, 0);
  for (int i = 0; i < n; i++)
    cin >> vv[i];
  for (int i = 0; i < m; i++)
  {
    string a;
    int b;
    cin >> a >> b;
    vol[a] = b;
  }
  for (int i = 0; i < n; i++)
  {
    v[i] = vol[vv[i]];
    add(i, v[i]);
  }
  while (q--)
  {
    int t;
    cin >> t;
    if (t == 1)
    {
      string a;
      int b;
      cin >> b >> a;
      b--;
      add(b, vol[a] - v[b]);
      v[b] = vol[a];
    }
    else
    {
      int l, r;
      cin >> l >> r;
      l--, r--;
      int ans = sum(r) - sum(l - 1);
      double eps = ans, limit = ((r - l + 1) * 60);
      limit = limit / 2;
      (eps <= limit) ? cout << "NO\n" : cout << "YES\n";
    }
  }
  return 0;
}