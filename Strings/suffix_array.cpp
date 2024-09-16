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
#define pii pair<pi, int>
#define pci pair<char, int>
#define fir first
#define sec second
#define MAXN 500001
#define mod 1000000007

vector<int> suffix_array(string s)
{
  s += "$"; // menor do que todos os chars da string st
  int n = s.size(), N = max(n + 1, 260ll);
  vector<int> sa(n), ra(n);
  for (int i = 0; i < n; i++)
  {
    sa[i] = i, ra[i] = s[i];
  }
  for (int k = 0; k < n; k ? k *= 2 : k++)
  {
    vector<int> nsa(sa), nra(n), cnt(N);
    for (int i = 0; i < n; i++)
    {
      nsa[i] = (nsa[i] - k + n) % n;
      cnt[ra[i]]++;
    }
    for (int i = 1; i < N; i++)
    {
      cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i + 1; i--)
    {
      sa[--cnt[ra[nsa[i]]]] = nsa[i];
    }
    for (int i = 1, r = 0; i < n; i++)
    {
      nra[sa[i]] = r += (ra[sa[i]] != ra[sa[i - 1]] || ra[(sa[i] + k) % n] != ra[(sa[i - 1] + k) % n]);
    }
    ra = nra;
    if (ra[sa[n - 1]] == n - 1)
      break;
  }
  return vector<int>(sa.begin() + 1, sa.end());
}

vector<int> kasai(string s, vector<int> sa)
{
  int n = s.size(), k = 0;
  vector<int> ra(n), lcp(n);
  for (int i = 0; i < n; i++)
  {
    ra[sa[i]] = i;
  }
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
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  int n = s.size();
  vector<int> p = suffix_array(s);
  vector<int> lcp = kasai(s, p);
  for (int i = 0; i < s.size(); i++) // sufix array
    cout << p[i] << " ";
  cout << endl;
  for (int i = 0; i + 1 < s.size(); i++) // lcp entre 2 suffixos adjacentes no suffix array
    cout << lcp[i] << " ";
  cout << endl;
  int q;
  cin >> q;
  while (q--)
  {
    string t;
    cin >> t;
    int i = 0, f = n - 1, m, lb, ub;
    while (i < f)
    {
      m = (i + f) / 2;
      (t <= s.substr(p[m], t.size())) ? f = m : i = m + 1;
    }
    ub = i, i = 0, f = n - 1;
    while (i < f)
    {
      m = (i + f) / 2;
      (t >= s.substr(p[m], t.size())) ? i = m + 1 : f = m;
    }
    lb = i;
    if (s.substr(p[lb], t.size()) == t)
      lb++;
    cout << lb - ub << endl;
  }
  return 0;
}
