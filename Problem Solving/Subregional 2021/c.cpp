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
#define MAXN 500001
//#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int base, n;
  cin >> base >> n;
  int mod = base + 1;
  vector<int> pot(n + 1);
  pot[0] = 1;
  for (int i = 1; i <= n; i++)
  {
    pot[i] = (pot[i - 1] * base) % mod;
  }
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  reverse(v.begin(), v.end());
  int curr = 0;
  for (int i = 0; i < n; i++)
  {
    int at = v[i];
    at = (at * pot[i]) % mod;
    curr += at;
    curr %= mod;
  }
  if (curr == 0)
  {
    cout << 0 << " " << 0 << endl;
    return 0;
  }
  for (int i = n - 1; i >= 0; i--)
  {
    int past = curr;
    int at = v[i];
    int idx = (n - 1) - i;
    at = (at * pot[i]) % mod;
    curr -= at;
    curr += mod;
    curr %= mod;
    if (curr < v[i])
    {
      int x = curr;
      int past2 = curr;
      int at2 = (x * pot[i]) % mod;
      curr += at2;
      curr %= mod;
      if (curr == 0)
      {
        cout << n - i << " " << x << endl;
        return 0;
      }
      curr = past2;
    }
    if (past < v[i])
    {
      int x = v[i] - past;
      int past2 = curr;
      int at2 = (x * pot[i]) % mod;
      curr += at2;
      curr %= mod;
      if (curr == 0)
      {
        cout << n - i << " " << x << endl;
        return 0;
      }
      curr = past2;
    }
    curr = past;
  }
  cout << -1 << " " << -1 << endl;
  return 0;
}