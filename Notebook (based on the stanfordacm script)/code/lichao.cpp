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
#define pii pair<pi, int>
#define pci pair<char, int>
#define fir first
#define sec second
#define MAXN 100005
#define mod 1000000007

const int inf = 1e18;

struct line
{
  int a, b, id;
  int ch[2];
  line()
  {
    a = 0, b = inf, id = -1;
    ch[0] = -1, ch[1] = -1;
  }
  line(int aa, int bb, int i)
  {
    a = aa, b = bb, id = i;
    ch[0] = -1, ch[1] = -1;
  }
  int f(int x) { return a * x + b; }
};
struct save
{
  int a, b, id, new_id, p;
};
struct lichao
{
  int lo, hi, curr;
  vector<line> t;
  stack<save> st; // se nao precisar de rollback, pode tirar a stack (pra nao usar tanta memoria)

  lichao(int ll, int rr)
  {
    lo = ll, hi = rr;
    t.emplace_back();
  }
  int child(int p, int d)
  {
    if (t[p].ch[d] == -1)
    {
      t[p].ch[d] = t.size();
      t.emplace_back();
    }
    return t[p].ch[d];
  }
  bool cmp(line a, line b, int x)
  {
    if (a.f(x) != b.f(x)) // menor valor em x
      return a.f(x) < b.f(x);
    return a.id > b.id; // desempata pelo maior id
  }
  void add(int l, int r, line s, int p)
  {
    int mid = (l + r) >> 1;
    bool fl = cmp(s, t[p], l);
    bool fm = cmp(s, t[p], mid);
    bool fr = cmp(s, t[p], r);
    if (fm)
    {
      st.push({t[p].a, t[p].b, t[p].id, curr, p});
      swap(t[p], s);
      swap(t[p].ch, s.ch);
    }
    if (s.b == inf)
      return;
    if (fl != fm)
      add(l, mid - 1, s, child(p, 0));
    else if (fr != fm)
      add(mid + 1, r, s, child(p, 1));
  }
  pi query(int l, int r, int x, int p)
  {
    int mid = (l + r) >> 1;
    pi ans = {t[p].f(x), -t[p].id}; // como eu quero o maior id, basta negar e pegar o menor
    if (ans.fir == inf)
      return ans;
    if (x < mid)
      return min(ans, query(l, mid - 1, x, child(p, 0)));
    return min(ans, query(mid + 1, r, x, child(p, 1)));
  }
  void add(line s)
  {
    curr = s.id;
    add(lo, hi, s, 0);
  }
  pi qry(int x)
  {
    return query(lo, hi, x, 0);
  }
  void rollback(int id)
  {
    while (!st.empty() && st.top().new_id == id)
    {
      int p = st.top().p;
      t[p].a = st.top().a;
      t[p].b = st.top().b;
      t[p].id = st.top().id;
      st.pop();
    }
  }
};
signed main()
{
  lichao lt(0, 1e9 + 2);
  lt.add(line(3, 2, 0));
  lt.add(line(5, -6, 1));
  cout << lt.qry(10).fir << " " << -lt.qry(10).sec << endl;
}
// li-chao tree
// dado uma coordenada x
// e um conjunto com varias equacoes lineares da forma: y = ax + b
// retorna o menor valor de y entre as equacoes do conjunto
// O(log(hi - lo))
// no qual:
// lo -> menor valor possivel de um x que vai ser passado pra uma query
// hi -> maior valor possivel de um x que vai ser passado pra uma query