#include <bits/stdc++.h>

using namespace std;

#define int long long int
#define pi pair<int, int>
#define fir first
#define sec second

pi sum(pi a, pi b)
{
  pi ans;
  ans.sec = (a.sec == b.sec) ? a.sec : (a.sec * b.sec);
  ans.fir = a.fir * (ans.sec / a.sec) + b.fir * (ans.sec / b.sec);
  return ans;
}
signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<pi> a(n + 1);
  a[0] = {1, 1};
  for (int i = 1; i <= n; i++)
  {
    a[i] = sum(pi(1, 1), a[i - 1]);
    swap(a[i].fir, a[i].sec);
    int g = __gcd(a[i].fir, a[i].sec);
    a[i].fir /= g;
    a[i].sec /= g;
  }
  cout << a[n].fir << endl;
  return 0;
}