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
#define mod 1000000007

struct modint
{
  int val;
  modint(int v = 0) { val = ((v % mod) + mod) % mod; }
  int pow(int y)
  {
    modint x = val;
    modint z = 1;
    while (y)
    {
      if (y & 1)
        z *= x;
      x *= x;
      y >>= 1;
    }
    return z.val;
  }
  int inv() { return pow(mod - 2); }
  void operator=(int o) { val = o % mod; }
  void operator=(modint o) { val = o.val % mod; }
  void operator+=(modint o) { *this = *this + o; }
  void operator-=(modint o) { *this = *this - o; }
  void operator*=(modint o) { *this = *this * o; }
  void operator/=(modint o) { *this = *this / o; }
  bool operator==(modint o) { return val == o.val; }
  bool operator!=(modint o) { return val != o.val; }
  int operator*(modint o) { return ((val * o.val) % mod); }
  int operator/(modint o) { return (val * o.inv()) % mod; }
  int operator+(modint o) { return (val + o.val) % mod; }
  int operator-(modint o) { return (val - o.val + mod) % mod; }
};

vector<modint> ans;

int gauss(vector<vector<modint>> a)
{
  int n = a.size(), m = a[0].size() - 1, ret = 1;
  ans.assign(m, 0);
  vector<int> where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; col++, row++)
  {
    int sel = row;
    for (int i = row; i < n; i++)
    {
      if (a[i][col].val > a[sel][col].val)
        sel = i;
    }
    if (!a[sel][col].val)
    {
      continue;
    }
    for (int i = col; i <= m; i++)
    {
      swap(a[sel][i], a[row][i]);
    }
    where[col] = row;
    for (int i = 0; i < n; i++)
    {
      if (i != row)
      {
        modint c = a[i][col] / a[row][col];
        for (int j = col; j <= m; j++)
          a[i][j] -= modint(a[row][j] * c);
      }
    }
  }
  for (int i = 0; i < m; i++)
  {
    if (where[i] != -1)
      ans[i] = (a[where[i]][m] / a[where[i]][i]);
    else
      ret = 2;
  }
  for (int i = 0; i < n; i++)
  {
    modint sum = 0;
    for (int j = 0; j < m; j++)
      sum += (ans[j] * a[i][j]);
    if ((sum - a[i][m]) > 0)
      ret = 0;
  }
  assert(ret == 1); // so uma solucao existe
  return ret;
}

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};
modint a[4];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int r;
  cin >> r;
  modint sum = 0;
  for (int i = 0; i < 4; i++)
  {
    cin >> a[i].val;
    sum += a[i];
  }
  for (int i = 0; i < 4; i++)
  {
    a[i] /= sum;
  }
  vector<pi> in;
  queue<pi> q;
  set<pi> vis;
  q.push({0, 0});
  vis.insert({0, 0});
  // quais posicoes tao a distancia <= R da origem
  while (!q.empty())
  {
    auto [x, y] = q.front();
    q.pop();
    if ((x * x) + (y * y) > (r * r))
      continue;
    in.pb({x, y});
    for (int dir = 0; dir < 4; dir++)
    {
      int i = x + dx[dir];
      int j = y + dy[dir];
      if (vis.find({i, j}) == vis.end())
      {
        q.push({i, j});
        vis.insert({i, j});
      }
    }
  }
  sort(in.begin(), in.end());
  int sz = in.size() + 1;
  auto get_id = [&](int x, int y)
  {
    if ((x * x) + (y * y) > (r * r))
      return sz - 1;
    return (int)(lower_bound(in.begin(), in.end(), pi(x, y)) - in.begin());
  };
  vector<vector<modint>> prob(sz, vector<modint>(sz, 0));
  // primeiro passo:
  // para cada nao terminal ii computamos prob[ii][j], probabilidade de ir de ii pra j em um move
  // todas as celulas com distancia > r, eu considero por um unico indice nessa representacao
  for (int ii = 0; ii < (sz - 1); ii++)
  {
    auto [x, y] = in[ii];
    for (int dir = 0; dir < 4; dir++)
    {
      int i = x + dx[dir];
      int j = y + dy[dir];
      int id = get_id(i, j);
      prob[ii][id] += a[dir];
    }
  }
  // agr quero calcular EV(i) para todo i
  // valor esperado de moves saindo da posicao i
  // monta o sisteminha de equacoes e dale
  vector<vector<modint>> eqs;
  for (int i = 0; i < sz; i++)
  {
    vector<modint> curr(sz + 1, 0);
    if (i == sz - 1) // estado terminal, EV(i) = 0
    {
      curr[sz - 1] = 1;
      eqs.pb(curr);
    }
    else // nao terminal, EV(i) = 1 + soma dos (prob[i][j] * EV(j))
    {
      for (int j = 0; j < sz; j++)
      {
        if (i == j)
          curr[j] = modint(1) - prob[i][j];
        else
          curr[j] = prob[i][j] * -1;
      }
      curr[sz] = 1;
      eqs.pb(curr);
    }
  }
  gauss(eqs);
  for (int i = 0; i < in.size(); i++)
  {
    if (in[i].fir == 0 && in[i].sec == 0) // ja que eu quero o valor esperado saindo da posicao (0,0)
      cout << ans[i].val << endl;
  }
  return 0;
}
// solucao tle (porem correta) de um problema legal
// https://codeforces.com/contest/963/problem/E

// tem um chip inicialmente na posicao (0, 0)
// e ele vai comecar a se mover aleatoriamente
// tem a[i] / (a[1] + a[2] + a[3] + a[4]) para se mover para a direcao i
// ele pode ir pra (x + 1, y) (x, y + 1), (x - 1, y), (x, y - 1)

// quero saber o valor esperado ate ele checar em uma celula
// com distancia maior do que R do (0, 0)