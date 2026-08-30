#include <bits/stdc++.h>
using namespace std;

// #define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500005
#define mod 1000000007
#define inf 1e9

struct segtree
{
  int n;
  vector<int> seg;

  int neutral()
  {
    return inf;
  }
  int merge(int a, int b)
  {
    return min(a, b);
  }
  segtree(int sz)
  {
    n = 1;
    while (n < sz)
      n <<= 1;
    seg.assign(n << 1, neutral());
  }
  void upd(int i, int value)
  {
    i += n;
    if (value > seg[i])
      return;
    seg[i] = value;
    for (i >>= 1; i; i >>= 1)
      seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
  }
  int qry(int l, int r)
  {
    int ansl = neutral(), ansr = neutral();
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
    {
      if (l & 1)
        ansl = merge(ansl, seg[l++]);
      if (r & 1)
        ansr = merge(seg[--r], ansr);
    }
    return merge(ansl, ansr);
  }
};

vector<int> ending_here[MAXN];

namespace aho
{
  int go(int v, char ch);
  const int K = 4;
  struct trie
  {
    char me;
    int go[K];
    int down[K];
    vector<int> ends;
    int parent = -1;
    int link = -1;
    int exit_link = -1;
    trie(int p = -1, char ch = '$') : parent(p), me(ch)
    {
      fill(begin(go), end(go), -1);
      fill(begin(down), end(down), -1);
    }
  };
  vector<trie> ac;
  void init()
  {
    ac.resize(1);
  }
  void add_string(string &s, int id)
  {
    int v = 0;
    for (auto const &ch : s)
    {
      int c = ch - '0';
      if (ac[v].down[c] == -1)
      {
        ac[v].down[c] = ac.size();
        ac.emplace_back(v, ch);
      }
      v = ac[v].down[c];
    }
    ac[v].ends.pb(id);
  }
  int get_link(int v)
  {
    if (ac[v].link == -1)
      ac[v].link = (!v || !ac[v].parent) ? 0 : go(get_link(ac[v].parent), ac[v].me);
    return ac[v].link;
  }
  int go(int v, char ch)
  {
    int c = ch - '0';
    if (ac[v].go[c] == -1)
    {
      if (ac[v].down[c] != -1)
        ac[v].go[c] = ac[v].down[c];
      else
        ac[v].go[c] = (!v) ? 0 : go(get_link(v), ch);
    }
    return ac[v].go[c];
  }
  int get_exit_link(int v)
  {
    if (ac[v].exit_link == -1)
    {
      int curr = get_link(v);
      if (!v || !curr)
        ac[v].exit_link = 0;
      else if (ac[curr].ends.size() > 0)
        ac[v].exit_link = curr;
      else
        ac[v].exit_link = get_exit_link(curr);
    }
    return ac[v].exit_link;
  }
  void query(string &s)
  {
    int curr = 0, at;
    for (int i = 0; i < s.size(); i++)
    {
      curr = go(curr, s[i]);
      for (auto const &str_id : ac[curr].ends)
        ending_here[i].pb(str_id);
      at = get_exit_link(curr);
      while (at)
      {
        for (auto const &str_id : ac[at].ends)
          ending_here[i].pb(str_id);
        at = get_exit_link(at);
      }
    }
  }
}
string transform(string &s)
{
  string t;
  for (auto const &i : s)
  {
    if (i == 'A')
      t.pb('0');
    if (i == 'T')
      t.pb('1');
    if (i == 'C')
      t.pb('2');
    if (i == 'G')
      t.pb('3');
  }
  return t;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string t;
  cin >> t;
  int n;
  cin >> n;
  t = transform(t);
  vector<string> strs(n);
  aho::init();
  for (int i = 0; i < n; i++)
  {
    cin >> strs[i];
    strs[i] = transform(strs[i]);
    aho::add_string(strs[i], i);
  }
  aho::query(t);
  int q;
  cin >> q;
  vector<pii> qry(q);
  for (int i = 0; i < q; i++)
  {
    int l, r;
    cin >> l >> r;
    l--, r--;
    qry[i] = {l, {r, i}};
  }
  auto cmp = [&](pii a, pii b)
  {
    return a.sec.fir < b.sec.fir;
  };
  sort(qry.begin(), qry.end(), cmp); // ordena do menor r pro maior r
  vector<int> ans(q);
  segtree st(t.size());
  int ptr = 0;
  for (auto [l, x] : qry)
  {
    auto [r, id] = x;
    while (ptr <= r)
    {
      for (auto const &i : ending_here[ptr])
        st.upd(ptr - strs[i].size() + 1, i);
      ptr++;
    }
    ans[id] = st.qry(l, r);
    if (ans[id] == inf)
      ans[id] = -1;
    else
      ans[id]++;
  }
  for (auto const &i : ans)
  {
    cout << i << endl;
  }
  return 0;
}