// dada uma sequencia s qual a maior soma que podemos obter escolhendo um subconjunto de termos adjacentes de s
// nesse caso o temos apenas duas opções
// não usar o elemento v[i]
// ou
// usamos, adicionando a maior soma possível que antes dele
#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define in insert
#define pi pair<int, int>
#define pd pair<double, int>
#define pib pair<pi, bool>
#define mp make_pair
#define fir first
#define sec second
#define MAXN 200001
#define MAXL 10001
#define mod 1000000007

signed main()
{
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  int ans = 0, at = 0;
  for (int i = 0; i < v.size(); i++)
  {
    at = max(0, at + v[i]);
    ans = max(at, ans);
  }
  cout << ans << endl;
  return 0;
}
