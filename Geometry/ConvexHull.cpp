#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define int long long int
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 100001
#define MAXL 512
#define INF 200001
#define mod 1000000007

struct pt
{
  double x, y;
  pt operator+(pt p) { return {x + p.x, y + p.y}; }
  pt operator-(pt p) { return {x - p.x, y - p.y}; }
  pt operator*(double d) { return {x * d, y * d}; }
  pt operator/(double d) { return {x / d, y / d}; }
};
bool cmp(pt a, pt b) // ordenar os n pontos pela cordenada x
{
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}
bool cw(pt a, pt b, pt c) // verificar se os pontos estao no sentido horario (clockwise)
{
  return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0;
}
bool ccw(pt a, pt b, pt c) // verificar se os pontos estao no sentido anti-horario (counter clockwise)
{
  return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0;
}
void convex_hull(vector<pt> v)
{
  sort(v.begin(), v.end(), cmp);
  pt p1 = v[0];
  pt p2 = v[v.size() - 1];
  vector<pt> up;
  vector<pt> down;
  up.pb(p1);
  down.pb(p1);
  for (int i = 1; i < v.size(); i++)
  {
    if (i == v.size() - 1 || cw(p1, v[i], p2))
    {
      while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], v[i]))
        up.pop_back();
      up.pb(v[i]);
    }
  }
  for (int i = 1; i < v.size(); i++)
  {
    if (i == v.size() - 1 || ccw(p1, v[i], p2))
    {
      while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], v[i]))
        down.pop_back();
      down.pb(v[i]);
    }
  }
  int start = 0, limit = 0; // para printar no sentido anti-horario e a partir de start
  for (int i = 1; i < down.size(); i++)
    if ((down[i].y < down[start].y) || (down[i].y == down[start].y && down[i].x < down[start].x))
      start = i;
  if (!start)
    limit = 1;
  vector<pt> ans;
  for (int i = start; i < down.size() - 1; i++)
    ans.pb(down[i]);
  for (int i = up.size() - 1; i >= limit; i--)
    ans.pb(up[i]);
  for (int i = 1; i < start; i++)
    ans.pb(down[i]);
  for (auto const &i : ans)
    cout << i.x << " " << i.y << endl;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  int t = 0;
  while (cin >> n)
  {
    vector<pt> v(n);
    for (int i = 0; i < n; i++)
      cin >> v[i].x >> v[i].y;
    convex_hull(v);
    cout << endl;
    t++;
  }
}

// conceitos importantes:
// 1- poligono: uma figura plana que possui no minimo 3 lados e 3 angulos
// 2- poligono convexo: um poligono cujo todos os seus angulos internos são menores do que 180 graus

// convex hull:
// dados n pontos em um plano, o objetivo é achar o menor polígono convexo que possui todos os n pontos dados
// Graham's Scan, complexidade O(n * log(n))

// ideia do algoritimo:
// 1- ache 2 pontos a e b tal que, a é o ponto mais a esquerda e b o ponto mais a direita do conjunto dado
// 2- a e b devem pertencer ao convex hull
// 3- desenhar uma linha ab, essa linha irá separar os outros pontos em 2 conjuntos s1 (superior) e s2 (inferior).
// 4- a e b pertencem aos dois conjuntos
// 5- agora para os conjuntos s1 e s2, achamos o convex hull dos dois conjuntos.
// 6- para isso, ordene todos os pontos pela cordenada x
// 7- para cada ponto, se o ponto dado pertence ao conjunto superior, verificamos o ângulo formado pela linha
//    que liga o penúltimo ponto e o último ponto do convex hull superior, com a linha que conecta o
//    último ponto do convex hull e o ponto atual. Se o ângulo não for no sentido horário,
//    removemos o ponto mais recente adicionado ao convex hull superior, pois o ponto atual será capaz
//    de conter o ponto anterior, uma vez que seja adicionado ao convex hull.
// 8- fazer o mesmo para o conjunto inferior
// 9- ao final teremos o conjunto de pontos que formam o convex hull dos n pontos
