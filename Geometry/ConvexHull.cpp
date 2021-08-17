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
#define MAXN 500001
#define mod 1000000007
#define PI acos(-1)

namespace p
{
  struct pt
  {
    double x, y;
    pt operator+(pt p) { return {x + p.x, y + p.y}; } // soma de pontos
    pt operator-(pt p) { return {x - p.x, y - p.y}; } // subtração de pontos
    pt operator*(double d) { return {x * d, y * d}; } // multiplicação por um double
    pt operator/(double d) { return {x / d, y / d}; } // divisão por um double
  };
  double dot(pt v, pt w) // produto escalar (dot product)
  {
    return v.x * w.x + v.y * w.y;
  }
  bool is_perp(pt v, pt w) // retorna se dois vetores sao perpendiculares (angulo 90 graus)
  {
    return dot(v, w) == 0;
  }
  double cross(pt v, pt w) // produto vetorial (cross product)
  {
    return v.x * w.y - v.y * w.x;
  }
  double dist(pt a, pt b) // distancia entre 2 pontos
  {
    pt c = a - b;
    return sqrt(c.x * c.x + c.y * c.y);
  }
  double dist2(pt a, pt b) // retorna o quadrado da distancia entre dois pontos
  {
    pt c = a - b;
    return c.x * c.x + c.y * c.y;
  }
  bool is_colinear(pt a, pt b, pt c) // retorna se os pontos a, b e c são colineares
  {
    return cross(b - a, c - a) == 0;
  }
  bool ccw(pt a, pt b, pt c) // retorna se os pontos a,b e c estão no sentido anti horario
  {
    return cross(b - a, c - b) > 0;
  }
  bool cw(pt a, pt b, pt c) // retorna se os pontos a,b e c estão no sentido horario
  {
    return cross(b - a, c - b) < 0;
  }
  double modulo(pt v) // |v| = sqrt(x² + y²)
  {
    return sqrt(v.x * v.x + v.y * v.y);
  }
  double angle(pt a, pt b, pt c) // angulo entre os vetores ab e ac
  {
    // dot(ab , ac) / |ab| * |ac|
    pt ab = b - a; // vetor ab
    pt ac = c - a; // vetor ac
    double m1 = modulo(ab);
    double m2 = modulo(ac);
    double m3 = m1 * m2;
    return (dot(ab, ac) / m3); // retorna o cos do angulo em graus
  }
  pt rotate(pt p, double a) // rotacionar o ponto p em relação a origem, em a graus, no sentido anti-horario
  {
    a = (a * PI) / 180;
    double xx = (cos(a) * p.x) + ((sin(a) * -1) * p.y);
    double yy = (sin(a) * p.x) + (cos(a) * p.y);
    pt ans = {xx, yy};
    return ans;
  }
  double polar(pt p) // polar angle
  {
    return atan2l(p.y, p.x);
  }
  bool cmp(pt a, pt b) // ordenar pontos pelo polar angle
  {
    return polar(a) < polar(b);
  }
  bool cmp_x(pt a, pt b) // ordenar os pontos pela coordenada x
  {
    if (a.x != b.x)
      return a.x < b.x;
    return a.y < b.y;
  }
  vector<pt> convex_hull(vector<pt> v)
  {
    sort(v.begin(), v.end(), cmp_x);
    pt p1 = v[0], p2 = v.back();
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
    int start = 0, limit = 0; // para por em ans no sentido anti-horario e a partir de start
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
    return ans;
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, t = 0;
  while (cin >> n)
  {
    cout << "caso " << t << ":" << endl;
    vector<p::pt> v(n);
    for (int i = 0; i < n; i++)
      cin >> v[i].x >> v[i].y;
    vector<p::pt> ans = p::convex_hull(v);
    for (auto const &i : ans)
      cout << i.x << " " << i.y << endl;
    cout << endl;
    t++;
  }
  return 0;
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