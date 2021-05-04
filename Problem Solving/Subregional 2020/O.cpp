#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 300005
#define mod 998244353
#define PI acos(-1)

int n;
vector<pi> v;
vector<pair<double, double>> sub;
vector<double> len;
vector<double> ori;

void prec()
{
  for (int i = 1; i <= n; i++)
  {
    sub.pb({(v[i].fir - v[i - 1].fir), (v[i].sec - v[i - 1].sec)});
    len.pb(sqrt((sub.back().fir * sub.back().fir) + (sub.back().sec * sub.back().sec)));
    ori.pb(atan2(sub.back().sec, sub.back().fir));
  }
}
double calc(double x)
{
  double ans = 0;
  for (int i = 0; i < n; i++)
  {
    double ang = x + ori[i];
    if (ang > PI)
      ang -= (2 * PI);
    if (ang < -PI)
      ang += (2 * PI);
    ans += (len[i] * max(0.00, cos(ang)));
  }
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  v.resize(n + 1);
  for (int i = 0; i < n; i++)
    cin >> v[i].fir >> v[i].sec;
  v[n] = v[0];
  prec();
  double l = -(2 * PI), r = 2 * PI;
  for (int i = 0; i < 70; i++)
  {
    double l1 = (l * 2 + r) / 3.0;
    double l2 = (l + 2 * r) / 3.0;
    double f1 = calc(l1);
    double f2 = calc(l2);
    if (f1 < f2)
      r = l2;
    else
      l = l1;
  }
  cout << setprecision(2) << fixed << calc(l) << endl;
  return 0;
}
// para cada line que esta no caminho do shuttle
// se considerarmos inicialmente que ele toma sol em qualquer lugar
// a quantidade de sol naquela line pode ser considerada como:
// L * cos(x + a)
// L -> distancia entre os pontos
// x -> local que voce escolheu
// a -> orientação da line atual
// nesse caso a soma de todos os (L * cos(x + a)) seria a resposta final
// mas temos que lembrar que, se o cos for <= 0, ele nao toma sol
// logo, para o calculo final, considerar apenas os cos positivos
// então temos uma primeira ideia
// percorrer todos os valores possiveis de x
// e ver qual o que da a menor soma de sol
// busca ternaria??
