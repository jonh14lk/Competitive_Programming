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

vector<int> f;
bitset<MAXN> prime;
int nxt[MAXN];

void crivo()
{
  prime.set();
  prime[0] = false, prime[1] = false;
  for (int i = 2; i < MAXN; i++)
  {
    if (prime[i])
    {
      nxt[i] = i;
      for (int j = 2; j * i < MAXN; j++)
      {
        prime[j * i] = false;
        nxt[j * i] = i;
      }
    }
  }
}
void fact(int n)
{
  f.clear();
  while (n > 1)
  {
    f.pb(nxt[n]);
    n = n / nxt[n];
  }
}

int mp[MAXN];

void add(int c, int d)
{
  fact(c);
  sort(f.begin(), f.end());
  f.erase(unique(f.begin(), f.end()), f.end());
  int n = f.size();
  for (int i = 1; i < (1 << n); i++)
  {
    int x = 1;
    for (int j = 0; j < n; j++)
    {
      if (i & (1 << j))
        x *= f[j];
    }
    mp[x] += d;
  }
}
int sum(int x)
{
  fact(x);
  sort(f.begin(), f.end());
  f.erase(unique(f.begin(), f.end()), f.end());
  int n = f.size(), ans = 0;
  for (int i = 1; i < (1 << n); i++)
  {
    int xx = 1;
    for (int j = 0; j < n; j++)
    {
      if (i & (1 << j))
        xx *= f[j];
    }
    (__builtin_popcount(i) & 1) ? ans += mp[xx] : ans -= mp[xx];
  }
  return ans;
}
void reset()
{
  for (int i = 0; i < MAXN; i++)
    mp[i] = 0;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  crivo();
  vector<int> v(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> v[i];
  vector<pi> qry(q);
  for (int i = 0; i < q; i++)
  {
    int c, d;
    cin >> c >> d;
    qry[i] = {c, d};
  }
  vector<int> l(n + 1);
  vector<int> r(n + 1);
  vector<vector<int>> on(q);
  for (int i = 1; i <= n; i++)
  {
    l[i] = 0;
    r[i] = q;
  }
  while (1)
  {
    bool ok = 1;
    for (int i = 1; i <= n; i++)
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
      add(qry[mid].fir, qry[mid].sec);
      for (auto const &j : on[mid])
        (sum(j) >= v[j]) ? r[j] = mid : l[j] = mid + 1;
      on[mid].clear();
    }
  }
  for (int i = 1; i <= n; i++)
  {
    if (l[i] >= q)
      cout << "-1\n";
    else
      cout << l[i] + 1 << endl;
  }
  return 0;
}
// inclusao e exclusao com os primos
// + busca binaria paralela