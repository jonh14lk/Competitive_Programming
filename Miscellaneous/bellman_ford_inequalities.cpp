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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 4005

const int inf = 1e18;
vector<int> d;

bool bellman_ford(int n, int src, vector<pii> &edges)
{
  d.assign(n, inf);
  d[src] = 0;
  int x;
  for (int i = 0; i < n; i++)
  {
    x = -1;
    for (auto const &e : edges)
    {
      auto [a, b] = e.fir;
      int cost = e.sec;
      if (d[a] < inf)
      {
        if (d[b] > d[a] + cost)
        {
          d[b] = max(-inf, d[a] + cost);
          x = b;
        }
      }
    }
  }
  return (x != -1); // se tem ciclo negativo
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  int source = n + 1;
  vector<pii> edges;
  auto add_constraint = [&](int i, int j, int c)
  {
    // pref[i] - pref[j] <= c
    edges.pb({{j, i}, c});
  };
  for (int i = 0; i <= n; i++)
  {
    edges.pb({{source, i}, 0}); // liga o source a todos os demais
  }
  for (int i = 0; i < m; i++)
  {
    // pref[r] - pref[l - 1] = c
    // eh equivalente a: (pref[r] - pref[l - 1] <= c) e (pref[r] - pref[l - 1] >= c)
    // ou seja: (pref[r] - pref[l - 1] <= c) e (pref[l - 1] - pref[r] <= -c)
    int l, r, c;
    cin >> l >> r >> c;
    add_constraint(r, l - 1, c);  // pref[r] - pref[l - 1] <= c
    add_constraint(l - 1, r, -c); // pref[l - 1] - pref[r] <= -c
  }
  for (int i = 1; i <= n; i++)
  {
    // pref[i] - pref[i - 1] >= 1, ja q os numeros tem que ser positivos
    // pref[i - 1] - pref[i] <= -1
    add_constraint(i - 1, i, -1);
  }
  if (bellman_ford(n + 2, source, edges))
  {
    cout << "-1\n";
    return 0;
  }
  // pref[0] tem que ser zero
  // e eu sei q minimizamos d[n] - d[0]
  // entao se eu faco pref[i] = d[i] - d[0], sei que pref[0] vai ser igual a zero
  // e pref[n] vai ser a soma do array inteiro, gg
  cout << d[n] - d[0] << endl;
  return 0;
}
// https://web.stanford.edu/class/cs97si/07-shortest-path-algorithms.pdf (slide 15)
// https://atcoder.jp/contests/abc404/tasks/abc404_g
// http://poj.org/problem?id=3169

/*
se vc tem um problema de programacao linear que eh algo do tipo:

vc tem variaveis x[0], x[1], ..., x[n]

o que vc quer eh:

minimizar max(x[i]) - min(x[i])

sujeito a varias restricoes, a i-esima restrição eh representada por uma tripla (a[i], b[i], c[i]) e tem a forma: x[a[i]] - x[b[i]] <= c[i]

isso pode ser resolvido com bellman ford
*/