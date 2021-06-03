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
#define MAXN 100005
#define mod 998244353
#define PI acos(-1)

struct point
{
  int x, y, b;
};

point sub(point a, point b)
{
  return {a.x - b.x, a.y - b.y, -1};
}
bool cmp(point a, point b)
{
  double ang = atan2l(a.y, a.x);
  double ang2 = atan2l(b.y, b.x);
  return (ang < ang2);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<point> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i].x >> v[i].y >> v[i].b;
  vector<point> c;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (v[i].b > v[j].b)
        c.pb(sub(v[i], v[j]));
  sort(c.begin(), c.end(), cmp);
  if (c.size() < 2)
  {
    cout << "Y\n";
    exit(0);
  }
  vector<double> kappa;
  kappa.pb(atan2l(c.back().y, c.back().x) - (2 * PI));
  for (auto const &i : c)
  {
    double ang = atan2l(i.y, i.x);
    double ang2 = kappa.back();
    if (ang - ang2 >= PI)
    {
      cout << "Y\n";
      exit(0);
    }
    kappa.pb(ang);
  }
  cout << "N\n";
  return 0;
}
// dado n pontos, preciso saber se existe um jeito de rotacionar o plano tal que
// para cada um dos n pontos, se ordenarmos os pontos pela coordenada y de modo decrescente
// o brilho das estelas tbm vai tar de maneira decrescente

// com isso, para checar:
// 1 - itera pelos pares no qual o brilho da estela i eh maior do que o brilho da estela j
// 2 - para cada par desse, subtrai os dois pontos e acha o angulo desse ponto
// 3 - ordena o vector contendo os angulos de maneira crescente
// 4 - se para um par adjacente, a diferença entre os angulos deles eh >= 180 graus (PI rad), a resposta eh yes
// 5 - caso contrario, se esse par nao existir, a resposta eh no