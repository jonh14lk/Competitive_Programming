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
#define mod 1000000007
#define INF 1e9

string v[302];
int cnt[302];
int lb[302];
int f[302][302];
int valid[302];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  map<string, int> mp;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    mp[v[i]] = i;
  }
  int q;
  cin >> q;
  while (q--)
  {
    int sz, w;
    cin >> sz >> w;
    w--;
    cnt[w]++;
    while (sz--)
    {
      string s;
      cin >> s;
      f[mp[s]][w]++;
      lb[mp[s]] = max(lb[mp[s]], w);
    }
  }
  vector<bool> used(n, 0);
  vector<int> resp(n, -1);
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (f[j][i] == cnt[i])
        valid[j]++;
    }
  }
  for (int i = 0; i < n; i++)
  {
    int c = -1, x = 1e9;
    for (int j = 0; j < n; j++)
    {
      if (f[j][i] == cnt[i] && valid[j] < x && lb[j] <= i)
      {
        c = j;
        x = valid[j];
      }
    }
    cout << v[c] << " ";
    valid[c] = 1e9;
    for (int j = 0; j < n; j++)
    {
      if (f[j][i] == cnt[i])
        valid[j]--;
    }
  }
  cout << endl;
}