#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// #define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 257
#define mod 998244353

int n, m;
int pos[MAXN];
int pos2[MAXN];
int on[MAXN];

void multiply()
{
  for (int i = 0; i < n; i++)
    pos[i] = pos2[pos[i]];
}
void ccnot(int c1, int c2, int t)
{
  t = (1 << t);
  for (int i = 0; i < n; i++)
  {
    if ((i & (1 << c1)) && (i & (1 << c2)))
      pos2[i] = (i ^ t);
    else
      pos2[i] = i;
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  n = (1ll << n);
  for (int i = 0; i < n; i++)
  {
    pos[i] = i;
  }
  while (m--)
  {
    int t;
    cin >> t;
    if (t == 1)
    {
      int c, t;
      cin >> c >> t;
      ccnot(c, c, t);
      multiply();
    }
    else
    {
      int c1, c2, t;
      cin >> c1 >> c2 >> t;
      ccnot(c1, c2, t);
      multiply();
    }
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      (pos[i] == j) ? cout << "1" : cout << "0";
    cout << endl;
  }
  return 0;
}