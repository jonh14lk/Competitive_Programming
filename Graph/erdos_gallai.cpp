#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define pci pair<char, int>
#define fir first
#define sec second
#define MAXN 100005
#define mod 998244353

bool erdos_gallai(vector<int> &v)
{
  int sum = 0, n = v.size();
  for (auto const &i : v)
  {
    sum += i;
  }
  if (sum % 2)
  {
    return false;
  }
  sort(v.rbegin(), v.rend());
  vector<int> suf(n + 1, 0);
  int qt = 0, ptr = n;
  sum = 0;
  for (int i = n - 1; i >= 0; i--)
  {
    if (v[i] >= i)
    {
      qt++;
    }
    else
    {
      sum += v[i];
      ptr = i;
    }
    while (ptr < n && v[ptr] >= i)
    {
      qt++;
      sum -= v[ptr];
      ptr++;
    }
    suf[i] = sum + (qt * i);
  }
  sum = 0;
  bool ok = 1;
  for (int i = 0; i < n; i++)
  {
    sum += v[i];
    int curr = i * (i + 1) + suf[i + 1];
    ok &= (sum <= curr);
  }
  return ok;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
      cin >> v[i];
    (erdos_gallai(v)) ? cout << "Y\n" : cout << "N\n";
  }
  return 0;
}
// https://codeforces.com/gym/101726/problem/A
// erdos gallai
// dado uma sequencia de n inteiros d[0], d[1], ..., d[n - 1]
// quero saber se existe um grafo simples e undirected com n vertices
// tal que o grau do i-esimo vertice é igual a d[i]