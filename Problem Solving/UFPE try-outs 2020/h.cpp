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

int tempo[MAXN];
int t[MAXN];
bool visited[MAXN];
vector<pi> adj[MAXN];

void bfs(int s)
{
  queue<int> q;
  q.push(s);
  while (!q.empty())
  {
    int v = q.front();
    for (auto const &u : adj[v])
    {
      if (tempo[u.fir] > tempo[v] + u.sec + t[u.fir])
      {
        tempo[u.fir] = tempo[v] + u.sec + t[u.fir];
        q.push(u.fir);
      }
    }
    q.pop();
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 0; i < m; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    adj[a].pb({b, c});
    adj[b].pb({a, c});
  }
  for (int i = 0; i < n; i++)
  {
    cin >> t[i];
    tempo[i] = 1e15;
  }
  for (int i = 0; i < k; i++)
  {
    int a;
    cin >> a;
    a--;
    tempo[a] = t[a];
  }
  for (int i = 0; i < n; i++)
    if (!visited[i] && tempo[i] != 1e15)
      bfs(i);
  for (int i = 0; i < n; i++)
    cout << tempo[i] << endl;
}