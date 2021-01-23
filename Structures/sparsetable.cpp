#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
 
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
#define PI acos(-1)
#define pb push_back
#define int long long int
#define pi pair<int, int>
#define pii pair<int, pair<int, pi>>
#define fir first
#define sec second
#define DEBUG 0
#define MAXN 10005
#define mod 1000000007
 
int n;
vector<int> v;
 
namespace st
{
  int st[MAXN][25];
  int log[MAXN + 1];
 
  void init()
  {
    log[1] = 0;
    for (int i = 2; i <= MAXN; i++)
      log[i] = log[i / 2] + 1;
    for (int i = 0; i < n; i++)
      st[i][0] = v[i];
    for (int j = 1; j <= 25; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
  }
  int query(int l, int r)
  {
    int j = log[r - l + 1];
    int minimum = min(st[l][j], st[r - (1 << j) + 1][j]);
    return minimum;
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}
