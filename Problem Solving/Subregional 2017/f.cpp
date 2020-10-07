#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 5001
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n >> k;
  vector<int> v(n);
  vector<int> cnt(1001, 0);
  for (int i = 0; i < n; i++)
    cin >> v[i], cnt[v[i]]++;
  int acc = 0;
  for (int i = 1000; i >= 0; i--)
  {
    acc += cnt[i];
    if (acc >= k)
      break;
  }
  cout << acc << endl;
}