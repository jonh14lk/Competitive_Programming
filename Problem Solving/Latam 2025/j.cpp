#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 10005
#define mod 998244353

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, d;
  cin >> n >> d;
  vector<int> v(n, 0);
  vector<int> cnt(d + 1, 0);
  for (int i = 0; i < d; i++)
  {
    int k;
    cin >> k;
    for (int j = 0; j < k; j++)
    {
      v[j]++;
      cnt[v[j]]++;
    }
    int ptr = 0;
    for (int j = 1; j <= d; j++)
    {
      while (cnt[j])
      {
        v[ptr] = j;
        ptr++;
        cnt[j]--;
      }
    }
  }
  cout << (*max_element(v.begin(), v.end())) << endl;
  return 0;
}