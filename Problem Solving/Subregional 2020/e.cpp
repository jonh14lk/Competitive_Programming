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
#define pii pair<int, pi>
#define fir first
#define sec second
#define DEBUG 0
#define MAXN 100001
#define mod 1000000007

int esq, dir, n, q, l, timer;
vector<int> idade;
vector<int> ans;
vector<int> tin;
vector<int> tout;
vector<int> adj[MAXN];
vector<pi> party[MAXN];
vector<vector<int>> up;
ordered_set<pi> curr;

void dfs(int v, int p)
{
  timer++;
  tin[v] = timer;
  up[v][0] = p;
  for (int i = 1; i <= l; i++)
    up[v][i] = up[up[v][i - 1]][i - 1];
  for (auto const &u : adj[v])
    if (u != p)
      dfs(u, v);
  timer++;
  tout[v] = timer;
}
void preprocess(int root)
{
  ans.resize(n);
  tin.resize(n);
  tout.resize(n);
  timer = 0;
  l = ceil(log2(n));
  up.assign(n, vector<int>(l + 1));
  dfs(root, root);
}
int binarylifting(int u)
{
  for (int i = l; i >= 0; i--)
    if (idade[up[u][i]] >= esq && idade[up[u][i]] <= dir)
      u = up[u][i];
  return u;
}
void dfs2(int v, int p)
{
  for (auto const &i : party[v])
    curr.insert(i);
  ans[v] = curr.order_of_key({idade[v] + 1, -1});
  for (auto const &i : adj[v])
    if (i != p)
      dfs2(i, v);
  for (auto const &i : party[v])
    curr.erase(i);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> q;
  idade.resize(n);
  for (int i = 0; i < n; i++)
  {
    int a, b;
    cin >> a >> b;
    b--;
    idade[i] = a;
    if (i != b)
    {
      adj[i].pb(b);
      adj[b].pb(i);
    }
  }
  preprocess(0);
  for (int i = 0; i < q; i++)
  {
    int parent, a;
    cin >> a >> esq >> dir;
    parent = binarylifting(a - 1);
    party[parent].pb({esq, i});
  }
  dfs2(0, 0);
  for (auto const &i : ans)
    cout << i << " ";
  cout << endl;
  return 0;
}