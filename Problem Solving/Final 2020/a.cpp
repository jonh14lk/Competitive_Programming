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
#define MAXN 200001
#define mod 1000000007
#define INF 1e9

int m, n, lim;
vector<int> v;
vector<pi> ans;
vector<pi> path;

void solve(int i)
{
  if (find(v.begin(), v.end(), n) != v.end())
  {
    if (ans.size() > path.size())
      ans = path;
    return;
  }
  if (i == lim)
    return;
  vector<int> vv = v;
  for (auto const &j : vv)
  {
    int k = vv.back();
    if (j + k > n)
      continue;
    path.pb({1, j});
    path.pb({1, k});
    v.pb(j + k);
    solve(i + 1);
    path.pop_back();
    path.pop_back();
    v.pop_back();
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> m >> n;
  if (m != 1)
  {
    cout << "*\n";
    return 0;
  }
  lim = log2(n) + 3;
  ans.assign(50, {-1, -1});
  v.pb(1);
  solve(0);
  for (auto const &i : ans)
    cout << i.fir << " " << i.sec << endl;
  return 0;
}
// em um passo:
// duas linhas na diagonal:
// uma do canto inferior esquerdo para o ponto pr
// e outra do canto inferior direito para o ponto pl
// inicialmente, pl e pr só podem ser = 1
// com isso, uma linha eh desenhada no ponto de intersecção entre as duas retas
// e um novo valor de pl e de pr surgem, justamente esse ponto de intersecção

// a grande sacada:
// o valor do novo ponto vai ser sempre (pr * pl)/ pr + pl
// com isso:
// x = (1/a * 1/b)/ 1/a + 1/b
// x = 1 / a + b

// logo todos os valores vão ter a forma de x = 1 / k