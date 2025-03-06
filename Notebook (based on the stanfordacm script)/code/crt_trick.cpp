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
#define MAXN 200005

vector<pi> eq;
map<int, int> by_mod;

bool check(pi curr)
{
  if (by_mod.find(curr.sec) != by_mod.end())
  {
    return by_mod[curr.sec] == curr.fir;
  }
  // no maximo O(sqrt(n)) mods distintos
  // ja que tem O(sqrt(n)) tamanhos de ciclos distintos na permutacao
  // ja que a soma dos tamanhos dos ciclos da permutacao eh igual a n
  for (auto [x, mod] : eq)
  {
    if ((curr.fir - x) % __gcd(curr.sec, mod))
      return 0;
  }
  return 1;
}
void add(pi curr)
{
  eq.pb(curr);
  by_mod[curr.sec] = curr.fir;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> p(n);
  for (int i = 0; i < n; i++)
  {
    cin >> p[i];
    p[i]--;
  }
  vector<int> a(n);
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
    a[i]--;
  }
  vector<bool> vis(n, 0);
  vector<int> comp(n);
  vector<int> pos(n);
  vector<vector<int>> vals(n);
  vector<vector<int>> vals2(n);
  for (int i = 0; i < n; i++)
  {
    if (!vis[i])
    {
      int x = i;
      while (!vis[x])
      {
        vis[x] = 1;
        comp[x] = i;
        pos[x] = vals[i].size();
        vals[i].pb(a[x]);
        vals2[i].pb(x);
        x = p[x];
      }
    }
  }
  set<int> st;
  vector<int> resp(n);
  for (int i = 0; i < n; i++)
  {
    if (st.find(comp[i]) == st.end())
    {
      st.insert(comp[i]);
      int x = comp[i];
      int sz = vals[x].size();
      int mn = 1e18, op = -1;
      for (int i = 0; i < sz; i++)
      {
        // numeros x tal que x % sz = i
        if (check({i, sz}) && vals[x][i] < mn)
        {
          mn = vals[x][i];
          op = i;
        }
      }
      for (int i = 0; i < sz; i++)
      {
        resp[vals2[x][i]] = vals[x][op];
        op = (op + 1) % sz;
      }
      add({op, sz});
    }
  }
  for (auto const &i : resp)
  {
    cout << i + 1 << " ";
  }
  cout << endl;
}
// a[i] -> a[p[i]]
// i -> p[i]
// tenho varios ciclos
// e quero minimizar lexocograficamente a permutacao
// o que eu quero e:
// para cada ciclo da permutacao, ver se em um dado momento do ciclo
// eh possivel satisfazer o sistema de equacoes modulares

// dado um sistema com duas equacoes modulares
// x == n1 (mod m1)
// x == n2 (mod m2)
// existe solucao se (n1 - n2) % gcd(m1, m2) == 0

// para n equacoes podemos fazer esse check
// iterando por todos os pares de equacoes
// e checando se todo par satisfaz

// se eu ja tenho n equacoes no conjunto
// e eu sei que esse sistema de n equacoes tem solucao
// entao pra adicionar mais uma
// so preciso checar iterando pelas as que ja existem e dale