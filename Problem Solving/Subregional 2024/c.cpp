#include <bits/stdc++.h>

using namespace std;

#define int long long int
#define pi pair<int, int>
#define pii pair<pi, int>
#define pci pair<char, int>
#define pb push_back
#define fir first
#define sec second

vector<int> suffix_array(vector<int> s)
{
  s.pb(0);
  int n = s.size(), N = n + 1;
  vector<int> sa(n), ra(n);
  for (int i = 0; i < n; i++)
    sa[i] = i, ra[i] = s[i];

  for (int k = 0; k < n; k ? k *= 2 : k++)
  {
    vector<int> nsa(sa), nra(n), cnt(N, 0);
    for (int i = 0; i < n; i++)
      nsa[i] = (nsa[i] - k + n) % n,
      cnt[ra[i]]++;

    for (int i = 1; i < N; i++)
      cnt[i] += cnt[i - 1];
    for (int i = n - 1; i + 1; i--)
      sa[--cnt[ra[nsa[i]]]] =
          nsa[i];

    for (int i = 1, r = 0; i < n; i++)
      nra[sa[i]] = r +=
          ra[sa[i]] !=
              ra[sa[i - 1]] or
          ra[(sa[i] + k) % n] !=
              ra[(sa[i - 1] + k) % n];

    ra = nra;
    if (ra[sa[n - 1]] == n - 1)
      break;
  }
  return vector<int>(sa.begin() + 1, sa.end());
}
vector<int> kasai(vector<int> s, vector<int> sa)
{
  int n = s.size(), k = 0;
  vector<int> ra(n), lcp(n);
  for (int i = 0; i < n; i++)
    ra[sa[i]] = i;
  for (int i = 0; i < n; i++, k -= !!k)
  {
    if (ra[i] == n - 1)
    {
      k = 0;
      continue;
    }
    int j = sa[ra[i] + 1];
    while (i + k < n and j + k < n and s[i + k] == s[j + k])
      k++;
    lcp[ra[i]] = k;
  }
  return lcp;
}
struct rmq
{
  int n;
  vector<vector<pi>> m;
  vector<int> log;

  rmq() {}
  rmq(vector<pi> &v)
  {
    n = v.size();
    log.resize(n + 1);
    log[1] = 0;
    for (int i = 2; i <= n; i++)
      log[i] = log[i / 2] + 1;
    int sz = log[n] + 2;
    m = vector<vector<pi>>(sz, vector<pi>(n + 1));
    for (int i = 0; i < n; i++)
    {
      m[0][i] = v[i];
    }
    for (int j = 1; j < sz; j++)
    {
      for (int i = 0; i + (1 << j) <= n; i++)
        m[j][i] = min(m[j - 1][i], m[j - 1][i + (1 << (j - 1))]);
    }
  }
  int qry(int a, int b)
  {
    return min(m[log[b - a + 1]][a], m[log[b - a + 1]][b - (1 << log[b - a + 1]) + 1]).second;
  }
};

vector<pi> l;
rmq rm;

int solve(int a, int b)
{
  if (a > b)
    return 0;
  int mid = rm.qry(a, b);
  int tot = (mid - a + 1) * (b - mid + 1);
  tot *= l[mid].fir;
  tot += solve(a, mid - 1);
  tot += solve(mid + 1, b);
  return tot;
}
signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  vector<int> sa = suffix_array(v);
  vector<int> lcp = kasai(v, sa);
  for (int i = 0; i + 1 < lcp.size(); i++)
    l.pb({2 * lcp[i], l.size()}); // bob no i e charlie no j, ou o contrario
  int sum = 0;
  for (int i = 1; i <= n; i++) // quando caem no mesmo indice gg
    sum += i;
  // eu quero isso de forma eficiente
  // achar a soma dos minimos de todo subarray de l e dale
  // for (int i = 0; i < l.size(); i++)
  // {
  //     int mn = 1e18;
  //     for (int j = i; j < l.size(); j++)
  //     {
  //         mn = min(mn, l[j]);
  //         sum += mn;
  //     }
  // }
  rm = rmq(l);
  sum += solve(0, (int)l.size() - 1);
  int tot = (n * n);
  int g = __gcd(sum, tot);
  sum /= g;
  tot /= g;
  cout << sum << "/" << tot << endl;
  return 0;
}