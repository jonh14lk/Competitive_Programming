#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 305
#define mod 998244353

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> v(n);
  vector<int> pos(n + 1, 0);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    pos[v[i]] = i + 1;
  }
  for (int i = 0; i < n; i++)
  {
    v[i] = pos[i + 1];
  }
  int need = 0, i = 0;
  while (i < n)
  {
    need++;
    while (i + 1 < n && v[i + 1] > v[i])
      i++;
    i++;
  }
  int pot = 0;
  while ((1 << pot) < need)
    pot++;
  cout << pot << endl;
  return 0;
}