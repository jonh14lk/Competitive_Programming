#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 10005
#define mod 1000000007

int n, m;
vector<pii> edges; // arestas directed
const int inf = 1e18;

// retorna true se tem ciclo negativo e que eh reachable a partir do vertice 0
bool bellman_ford()
{
  vector<int> d(n, inf);
  d[0] = 0;
  int x;
  for (int i = 0; i < n; i++)
  {
    x = -1;
    for (auto const &e : edges)
    {
      auto [a, b] = e.fir;
      int cost = e.sec;
      if (d[a] < inf && d[b] > (d[a] + cost))
      {
        d[b] = d[a] + cost;
        x = b;
      }
    }
    if (x == -1)
      return false;
  }
  return true;
}
// retorna true se tem ciclo negativo em qualquer lugar do grafo
bool bellman_ford_2()
{
  vector<int> d(n, 0);
  int x;
  for (int i = 0; i < n; i++)
  {
    x = -1;
    for (auto const &e : edges)
    {
      auto [a, b] = e.fir;
      int cost = e.sec;
      if (d[b] > (d[a] + cost))
      {
        d[b] = d[a] + cost;
        x = b;
      }
    }
    if (x == -1)
      return false;
  }
  return true;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}