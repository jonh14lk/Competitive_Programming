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
#define MAXN 1005
#define mod 998244353
#define INF 1e18

struct item
{
  int t, d, id;
  bool operator<(item ot)
  {
    if (d != ot.d)
      return d < ot.d;
    return id < ot.id;
  }
};

int n, curr_i;
vector<item> v;
vector<int> c, pref, sum, ord;

bool cmp(int a, int b)
{
  return v[a] < v[b];
}
bool naive()
{
  int t = 0, s = 0;
  c.clear(), sum.clear();
  for (int j = 0; j < n; j++)
  {
    int i = ord[j];
    t += v[i].t;
    (j > curr_i) ? c.pb(v[i].d - t) : c.pb(1e18);
    sum.pb(t);
    if (t > v[i].d)
      return 0;
  }
  pref.resize(n);
  pref[0] = c[0];
  for (int i = 1; i < n; i++)
    pref[i] = min(pref[i - 1], c[i]);
  return 1;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  v.resize(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].t >> v[i].d;
    v[i].id = i;
    ord.pb(i);
  }
  curr_i = -1;
  sort(ord.begin(), ord.end(), cmp);
  if (!naive())
  {
    cout << "*\n";
    return 0;
  }
  int lim = 0;
  for (int i = 0; i < n; i++)
  {
    vector<int> pos(n);
    for (int j = 0; j < n; j++)
      pos[ord[j]] = j;
    int best = 1e18;
    for (int j = 0; j < n; j++) // por j na posicao i
    {
      if (pos[j] < i)
        continue;
      if (pos[j] == i)
      {
        best = j;
        break;
      }
      if (pref[pos[j] - 1] >= v[j].t)
      {
        best = j;
        break;
      }
    }
    curr_i++;
    for (int j = pos[best] - 1; j >= i; j--)
      ord[j + 1] = ord[j];
    ord[i] = best;
    naive();
  }
  for (auto const &i : ord)
    cout << i + 1 << " ";
  cout << endl;
  return 0;
}