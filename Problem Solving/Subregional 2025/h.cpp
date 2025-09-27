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
#define mod 998244353

vector<int> fwht(char op, vector<int> f, bool inv = 0)
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
          f[j] += f[i], f[i] = f[j] - 2 * f[i];
        if (op == '|')
          f[i] += (inv ? -1 : 1) * f[j];
        if (op == '&')
          f[j] += (inv ? -1 : 1) * f[i];
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
vector<int> conv(char op, vector<int> a, vector<int> b)
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
  int n, k;
  cin >> n >> k;
  vector<int> cnt(1ll << k, 0);
  for (int i = 0; i < n; i++)
  {
    string s;
    cin >> s;
    int x = 0;
    for (int j = 0; j < k; j++)
    {
      if (s[j] == '1')
        x += (1ll << j);
    }
    cnt[x]++;
  }
  vector<int> duplas = conv('|', cnt, cnt);
  for (int i = 0; i < (1 << k); i++)
  {
    duplas[i] -= cnt[i];
    duplas[i] /= 2;
  }
  vector<int> triplas = conv('|', duplas, cnt);
  for (int i = 0; i < (1 << k); i++)
  {
    triplas[i] -= (duplas[i] * 2);
    triplas[i] /= 3;
  }
  int m;
  cin >> m;
  while (m--)
  {
    string s;
    cin >> s;
    int x = 0;
    for (int j = 0; j < k; j++)
    {
      if (s[j] == '1')
        x += (1ll << j);
    }
    cout << triplas[x] << endl;
  }
  return 0;
}