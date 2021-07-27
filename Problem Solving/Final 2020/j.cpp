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
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 1000000007

int n, m, idx = 1;
int fac[8][MAXN];
vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};
cc_hash_table<int, int> cnt;

void rem(int idx, int x, int i)
{
  if (i == 8)
  {
    cnt[x]--;
    return;
  }
  int num = 1;
  for (int j = 0; j <= fac[i][idx]; j++)
  {
    rem(idx, x * num, i + 1);
    num *= primes[i];
  }
}
void add(int idx, int x, int i)
{
  if (i == 8)
  {
    cnt[x]++;
    return;
  }
  int num = 1;
  for (int j = 0; j <= fac[i][idx]; j++)
  {
    add(idx, x * num, i + 1);
    num *= primes[i];
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  while (n--)
  {
    char c;
    cin >> c;
    if (c == 'C')
    {
      int k;
      cin >> k;
      for (int i = 0; i < k; i++)
      {
        int x;
        cin >> x;
        x--;
        fac[x][idx]++;
      }
      add(idx, 1, 0);
      idx++;
    }
    else if (c == 'D')
    {
      int idx;
      cin >> idx;
      rem(idx, 1, 0);
    }
    else
    {
      int k;
      cin >> k;
      int x = 1;
      for (int i = 0; i < k; i++)
      {
        int t;
        cin >> t;
        t--;
        x *= primes[t];
      }
      cout << cnt[x] << endl;
    }
  }
  return 0;
}