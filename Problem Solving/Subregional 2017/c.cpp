#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 100001
#define mod 1000000007

int lcm(int a, int b)
{
  return (a / __gcd(a, b)) * b;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, l;
  cin >> n >> l;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  int lc = v[0];
  for (int i = 1; i < n; i++)
    lc = lcm(lc, v[i]);
  int ans = INT_MIN, idx = 1;
  for (int i = 1; i <= l; i++)
  {
    int curr = lcm(lc, i);
    if (curr > ans && curr <= l)
    {
      ans = curr;
      idx = i;
    }
  }
  cout << idx << endl;
}