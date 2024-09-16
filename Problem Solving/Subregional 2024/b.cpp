// codigo da hora da prova, ta horrivel
#include <bits/stdc++.h>

using namespace std;

// #define int long long int
#define pi pair<int, int>
#define pb push_back
#define fir first
#define sec second

int n, m;
int common[102][102]; // um ator que aparece nos filmes i e j
bool has[102][1000006];
bool reach[102][102];
int par[102][102];
vector<int> adj[102];
vector<int> g[102];

signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++)
  {
    int sz;
    cin >> sz;
    for (int j = 0; j < sz; j++)
    {
      int x;
      cin >> x;
      x--;
      has[i][x] = 1;
      adj[i].pb(x);
    }
    sort(adj[i].begin(), adj[i].end());
  }
  auto get = [&](int i, int j)
  {
    if (adj[i].size() > adj[j].size())
    {
      swap(i, j);
    }
    for (auto const &k : adj[i])
    {
      if (has[j][k])
        return k;
    }
    return -1;
  };
  for (int i = 0; i < n; i++)
  {
    for (int j = i; j < n; j++)
    {
      int curr = get(i, j);
      common[i][j] = curr;
      common[j][i] = curr;
      if (curr != -1)
      {
        g[i].pb(j);
        g[j].pb(i);
      }
    }
  }
  for (int ini = 0; ini < n; ini++)
  {
    reach[ini][ini] = 1;
    queue<int> q;
    q.push(ini);
    while (!q.empty())
    {
      int x = q.front();
      q.pop();
      for (int y = 0; y < n; y++)
      {
        if (!reach[ini][y] && common[x][y] != -1)
        {
          reach[ini][y] = 1;
          par[ini][y] = x;
          q.push(y);
        }
      }
    }
  }
  auto solve = [&](int a, int b)
  {
    for (int i = 0; i < n; i++)
    {
      if (has[i][a])
      {
        for (int j = 0; j < n; j++)
        {
          if (reach[i][j] && has[j][b])
          {
            vector<int> ans;
            int x = j;
            ans.pb(b);
            while (1)
            {
              ans.pb(x); // filme
              if (x == i)
                break;
              int nxt = par[i][x];
              ans.pb(common[x][nxt]); // ator
              x = nxt;
            }
            ans.pb(a);
            reverse(ans.begin(), ans.end());
            cout << (ans.size() + 1) / 2 << endl;
            for (auto const &i : ans)
              cout << i + 1 << " ";
            cout << endl;
            return;
          }
        }
      }
    }
    cout << "-1\n";
  };
  int q;
  cin >> q;
  while (q--)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    solve(a, b);
  }
  return 0;
}