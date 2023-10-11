#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500005
#define mod 998244353

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct query
{
  char c;
  int id, u, d;
};
struct bit
{
  vector<ordered_set<pi>> bb;
  vector<map<int, int>> cnt;

  bit(int n)
  {
    bb.resize(n + 2);
    cnt.resize(n + 2);
  }
  int qry(int r, int a, int b)
  {
    int ret = 0, curr = r;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      ret += (bb[r].order_of_key({b + 1, -1}) - bb[r].order_of_key({a, -1}));
    return ret;
  }
  void add(int idx, int delta)
  {
    for (; idx < MAXN; idx = idx | (idx + 1))
    {
      cnt[idx][delta]++;
      bb[idx].insert({delta, cnt[idx][delta]});
    }
  }
  void rem(int idx, int delta)
  {
    for (; idx < MAXN; idx = idx | (idx + 1))
    {
      bb[idx].erase({delta, cnt[idx][delta]});
      cnt[idx][delta]--;
    }
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q, h1, h2, w;
  cin >> n >> q >> h1 >> h2 >> w;
  vector<int> val;
  vector<pi> v(n);
  for (int i = 0; i < n; i++)
  {
    int u, d, l, r;
    cin >> u >> d >> l >> r;
    v[i] = {u, d};
    val.pb(u);
    val.pb(d);
  }
  vector<query> qry(q);
  for (int i = 0; i < q; i++)
  {
    char c;
    cin >> c;
    int l, r;
    qry[i].c = c;
    if (c == 'A')
    {
      cin >> qry[i].id >> qry[i].u >> qry[i].d >> l >> r;
      val.pb(qry[i].u);
      val.pb(qry[i].d);
    }
    else
    {
      cin >> qry[i].id;
      val.pb(qry[i].id);
    }
  }
  val.pb(h1);
  val.pb(h2);
  sort(val.begin(), val.end());
  val.erase(unique(val.begin(), val.end()), val.end());
  vector<int> lim(val.size());
  int j = 0;
  for (int i = 0; i < val.size(); i++)
  {
    j = max(j, i);
    while (j + 1 < val.size() && val[j + 1] - val[i] < h1)
      j++;
    lim[i] = j + 1;
  }
  map<int, pi> mp;
  bit b(MAXN);
  bit b2(MAXN);
  for (int i = 0; i < n; i++)
  {
    v[i].fir = lower_bound(val.begin(), val.end(), v[i].fir) - val.begin();
    v[i].sec = lower_bound(val.begin(), val.end(), v[i].sec) - val.begin();
    b.add(v[i].fir, v[i].sec);
    b2.add(MAXN - v[i].sec, MAXN - v[i].fir);
    mp[i + 1] = v[i];
  }
  int wwl = 0, wwr = lim[0];
  auto intersect = [&](pi x, int l, int r)
  {
    return (!(x.sec < l || x.fir > r));
  };
  auto count1 = [&](int l, int r, int xx)
  {
    // contar intervalos [lx, rx]
    // que se intersectam com [l, r]
    // e com rx <= xx
    return b.qry(min(r, xx), l, xx);
  };
  auto count2 = [&](int l, int r, int xx)
  {
    l = MAXN - l;
    r = MAXN - r;
    xx = MAXN - xx;
    // contar intervalos [lx, rx]
    // que se intersectam com [l, r]
    // e com coordenada lx >= xx
    return b2.qry(min(l, xx), r, xx);
  };
  for (int ii = 0; ii < q; ii++)
  {
    char c = qry[ii].c;
    int id = qry[ii].id;
    int u = qry[ii].u;
    int d = qry[ii].d;
    if (c == 'A')
    {
      u = lower_bound(val.begin(), val.end(), u) - val.begin();
      d = lower_bound(val.begin(), val.end(), d) - val.begin();
      b.add(u, d);
      b2.add(MAXN - d, MAXN - u);
      mp[id] = {u, d};
      cout << intersect(mp[id], wwl + 1, wwr - 1) << " " << 0 << endl;
    }
    else if (c == 'M')
    {
      id = lower_bound(val.begin(), val.end(), id) - val.begin();
      int ans1 = 0, ans2 = 0;
      int l1 = id + 1, r1 = lim[id] - 1;
      int l2 = wwl + 1, r2 = wwr - 1;
      if (l1 == l2)
      {
        cout << "0 0\n";
        continue;
      }
      if (l1 < l2)
      {
        ans1 = count1(l1, r1, l2 - 1);
        ans2 = count2(l2, r2, r1 + 1);
      }
      else
      {
        ans1 = count2(l1, r1, r2 + 1);
        ans2 = count1(l2, r2, l1 - 1);
      }
      cout << ans1 << " " << ans2 << endl;
      wwl = id;
      wwr = lim[id];
    }
    else
    {
      cout << 0 << " " << intersect(mp[id], wwl + 1, wwr - 1) << endl;
      b.rem(mp[id].fir, mp[id].sec);
      b2.rem(MAXN - mp[id].sec, MAXN - mp[id].fir);
    }
  }
  return 0;
}
// um site com h2 por w
// a tela pega uma regiao h1 por w
// as pictures nao se intersectam
// adicionar uma picture
// remover uma picture
// mudar a posição do scroll

// pela tela ter sempre a largura maxima
// entao da pra pensar no problema 1d
// fzr compressão de coordenadas
// e reduzir pra um problema de data structures