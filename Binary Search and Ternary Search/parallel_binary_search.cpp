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
#define MAXN 300006
#define mod 1000000007

int n;
int b[MAXN];

void reset()
{
  for (int i = 0; i < MAXN; i++)
    b[i] = 0;
}
int sum(int r)
{
  int ret = 0;
  for (; r >= 0; r = (r & (r + 1)) - 1)
    ret += b[r];
  return ret;
}
void add(int idx, int delta)
{
  for (; idx < MAXN; idx = idx | (idx + 1))
    b[idx] += delta;
}
void update(int l, int r, int x)
{
  add(l, x);
  add(r + 1, -x);
}
void upd(int l, int r, int x)
{
  if (l <= r)
  {
    update(l, r, x);
    return;
  }
  update(l, MAXN - 2, x);
  update(0, r, x);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; i++)
  {
    int x;
    cin >> x;
    x--;
    adj[x].pb(i);
  }
  vector<int> need(n);
  for (int i = 0; i < n; i++)
  {
    cin >> need[i];
  }
  int q;
  cin >> q;
  vector<pii> qry(q);
  for (int i = 0; i < q; i++)
  {
    cin >> qry[i].sec.fir >> qry[i].sec.sec >> qry[i].fir;
    qry[i].sec.fir--, qry[i].sec.sec--;
  }
  vector<int> l(n);
  vector<int> r(n);
  vector<vector<int>> on(q);
  for (int i = 0; i < n; i++)
  {
    l[i] = 0;
    r[i] = q;
  }
  while (1)
  {
    bool ok = 1;
    for (int i = 0; i < n; i++)
    {
      if (l[i] < r[i])
      {
        ok = 0;
        int mid = (l[i] + r[i]) >> 1;
        on[mid].pb(i);
      }
    }
    if (ok)
      break;
    reset();
    for (int mid = 0; mid < q; mid++)
    {
      upd(qry[mid].sec.fir, qry[mid].sec.sec, qry[mid].fir);
      for (auto const &j : on[mid])
      {
        int val = 0;
        for (auto const &k : adj[j])
        {
          val += sum(k);
          if (val >= need[j])
            break;
        }
        (val >= need[j]) ? r[j] = mid : l[j] = mid + 1;
      }
      on[mid].clear();
    }
  }
  for (int i = 0; i < n; i++)
  {
    if (l[i] >= q)
      cout << "NIE\n";
    else
      cout << l[i] + 1 << endl;
  }
  return 0;
}
// busca binaria paralela
// https://www.spoj.com/problems/METEORS/

// tem n member states e m sectors
// cada sector ta associado a uma member state
// cada query incrementa o range [l[i], r[i]] de sectors por a[i]
// seja q[i] a soma de todos os v[j], sendo j um sector associado ao member state i
// qual o primeiro momento no qual q[i] >= min_qt[i]
// para todos os i

// a sagacidade vai ser fzr uma busca binaria pra cada resposta
// primeiro vc faz todas a primeira iteracao de cada busca binaria
// depois cada segunda iteracao de cada bb
// e assim vai

// ai a bb eh so tipo
// a soma apos a query mid ja deu bom pra aquele member state?
