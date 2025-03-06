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
#define MAXN 500005
#define mod 998244353

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

pi get_line(pi x, pi y)
{
  int xx = x.fir - y.fir;
  int yy = x.sec - y.sec;
  int g = __gcd(abs(xx), abs(yy));
  if (g != 0)
  {
    xx /= g, yy /= g;
  }
  if (xx < 0)
  {
    xx *= -1;
    yy *= -1;
  }
  return {xx, yy};
}
void solve()
{
  int n;
  cin >> n;
  vector<pi> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].fir >> v[i].sec;
  }
  map<pi, int> mp;
  map<pi, int> repr;
  int cc = 0;
  // pega 2 indices i e j, e acha a reta que passa por esses 2 pontos
  while (cc < (2 * n))
  {
    cc++;
    int x = rng() % n;
    int y = rng() % n;
    if (x == y)
      continue;
    pi l = get_line(v[x], v[y]);
    mp[l]++;
    repr[l] = x;
  }
  vector<pii> vec;
  for (auto const &i : mp)
  {
    vec.pb({i.sec, i.fir});
  }
  sort(vec.rbegin(), vec.rend());
  // agora considerando as duas retas de maior frequencia
  // veja quantos pontos do conjunto estao nela
  int ans = n;
  for (int i = 0; i < min(2ll, (int)vec.size()); i++)
  {
    // guardo um "representante" dessa reta, que eu sei que ta nessa reta
    // pq dai eh so iterar por cada ponto e ver se o get_line bate com a reta que queremos
    int guy = repr[vec[i].sec];
    int cnt = 0;
    for (int j = 0; j < n; j++)
    {
      if (j == guy || get_line(v[guy], v[j]) == vec[i].sec)
        cnt++;
    }
    ans = min(ans, n - cnt);
  }
  cout << ans << endl;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  for (int i = 1; i <= q; i++)
  {
    cout << "Case #" << i << ": ";
    solve();
  }
  return 0;
}
// problema dahora
// https://www.facebook.com/codingcompetitions/hacker-cup/2024/practice-round/problems/C
// tem n pontos (x, y)
// ache a quantidade maxima de pontos, tal que, existe uma reta que passa por todos eles
// e imprima n - essa quantidade

// mas nao quero printar a resposta exata
// se a resposta otima for igual a m
// posso printar ate m * 2
// o que significa que da pra fazer umas heuristicas