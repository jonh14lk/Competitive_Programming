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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 300005
#define mod 1000000009

int P;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int uniform(int l, int r)
{
  uniform_int_distribution<int> uid(l, r);
  return uid(rng);
}
int pot[MAXN];

namespace sa
{
  vector<int> dq;  // guarda o hash de sufixo
  vector<char> st; // guarda a string
  int resp;        // guarda a soma de max(0ll, lcp[i] - lcp[i - 1])

  int get_hash(int l, int r)
  {
    int hash = dq[(dq.size() - 1) - l] - ((r + 1 < dq.size()) ? ((dq[(dq.size() - 1) - (r + 1)] * pot[r - l + 1]) % mod) : 0);
    return hash < 0 ? hash + mod : hash;
  }
  int lcp(int a, int b)
  {
    int ida = dq.size() - a;
    int idb = dq.size() - b;
    int l = 0, r = min(dq.size() - ida, dq.size() - idb);
    while (l < r)
    {
      int mid = (l + r + 1) >> 1;
      (get_hash(ida, ida + mid - 1) == get_hash(idb, idb + mid - 1)) ? l = mid : r = mid - 1;
    }
    return l;
  }
  bool cmp(int a, int b)
  {
    int l = lcp(a, b);
    int ida = dq.size() - a;
    int idb = dq.size() - b;
    if (idb + l == dq.size())
      return 0;
    if (ida + l == dq.size())
      return 1;
    return (st[(dq.size() - 1) - (ida + l)] < st[(dq.size() - 1) - (idb + l)]);
  }
  set<int, decltype(cmp) *> sa(cmp);

  void add2(char c)
  {
    if (!dq.size())
      dq.pb(c);
    else
      dq.pb((((dq.back() * P) % mod) + c) % mod);
    st.pb(c);
    sa.insert(dq.size());
  }
  void add(char c)
  {
    add2(c);
    auto it = sa.find(dq.size());
    auto nxt = it;
    nxt++;
    auto nxt2 = nxt;
    nxt2++;
    auto prv = it;
    prv--;
    auto prv2 = prv;
    prv2--;
    {
      int x1 = lcp(*prv, *nxt);
      int x2 = lcp(*prv2, *prv);
      int x3 = lcp(*nxt, *nxt2);
      int x4 = lcp(*prv, *it);
      int x5 = lcp(*it, *nxt);
      resp -= max(0ll, x1 - x2);
      resp -= max(0ll, x3 - x1);
      resp += max(0ll, x4 - x2);
      resp += max(0ll, x5 - x4);
      resp += max(0ll, x3 - x5);
    }
  }
  void pop()
  {
    auto it = sa.find(dq.size());
    auto nxt = it;
    nxt++;
    auto nxt2 = nxt;
    nxt2++;
    auto prv = it;
    prv--;
    auto prv2 = prv;
    prv2--;
    {
      int x1 = lcp(*prv, *nxt);
      int x2 = lcp(*prv2, *prv);
      int x3 = lcp(*nxt, *nxt2);
      int x4 = lcp(*prv, *it);
      int x5 = lcp(*it, *nxt);
      resp -= max(0ll, x4 - x2);
      resp -= max(0ll, x5 - x4);
      resp -= max(0ll, x3 - x5);
      resp += max(0ll, x1 - x2);
      resp += max(0ll, x3 - x1);
    }
    sa.erase(dq.size());
    dq.pop_back();
    st.pop_back();
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  P = uniform(256, mod - 1);
  pot[0] = 1;
  for (int i = 1; i < MAXN; i++)
  {
    pot[i] = (pot[i - 1] * P) % mod;
  }
  string s, t;
  cin >> s >> t;
  sa::add2('$');
  sa::add2('#');
  sa::add2('[');
  sa::add2('\\');
  sa::resp = 0;
  for (auto const &i : s)
  {
    sa::add(i);
  }
  cout << sa::resp << endl;
  for (auto const &i : t)
  {
    if (i == '-')
      sa::pop();
    else
      sa::add(i);
    cout << sa::resp << endl;
  }
}
// queries de:
// quantas substrings distintas aparecem pelo menos 2x na string
// append um char no fim da string
// pop o ultimo char da string

// como resolver o problema sem as queries de update?
// da pra resolver com suffix array
// a resposta eh a soma de max(0ll, lcp[i] - lcp[i - 1])

// mas ai precisamos lidar com os updates ne
// ai eh duro pq precisamos manter um suffix array dinamico, alem do array de lcp pra isso

// resolver o problema eh o mesmo de resolver o problema pra string reversa
// entao podemos pensar em adicionar um char no inicio ao inves do final
// dai temos que atualizar o novo suffix array alem de atualizar o lcp
// adicionar no inicio eh mais facil pq o novo char so impacta no sufixo q eh a string toda

// manter um suffix aray com hashing e um set de custom comparator, comparo dois sufixos
// achando o lcp deles, que eh fazendo uma busca binaria e comparando os hashings
// a partir que acho o primeiro char que difere, eh so ver eles e gg