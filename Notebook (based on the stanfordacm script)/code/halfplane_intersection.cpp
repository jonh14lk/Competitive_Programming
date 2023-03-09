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
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 1000000007

const long double eps = 1e-9;
const long double inf = 1e9;

struct pt
{
  long double x, y;
  pt(long double x = 0, long double y = 0) : x(x), y(y) {}
  friend pt operator+(pt p, pt q)
  {
    return pt(p.x + q.x, p.y + q.y);
  }
  friend pt operator-(pt p, pt q)
  {
    return pt(p.x - q.x, p.y - q.y);
  }
  friend pt operator*(pt p, long double k)
  {
    return pt(p.x * k, p.y * k);
  }
  friend long double dot(pt p, pt q)
  {
    return p.x * q.x + p.y * q.y;
  }
  friend long double cross(pt p, pt q)
  {
    return p.x * q.y - p.y * q.x;
  }
};
struct halfplane
{
  pt p, pq;
  long double angle;
  halfplane() {}
  halfplane(pt a, pt b) : p(a), pq(b - a)
  {
    angle = atan2l(pq.y, pq.x);
  }
  bool out(const pt &r)
  {
    return cross(pq, r - p) < -eps;
  }
  bool operator<(halfplane e) const
  {
    return angle < e.angle;
  }
  friend pt inter(halfplane s, halfplane t)
  {
    long double alpha = cross((t.p - s.p), t.pq) / cross(s.pq, t.pq);
    return s.p + (s.pq * alpha);
  }
};
vector<pt> hp_intersect(vector<halfplane> &h)
{
  pt box[4] = {pt(inf, inf), pt(-inf, inf), pt(-inf, -inf), pt(inf, -inf)}; // Bounding box in CCW order
  for (int i = 0; i < 4; i++)
  {
    halfplane aux(box[i], box[(i + 1) % 4]);
    h.pb(aux);
  }
  sort(h.begin(), h.end());
  deque<halfplane> dq;
  int len = 0;
  for (int i = 0; i < h.size(); i++)
  {
    while (len > 1 && h[i].out(inter(dq[len - 1], dq[len - 2])))
    {
      dq.pop_back();
      --len;
    }
    while (len > 1 && h[i].out(inter(dq[0], dq[1])))
    {
      dq.pop_front();
      --len;
    }
    if (len > 0 && fabsl(cross(h[i].pq, dq[len - 1].pq)) < eps)
    {
      if (dot(h[i].pq, dq[len - 1].pq) < 0.0)
      {
        return vector<pt>();
      }
      if (h[i].out(dq[len - 1].p))
      {
        dq.pop_back();
        --len;
      }
      else
      {
        continue;
      }
    }
    dq.push_back(h[i]);
    ++len;
  }
  while (len > 2 && dq[0].out(inter(dq[len - 1], dq[len - 2])))
  {
    dq.pop_back();
    --len;
  }
  while (len > 2 && dq[len - 1].out(inter(dq[0], dq[1])))
  {
    dq.pop_front();
    --len;
  }
  if (len < 3)
  {
    return vector<pt>();
  }
  vector<pt> ret(len);
  for (int i = 0; i + 1 < len; i++)
  {
    ret[i] = inter(dq[i], dq[i + 1]);
  }
  ret.back() = inter(dq[len - 1], dq[0]);
  return ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q; // quantidade de poligonos
  vector<halfplane> h;
  while (q--)
  {
    int n;
    cin >> n;
    vector<pt> v(n);
    for (int i = 0; i < n; i++)
    {
      cin >> v[i].x >> v[i].y;
    }
    for (int i = 0; i < n; i++)
    {
      int j = (i + 1) % n;
      h.pb(halfplane(v[i], v[j]));
    }
  }
  vector<pt> ans = hp_intersect(h);
  if (ans.size() == 0)
  {
    cout << "0.0\n";
    return 0;
  }
  long double res = 0;
  for (int i = 0; i < ans.size(); i++) // area da interseccao
  {
    pt p = (i) ? ans[i - 1] : ans.back();
    pt q = ans[i];
    res += (p.x - q.x) * (p.y + q.y);
  }
  double resp = abs(res) / 2;
  cout << fixed << setprecision(15) << resp << endl;
  return 0;
}
// half-plane intersection

// definicoes:
// half-plane - regiao planar que consiste de todos os pontos que estao de um lado de uma reta
// geralmente podem ser descritos da seguninte forma
// conjuntos dos pontos (x, y) que satisfazem algo do tipo:
// ax + by + c <= 0 ou ax + by + c >= 0
// da pra representar as retas e os half-planes atraves de um ponto (que ta na reta) e o vetor de direcao
// e dai pros half-planes, considerando que e a regiao da esquerda em relacao ao vetor de direcao

// alem disso, considerar uma bounding box sendo um retangulo, pra caso a inserseccao dos halfplanes nao seja "fechada"

// https://open.kattis.com/problems/bigbrother
// qual a area que voce pode botar uma camera dentro do poligono
// tal que de um ponto escolhido, e possivel ver todos o poligono
// dai considerar todos os halfplanes de arestas do poligono
// e achar a interseccao de todos esses halfplanes

// https://www.codechef.com/problems/CHN02
// achar a area da interseccao de varios poligonos convexos
// considerar todos os halfplanes de arestas do poligono
// e achar a interseccao de todos esses halfplanes