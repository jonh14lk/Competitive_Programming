#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 500001
#define mod 1000000007

void radix(vector<pii> &v)
{
  {
    int n = v.size();
    vector<int> cnt(n);
    for (auto const &i : v)
      cnt[i.fir.sec]++;
    vector<pii> ans(n);
    vector<int> pos(n);
    pos[0] = 0;
    for (int i = 1; i < n; i++)
      pos[i] = pos[i - 1] + cnt[i - 1];
    for (auto const &i : v)
    {
      int k = i.fir.sec;
      ans[pos[k]] = i;
      pos[k]++;
    }
    v = ans;
  }
  {
    int n = v.size();
    vector<int> cnt(n);
    for (auto const &i : v)
      cnt[i.fir.fir]++;
    vector<pii> ans(n);
    vector<int> pos(n);
    pos[0] = 0;
    for (int i = 1; i < n; i++)
      pos[i] = pos[i - 1] + cnt[i - 1];
    for (auto const &i : v)
    {
      int k = i.fir.fir;
      ans[pos[k]] = i;
      pos[k]++;
    }
    v = ans;
  }
}
vector<int> suffix_array(vector<int> &s)
{
  int n = s.size();
  vector<int> p(n), c(n);
  vector<pi> a(n);
  for (int i = 0; i < n; i++)
    a[i] = {s[i], i};
  sort(a.begin(), a.end());
  for (int i = 0; i < n; i++)
    p[i] = a[i].sec;
  c[p[0]] = 0;
  for (int i = 1; i < n; i++)
    (a[i].fir == a[i - 1].fir) ? c[p[i]] = c[p[i - 1]] : c[p[i]] = c[p[i - 1]] + 1;
  int k = 0;
  while ((1 << k) < n)
  {
    vector<pii> v(n);
    for (int i = 0; i < n; i++)
      v[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
    radix(v);
    for (int i = 0; i < n; i++)
      p[i] = v[i].sec;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++)
      (v[i].fir == v[i - 1].fir) ? c[p[i]] = c[p[i - 1]] : c[p[i]] = c[p[i - 1]] + 1;
    k++;
  }
  return p;
}
int eval(vector<int> &ans)
{
  int resp = 0, p = 365;
  for (int i = ans.size() - 1; i >= 0; i--)
  {
    int x = (ans[i] * 1ll * p) % mod;
    resp = (resp + x) % mod;
    p = (p * 1ll * 365) % mod;
  }
  return resp;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<vector<int>> v(n);
  vector<vector<int>> pos(n);
  vector<vector<int>> value(n);
  vector<pi> pos_rev;
  vector<int> all;
  for (int i = 0; i < n; i++)
  {
    int m;
    cin >> m;
    v[i].resize(m);
    pos[i].resize(m);
    value[i].resize(m);
    for (int j = 0; j < m; j++)
    {
      cin >> v[i][j];
      all.pb(v[i][j]);
      pos_rev.pb({i, j});
      pos[i][j] = all.size() - 1;
    }
    all.pb(305);
    pos_rev.pb({-1, -1});
  }
  vector<int> suf = suffix_array(all);
  for (int i = 0; i < suf.size(); i++)
  {
    int x = suf[i];
    if (pos_rev[x].fir == -1)
      continue;
    int a = pos_rev[x].fir, b = pos_rev[x].sec;
    value[a][b] = i;
  }
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 0; i < n; i++)
    pq.push({{value[i][0], i}, 0});
  vector<int> ans;
  while (!pq.empty())
  {
    int i = pq.top().fir.sec;
    int j = pq.top().sec;
    pq.pop();
    ans.pb(v[i][j]);
    if (j + 1 < v[i].size())
      pq.push({{value[i][j + 1], i}, j + 1});
  }
  cout << eval(ans) << endl;
  return 0;
}
// a melhor ordem eh a que eh a menor lexicograficamente
// com isso o problema eh:
// dados n arrays, qual o merge lexicograficamente minimo entre eles?

// uma alternativa eh:
// pega o menor elemento dos que restam, e vai botando ele na resposta
// mas não vai funcionar, por exemplo se eu tenho:
// [3, 2] e [3, 1]
// o merge otimo eh: [3, 1, 3, 2]
// porém se eu tirar o 3 do primeiro array antes do 3 do segundo array
// vou construir a resposta errada

// Quando mais de um cara empata, temos que olhar para a proxima posição
// no final das contas, vamos ter que olhar pro sufixo começando da posição ptr[i]
// em cada array, e tirar do cara com o menor sufixo lexicograficamente

// uma possivel ideia eh:
// junta todas os arrays em um só
// acha o suffix array desse array
// com isso salva a posição de cada sufixo de cada array no suffix array
// e dps conseguimos buildar a respostas
