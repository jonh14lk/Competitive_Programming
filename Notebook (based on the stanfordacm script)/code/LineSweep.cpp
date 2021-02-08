#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 200001
#define mod 1000000007

const double EPS = 1E-9; // para tratar a precisao do double e divisao por 0

struct pt
{
  double x, y;
};
struct seg
{
  pt p, q;
};
struct event
{
  double x;
  int type, id;
};

set<seg> s;                       // set de segmentos que começaram mas nao acabaram ainda
vector<set<seg>::iterator> where; // guarda os iterators de cada evento no set para que a gente consiga acessa-los

set<seg>::iterator prev(set<seg>::iterator it) // achar o iterator do adjacente da esquerda
{
  return it == s.begin() ? s.end() : it--;
}
set<seg>::iterator next(set<seg>::iterator it) // achar o iterator do adjacente da direita
{
  return it++;
}
double get_y(seg a, double x)
{
  if (abs(a.p.x - a.q.x) < EPS)
    return a.p.y;
  return a.p.y + (a.q.y - a.p.y) * (x - a.p.x) / (a.q.x - a.p.x);
}
bool operator<(const seg &a, const seg &b) // operator para o set de segmentos
{
  double x = max(min(a.p.x, a.q.x), min(b.p.x, b.q.x));
  return get_y(a, x) < get_y(b, x) - EPS;
}
bool cmp(event a, event b) // comparador para ordenar os eventos
{
  if (abs(a.x - b.x) > EPS)
    return a.x < b.x;
  a.type > b.type;
}
bool intersect1d(double l1, double r1, double l2, double r2) // verificar intersecção
{
  if (l1 > r1)
    swap(l1, r1);
  if (l2 > r2)
    swap(l2, r2);
  return max(l1, l2) <= min(r1, r2) + EPS;
}
int vec(pt a, pt b, pt c) // verificar intersecção
{
  double s = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
  return abs(s) < EPS ? 0 : s > 0 ? +1 : -1;
}
bool intersect(seg a, seg b) // verificar intersecção
{
  return intersect1d(a.p.x, a.q.x, b.p.x, b.q.x) &&
         intersect1d(a.p.y, a.q.y, b.p.y, b.q.y) &&
         vec(a.p, a.q, b.p) * vec(a.p, a.q, b.q) <= 0 &&
         vec(b.p, b.q, a.p) * vec(b.p, b.q, a.q) <= 0;
}
bool line_sweep(vector<seg> v)
{
  vector<event> e;
  for (int i = 0; i < v.size(); i++) // para cada segmento
  {
    e.push_back({min(v[i].p.x, v[i].q.x), 1, i}); // evento do primeiro tipo: inicio do segmento
    e.push_back({max(v[i].p.x, v[i].q.x), 0, i}); // evento do segundo tipo: fim do segmento
  }
  sort(e.begin(), e.end(), cmp);     // ordenar os nossos eventos
  where.resize(v.size());            // tamanho do where = quantidade de eventos
  for (int i = 0; i < e.size(); i++) // para cada evento
  {
    int id = e[i].id; // id do evento atual
    if (e[i].type)    // primeiro tipo: o segmento com (ID = id) começa
    {
      auto nxt = s.lower_bound(v[id]), prv = prev(nxt); // acho os eventos adjacentes ao novo evento
      if (nxt != s.end() && intersect(*nxt, v[id]))     // um dos adjacentes se intersectam com o segmento atual ?
        return true;
      if (prv != s.end() && intersect(*prv, v[id]))
        return true;
      where[id] = s.insert(nxt, v[id]); // insiro o segmento no set de segmentos que começaram mas nao acabaram
    }
    else // segundo tipo: o segmento com (ID = id) acaba
    {
      auto nxt = next(where[id]), prv = prev(where[id]);             // acho os adjacentes do evento q vou remover
      if (nxt != s.end() && prv != s.end() && intersect(*nxt, *prv)) // esses novos adjacentes entre si se intersectam ?
        return true;
      s.erase(where[id]); // removo o segmento do set pois o segmento acabou
    }
  }
  return false;
}
signed main()
{
  int n;
  cin >> n;
  vector<seg> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i].p.x >> v[i].p.y >> v[i].q.x >> v[i].q.y;
  (line_sweep(v)) ? cout << "YES\n" : cout << "NO\n";
  return 0;
}

// line sweep

// problema: dados n segmentos de reta em um plano, verifique se pelo menos dois desses segmentos se intersectam
// solução mais simples: iterar sobre todos os pares de segmentos existentes e verificar se algum deles se intersectam
// complexidade: O(n^2)
// solução mais eficiente: line sweep, complexidade: O(n * log n)

// algoritimo para o problema:
// 1- imagine uma reta na vertical com x = - INF (x mais a esquerda)
// 2- começar a mover esta reta para a direita, durante o movimento essa reta irá se encontrar com os segmentos.
// 3- estamos interessados na ordem relativa dos segmentos ao longo da vertical, para isso vamos criar um vector que
// guarda a coordenada x do inicio do segmento e a coordenada x do final do segmento
// 4- para encontrar um par de segmentos que se intersectam nesse processo, basta apenas considerar os segmentos
// adjacentes entre si.
// 5- se algum dos adjacentes se intersectam, return true, se eu nao achar nenhum, return false

/* 
2
1 1 2 2 
3 3 -1 1
NO

3
1 1 2 2 
3 3 -1 1
0 0 -2 2
YES

*/
