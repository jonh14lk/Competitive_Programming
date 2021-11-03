#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 300005

int id = 1;
vector<int> adj[MAXN];
bool vis[MAXN];
queue<int> qq;

void dfs(int s)
{
  qq.push(s);
  for (auto const &i : adj[s])
    dfs(i);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  vector<int> queries;
  while (q--)
  {
    int a, b;
    cin >> a >> b;
    b--;
    if (a == 1)
      adj[b].pb({id++});
    else
      queries.pb(b);
  }
  dfs(0);
  for (auto const &i : queries)
  {
    vis[i] = 1;
    while (vis[qq.front()])
      qq.pop();
    cout << qq.front() + 1 << endl;
  }
  return 0;
}