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
#define MAXN 500001
#define mod 1000000007

int n;
string s;

bool can(int k)
{
  int g = __gcd(n, k);
  vector<int> adj[g];
  for (int i = 0; i < n; i++)
  {
    adj[i % g].pb(i);
  }
  for (auto const &v : adj)
  {
    bool can = 1;
    for (auto const &j : v)
      can &= (s[j] == 'R');
    if (can)
      return 1;
  }
  return 0;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> s;
  n = s.size();
  vector<bool> vis(n, false);
  vector<int> dp(n, 0);
  for (int i = 1; i < n; i++)
  {
    int g = __gcd(i, n);
    if (vis[g])
      continue;
    vis[g] = 1;
    if (can(i))
    {
      for (int j = i; j < n; j += i)
        dp[j] = 1;
    }
  }
  int ans = 0;
  for (int i = 1; i < n; i++)
    ans += dp[i];
  cout << ans << endl;
  return 0;
}
// se eu consigo pra um numero
// consigo para todos os multiplos dele
// como checar se consigo para um valor de k?

// para checar:
// imagina um grafo no qual, existe uma aresta de um nó i pra j
// se saindo de i eu consigo chegar em j com um ou mais pulos

// com isso:
// todos os pares de nós (i, j) vão tar na mesma componente se
// i % gcd(k, n) == j % gcd(k, n)
// no final pra saber se eh possivel para um valor de k
// resta saber se pelo menos
// uma dessas componentes eh formada somente por "R"