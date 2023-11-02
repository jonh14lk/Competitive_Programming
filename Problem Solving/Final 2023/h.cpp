#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAX 205
#define mod 998244353

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
  pt box[4] = {pt(inf, inf), pt(-inf, inf), pt(-inf, -inf), pt(inf, -inf)};
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
  int n;
  double d;
  cin >> n >> d;
  vector<pair<pt, pt>> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].fir.x >> v[i].fir.y >> v[i].sec.x >> v[i].sec.y;
  }
  auto can = [&](int qt)
  {
    vector<halfplane> h;
    for (int i = 0; i < qt; i++)
    {
      halfplane ha = halfplane(v[i].fir, v[i].sec);
      halfplane hb = halfplane(v[i].sec, v[i].fir);
      if (!ha.out({0, 0}))
        h.pb(ha);
      else
        h.pb(hb);
    }
    vector<pt> ans = hp_intersect(h);
    for (auto const &i : ans)
    {
      double dist = abs(i.x * i.x);
      dist += abs(i.y * i.y);
      if (sqrtl(dist) >= d)
        return 0;
    }
    return 1;
  };
  if (!can(n))
  {
    cout << "*\n";
    return 0;
  }
  int l = 1, r = n;
  while (l < r)
  {
    int mid = (l + r) >> 1;
    (can(mid)) ? r = mid : l = mid + 1;
  }
  cout << l << endl;
}
// pegar a halfplane intersection
// que vai ser um poligono
// dai dado esse poligono, eu quero saber se do ponto 0,0
// eh impossivel chegar em algum ponto da borda da circunferencia
// ou resumindo
// a maior distancia de 0,0 ate um ponto da borda do poligono
// precisa ser < d