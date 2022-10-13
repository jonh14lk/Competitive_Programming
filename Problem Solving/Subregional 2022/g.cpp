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
#define pii pair<pi, pi>
#define fir first
#define sec second
#define MAXN 400005
#define mod 1000000007

int id;
double p[MAXN];
double dp[MAXN][2];
map<pii, int> mp;
map<pii, bool> ok;
vector<pi> v[MAXN];
vector<int> adj[MAXN];

double cross(pi v, pi w)
{
  return v.fir * w.sec - v.sec * w.fir;
}
double area(pi p1, pi p2, pi p3)
{
  pi a = {p2.fir - p1.fir, p2.sec - p1.sec};
  pi b = {p3.fir - p2.fir, p3.sec - p2.sec};
  return abs(cross(a, b)) / 2.0;
}
void add(pi a, pi b, int i)
{
  if (a > b)
    swap(a, b);
  if (mp.count({a, b}))
  {
    adj[i].pb(mp[{a, b}]);
    adj[mp[{a, b}]].pb(i);
    ok[{a, b}] = 1;
  }
  else
  {
    mp[{a, b}] = i;
  }
}
void check(pi a, pi b, int i)
{
  if (a > b)
    swap(a, b);
  if (!ok[{a, b}])
  {
    adj[i].pb(id);
    adj[id].pb(i);
    p[id] = 1e13;
    id++;
  }
}
double solve(int i, int j, int par)
{
  if (dp[i][j] != -1)
    return dp[i][j];
  double ans = p[i];
  {
    for (auto const &k : adj[i])
    {
      if (k != par)
        ans += solve(k, 1, i);
    }
  }
  if (j == 1)
  {
    double ans2 = 0;
    for (auto const &k : adj[i])
    {
      if (k != par)
        ans2 += solve(k, 0, i);
    }
    ans = min(ans, ans2);
  }
  return dp[i][j] = ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    v[i].resize(3);
    for (int j = 0; j < 3; j++)
      cin >> v[i][j].fir >> v[i][j].sec;
    p[i] = area(v[i][0], v[i][1], v[i][2]);
    add(v[i][0], v[i][1], i);
    add(v[i][1], v[i][2], i);
    add(v[i][0], v[i][2], i);
  }
  id = n;
  for (int i = 0; i < n; i++)
  {
    check(v[i][0], v[i][1], i);
    check(v[i][1], v[i][2], i);
    check(v[i][0], v[i][2], i);
  }
  for (int i = 0; i < MAXN; i++)
  {
    dp[i][0] = -1;
    dp[i][1] = -1;
  }
  cout << fixed << setprecision(1) << solve(0, 1, -1) << endl;
  return 0;
}
// dada uma triangulação na qual:
// cada triangulo adicionado toca exatamente um lado de um triangulo adicionado anteriormente

// o grafo dual dessa triangulação vai ser uma arvore
// cada aresta no grafo dual eh equivalente a um lado de algum triangulo na triangulação

// dai quero remover alguns triangulos tal que:
// os "lados" continuem os mesmos
// a area total dos triangulos restantes seja minimizada

// ou seja:
// pensando em resolver pro grafo dual
// vai ser achar o minimum vertex cover
// tendo peso pros vertices

// pros lados que nao forem lados de dois triangulos
// tenho que por eles
// dai vou adicionar vertices fakes
// e peso infinito pra eles