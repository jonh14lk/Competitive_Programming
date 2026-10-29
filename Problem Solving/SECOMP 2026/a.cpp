
#include <bits/stdc++.h>
using namespace std;

#define int long long int

int n;
string s;
vector<int> graph[200005];
bool visited[200005];

int dfs(int vertex, char os)
{
  visited[vertex] = true;
  int diff = 0;
  if (os != s[vertex])
  {
    diff++;
  }
  char other_os = (os == 'W') ? 'L' : 'W';
  for (auto to : graph[vertex])
  {
    if (!visited[to])
      diff += dfs(to, other_os);
  }
  return diff;
}
signed main()
{
  cin >> n >> s;
  for (int i = 0; i < (n - 1); i++)
  {
    int u, v;
    cin >> u >> v;
    u--, v--;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  int diff = dfs(0, 'W');
  cout << min(diff, n - diff) << endl;
}