#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 10001
#define mod 1000000007

int n, r;
vector<int> adj[MAXN];
int t[MAXN];

int dfs(int s, int f)
{
  vector<int> vec;
  for (auto const &v : adj[s])
  {
    if (v != f)
    {
      int at = 1 + dfs(v, s);
      vec.pb(at);
    }
  }
  sort(vec.rbegin(), vec.rend());
  int ans = 0, inc = 0;
  for (auto const &i : vec)
  {
    int curr = i + inc;
    ans = max(ans, curr);
    inc++;
  }
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    cin >> n >> r;
    r--;
    for (int i = 0; i < MAXN; i++)
    {
      adj[i].clear();
      t[i] = 0;
    }
    for (int i = 0; i < n - 1; i++)
    {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a].pb(b);
      adj[b].pb(a);
    }
    cout << dfs(r, -1) << endl;
  }
}