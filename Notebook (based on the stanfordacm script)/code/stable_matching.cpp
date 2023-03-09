#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// #define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define pci pair<char, int>
#define fir first
#define sec second
#define MAXN 100005
#define mod 1000000007

bool in[1005][1005];
int tt[1005][1005];
int b[1005];
int ini[1005];

// a.size() <= b.size()
vector<int> stable_marriage(vector<vector<int>> &a, vector<vector<int>> &b)
{
  int n = a.size(), m = b.size();
  assert(a[0].size() == m and b[0].size() == n and n <= m);
  vector<int> match(m, -1), it(n, 0);
  vector<vector<int>> inv_b(m, vector<int>(n));
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      inv_b[i][b[i][j]] = j;
  queue<int> q;
  for (int i = 0; i < n; i++)
    q.push(i);
  while (q.size())
  {
    int i = q.front();
    q.pop();
    int j = a[i][it[i]];
    if (match[j] == -1)
      match[j] = i;
    else if (inv_b[j][i] < inv_b[j][match[j]])
    {
      q.emplace(match[j]);
      it[match[j]]++;
      match[j] = i;
    }
    else
      q.emplace(i), it[i]++;
  }
  vector<int> ret(n);
  for (int i = 0; i < m; i++)
    if (match[i] != -1)
      ret[match[i]] = i;
  return ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m, d, e;
  cin >> n >> m >> d >> e;
  if (n > m)
  {
    cout << "impossible\n";
    return 0;
  }
  vector<vector<int>> adj(n);
  vector<vector<int>> adj2(m);
  memset(b, -1, sizeof(b));
  memset(ini, -1, sizeof(ini));
  for (int i = 0; i < e; i++)
  {
    int s, k, t;
    cin >> s >> k >> t;
    k--, t--;
    if (t == -1)
    {
      tt[k][b[k]] += (s - ini[k]);
      b[k] = -1;
      ini[k] = -1;
    }
    else
    {
      if (b[k] != -1)
      {
        tt[k][b[k]] += (s - ini[k]);
      }
      if (!in[k][t])
      {
        in[k][t] = 1;
        adj[k].pb(t);
      }
      b[k] = t;
      ini[k] = s;
    }
  }
  for (int k = 0; k < n; k++)
  {
    if (b[k] != -1)
      tt[k][b[k]] += (d - ini[k]);
  }
  for (int k = 0; k < n; k++)
  {
    for (int t = 0; t < m; t++)
    {
      if (!in[k][t])
        adj[k].pb(t);
    }
  }
  for (int t = 0; t < m; t++)
  {
    vector<pi> curr;
    for (int k = 0; k < n; k++)
    {
      curr.pb({tt[k][t], k});
    }
    sort(curr.begin(), curr.end());
    for (auto const &i : curr)
      adj2[t].pb(i.sec);
  }
  vector<int> ans = stable_marriage(adj, adj2);
  for (auto const &i : ans)
    cout << i + 1 << " ";
  cout << endl;
}
// solucao pro: https://open.kattis.com/problems/jealousyoungsters

// stable marriage
// voce quer achar um matching em um grafo bipartido
// que todos os caras de um lado dao matching com algum do outro lado

// cada vertice tem um vector
// que diz qual a ordem de preferencia dele
// o que ele mais quer dar matching eh com v[0]
// o segundo com que ele mais quer dar matching eh com v[1]
// e assim vai

// quando a.size() <= b.size(), entao sempre existe um stable matching
