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
#define MAXN 1005
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> tin(n);
  vector<int> tout(n);
  for (int i = 0; i < (2 * n); i++)
  {
    char c;
    int x;
    cin >> c >> x;
    x--;
    if (c == '+')
      tin[x] = i;
    else
      tout[x] = i;
  }
  auto cannot = [&](int i, int j)
  {
    return (tin[i] < tin[j] && tout[i] < tout[j] && tout[i] > tin[j]);
  };
  vector<vector<int>> adj(n);
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (i != j && cannot(i, j))
      {
        adj[i].pb(j);
        adj[j].pb(i);
      }
    }
  }
  bool is = 1;
  vector<int> c(n, -1);
  queue<int> q;
  for (int st = 0; st < n; st++)
  {
    if (c[st] == -1)
    {
      q.push(st);
      c[st] = 0;
      while (!q.empty())
      {
        int v = q.front();
        q.pop();
        for (auto const &u : adj[v])
        {
          if (c[u] == -1)
          {
            c[u] = c[v] ^ 1;
            q.push(u);
          }
          else
          {
            is &= c[u] != c[v];
          }
        }
      }
    }
  }
  if (!is)
  {
    cout << "*\n";
    return 0;
  }
  for (int i = 0; i < n; i++)
  {
    cout << "GS"[c[i] == 0];
  }
  cout << endl;
}