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
#define MAXN 600005
#define mod 1000000007
#define PI acos(-1)

vector<int> adj[MAXN];
int parent[MAXN];
int dist[MAXN];
int diameter, best;
int root = 600002;

void dfs(int s, int c, int f)
{
  if (c > diameter)
  {
    diameter = c;
    best = s;
  }
  for (auto const &i : adj[s])
  {
    if (i != f)
      dfs(i, c + 1, s);
  }
}
void bfs(int s)
{
  for (int i = 0; i < MAXN; i++)
  {
    dist[i] = 1e9;
  }
  queue<int> q;
  dist[s] = 0;
  q.push(s);
  while (!q.empty())
  {
    int v = q.front();
    q.pop();
    for (auto const &i : adj[v])
    {
      if (dist[i] > dist[v] + 1)
      {
        dist[i] = dist[v] + 1;
        q.push(i);
      }
    }
  }
}
int solve()
{
  // agora virou um problema de arvore
  // escolher dois nós tal que:
  // d = dist(m, l) + dist(l, root)
  // eh maximizada
  // se pa:
  // acha o diametro da arvore
  // os dois vértices do diametro são otimos
  diameter = 0, best = 0;
  dfs(root, 0, -1);
  int start = best;
  dfs(start, 0, -1);
  int ans = diameter;
  bfs(root);
  ans += max(dist[best], dist[start]);
  return ans;
}

struct pt
{
  int x, y;
};
struct seg
{
  pt p, q;
  int id;
  bool is_upper;
  seg() {}
  seg(pt p, pt q, int id) : p(p), q(q), id(id)
  {
    is_upper = false;
    if (p.x > q.x)
      is_upper = true;
  }
  double get_y(int x) const
  {
    if (p.x == q.x)
      return p.y;
    return p.y + (q.y - p.y) * 1.0 * (x - p.x) / (q.x - p.x);
  }
};
int current_x;
bool operator<(const seg &a, const seg &b)
{
  if (a.get_y(current_x) == b.get_y(current_x))
  {
    if (a.is_upper == b.is_upper)
      return a.q.x < b.q.x;
    return a.is_upper < b.is_upper;
  }
  return a.get_y(current_x) < b.get_y(current_x);
}
struct event
{
  int x;
  int tp;
  seg l;
  event() {}
  event(int x, int tp, seg l) : x(x), tp(tp), l(l) {}
  bool operator<(const event &e) const
  {
    if (x == e.x)
    {
      if (tp == e.tp)
        return l.p.y > e.l.p.y;
      return tp > e.tp;
    }
    return x < e.x;
  }
};

set<seg> s;

void line_sweep(vector<seg> &v)
{
  vector<event> e;
  for (int i = 0; i < v.size(); i++)
  {
    if (v[i].p.x == v[i].q.x)
      continue;
    if (v[i].p.x > v[i].q.x)
      swap(v[i].p, v[i].q);
    e.pb({v[i].p.x, 1, v[i]});
    e.pb({v[i].q.x, 0, v[i]});
  }
  sort(e.begin(), e.end());
  for (int i = 0; i < e.size(); i++)
  {
    current_x = e[i].x;
    int id = e[i].l.id;
    if (e[i].l.is_upper && parent[id] == -1)
    {
      auto it = s.upper_bound(e[i].l);
      if (it != s.end())
      {
        seg par = (*it);
        if (par.is_upper)
          parent[id] = par.id;
        else
          parent[id] = parent[par.id];
      }
      else
      {
        parent[id] = root;
      }
    }
    if (e[i].tp == 1)
    {
      s.insert(e[i].l);
    }
    else
    {
      s.erase(e[i].l);
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<seg> vv;
  for (int i = 0; i < n; i++)
  {
    int m;
    cin >> m;
    vector<pt> v(m);
    for (int j = 0; j < m; j++)
      cin >> v[j].x >> v[j].y;
    for (int j = 0; j < m; j++)
    {
      int k = (j + 1) % m;
      if (v[j].x == v[k].x)
        continue;
      vv.pb({v[j], v[k], i});
    }
  }
  memset(parent, -1, sizeof(parent));
  line_sweep(vv);
  for (int i = 0; i < n; i++)
  {
    adj[i].pb(parent[i]);
    adj[parent[i]].pb(i);
  }
  cout << solve() << endl;
  return 0;
}