#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define MAXN 200005
#define pi pair<int, int>
#define pii pair<pi, int>
#define pb push_back
#define fir first
#define sec second

signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  string s;
  cin >> s;
  int n = s.size();
  vector<int> a(n);
  vector<int> cnt(2, 0);
  for (int i = 0; i < n; i++)
  {
    a[i] = s[i] - '0';
    cnt[a[i]]++;
  }
  int mn = -1, mx = -1;
  for (int i = 0; i < n; i++)
  {
    swap(cnt[0], cnt[1]);
    int sp = i % 2;
    cnt[(a[i] ^ sp)]++;
    cnt[a[i] ^ 1 ^ sp]--;
    if (i == 0 || mn > cnt[1])
      mn = cnt[1];
    if (i == 0 || mx < cnt[1])
      mx = cnt[1];
  }
  cout << mn << " " << mx << endl;
}
