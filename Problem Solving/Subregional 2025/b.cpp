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
#define MAXN 100005

const int inf = 1e18;

const int MOD = (1ll << 61) - 1;
int P;
int mulmod(int a, int b)
{
  const static int LOWER = (1ll << 30) - 1, GET31 = (1ll << 31) - 1;
  int l1 = a & LOWER, h1 = a >> 30, l2 = b & LOWER, h2 = b >> 30;
  int m = l1 * h2 + l2 * h1, h = h1 * h2;
  int ans = l1 * l2 + (h >> 1) + ((h & 1) << 60) + (m >> 31) + ((m & GET31) << 30) + 1;
  ans = (ans & MOD) + (ans >> 61), ans = (ans & MOD) + (ans >> 61);
  return ans - 1;
}
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int uniform(int l, int r)
{
  uniform_int_distribution<int> uid(l, r);
  return uid(rng);
}
struct string_hashing
{
  vector<int> h, p;
  string_hashing() {}
  string_hashing(vector<int> &s) : h(s.size()), p(s.size())
  {
    p[0] = 1, h[0] = s[0];
    for (int i = 1; i < s.size(); i++)
      p[i] = mulmod(p[i - 1], P), h[i] = (mulmod(h[i - 1], P) + s[i]) % MOD;
  }
  int get(int l, int r)
  {
    int hash = h[r] - (l ? mulmod(h[l - 1], p[r - l + 1]) : 0);
    return hash < 0 ? hash + MOD : hash;
  }
  int append(int h, int hb, int blen)
  {
    return (hb + mulmod(h, p[blen])) % MOD;
  }
};

vector<pi> eq;
map<int, int> by_mod;

bool check(pi curr)
{
  if (by_mod.find(curr.sec) != by_mod.end())
  {
    return by_mod[curr.sec] == curr.fir;
  }
  // no maximo O(sqrt(n)) mods distintos
  // ja que tem O(sqrt(n)) tamanhos de ciclos distintos na permutacao
  // ja que a soma dos tamanhos dos ciclos da permutacao eh igual a n
  for (auto [x, mod] : eq)
  {
    if ((curr.fir - x) % __gcd(curr.sec, mod))
      return 0;
  }
  return 1;
}
void add(pi curr)
{
  eq.pb(curr);
  by_mod[curr.sec] = curr.fir;
}
__int128 gcd(__int128 a, __int128 b, __int128 &x, __int128 &y)
{
  if (b == 0)
  {
    x = 1, y = 0;
    return a;
  }
  __int128 x1, y1, d = gcd(b, a % b, x1, y1);
  x = y1, y = x1 - y1 * (a / b);
  return d;
}
void crt()
{
  __int128 trash, trash2;
  __int128 a1 = eq[0].fir, m1 = eq[0].sec;
  a1 %= m1;
  for (int i = 1; i < eq.size(); i++)
  {
    __int128 a2 = eq[i].fir, m2 = eq[i].sec;
    __int128 g = gcd(m1, m2, trash, trash2);
    __int128 p, q;
    gcd(m1 / g, m2 / g, p, q);
    __int128 mod = m1 / g * m2;
    __int128 x = (a1 * (m2 / g) % mod * q % mod + a2 * (m1 / g) % mod * p % mod) % mod;
    a1 = x;
    if (a1 < 0)
      a1 += mod;
    m1 = mod;
    if (m1 > 1000000000)
      break;
  }
  if (a1 > 1000000000)
  {
    cout << "DEMAIS\n";
    return;
  }
  for (auto const &i : eq)
  {
    if (a1 % i.sec != i.fir)
    {
      cout << "DEMAIS\n";
      return;
    }
  }
  cout << (int)a1 << endl;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  P = uniform(256, MOD - 1);
  int n;
  cin >> n;
  vector<int> a(n);
  vector<int> b(n);
  vector<int> p(n);
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++)
  {
    cin >> b[i];
  }
  for (int i = 0; i < n; i++)
  {
    cin >> p[i];
    p[i]--;
  }
  vector<bool> vis(n, 0);
  for (int i = 0; i < n; i++)
  {
    if (vis[i])
      continue;
    int x = i;
    vector<int> cyc;
    while (!vis[x])
    {
      cyc.pb(x);
      vis[x] = 1;
      x = p[x];
    }
    vector<int> va, vb;
    for (auto const &j : cyc)
    {
      va.pb(a[j]);
      vb.pb(b[j]);
    }
    for (auto const &j : cyc)
    {
      va.pb(a[j]);
    }
    int num_matches = 0, first_match = inf;
    string_hashing ha(va), hb(vb);
    for (int i = 0; i < cyc.size(); i++)
    {
      if (ha.get(i, i + cyc.size() - 1) == hb.get(0, cyc.size() - 1))
      {
        num_matches++;
        first_match = min(first_match, ((int)cyc.size() - i) % (int)cyc.size());
      }
    }
    if (first_match == inf)
    {
      cout << "IMPOSSIVEL\n";
      return 0;
    }
    assert(cyc.size() % num_matches == 0);
    pi curr_eq = {first_match, cyc.size() / num_matches};
    if (!check(curr_eq))
    {
      cout << "IMPOSSIVEL\n";
      return 0;
    }
    add(curr_eq);
  }
  crt();
  return 0;
}
// tem o ciclo da permutacao
// entao para posicoes de a, tem que ser alguem do ciclo
// dps disso, eh ver quais rotacoes do ciclo da matching com o ciclo esperado
// pode ter mais de uma rotacao valida do ciclo

// no final das contas eu vou ter algo como
// pro primeiro ciclo vai ser valido se:
// x % sz[0] = a ou x % sz[0] = b, ...

// pro segundo ciclo vai ser valido se:
// x % sz[1] = c ou x % sz[1] = d, ...

// isso pra cada ciclo da permutacao
// e queremos achar o menor x que satisfaz

// dado que eu fixei um ciclo
// se existir um matching valido, entao vai existir um periodo de rotacao minimo x
// que a cada x rotacoes vai voltar pro estado de matching daquele ciclo
// so que esse x eh um divisor do tamanho do ciclo, essa eh a sacada
// entao no fim vai ser meio que o problema como se a e b fossem permutacoes msm