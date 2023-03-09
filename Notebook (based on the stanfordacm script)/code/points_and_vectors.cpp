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
    pt operator-(pt p) { return {x - p.x, y - p.y}; } // subtracao de pontos
    pt operator*(double d) { return {x * d, y * d}; } // multiplicacao por um double
    pt operator/(double d) { return {x / d, y / d}; } // divisao por um double
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
  bool is_colinear(pt a, pt b, pt c) // retorna se os pontos a, b e c sao colineares
  {
    return cross(b - a, c - a) == 0;
  }
  bool ccw(pt a, pt b, pt c) // retorna se os pontos a,b e c estao no sentido anti horario
  {
    return cross(b - a, c - b) > 0;
  }
  bool cw(pt a, pt b, pt c) // retorna se os pontos a,b e c estao no sentido horario
  {
    return cross(b - a, c - b) < 0;
  }
  double modulo(pt v) // |v| = sqrt(x2 + y2)
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
  pt rotate(pt p, double a) // rotacionar o ponto p em relacao a origem, em a graus, no sentido anti-horario
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
  pt polar_to_cartesian(double r, double theta) // r - distancia do centro, theta - polar angle
  {
    pt ans;
    ans.x = r * cos(double(theta) / 180 * PI); // assumindo que theta ta em graus, transforma pra radiano
    ans.y = r * sin(double(theta) / 180 * PI);
    return ans;
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}