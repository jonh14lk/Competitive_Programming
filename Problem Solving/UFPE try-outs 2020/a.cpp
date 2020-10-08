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
 
vector<int> d1;
vector<int> d2;
 
void manacher(string s)
{
  d1.resize(s.size());
  d2.resize(s.size());
  int l = 0, r = -1;
  for (int i = 0; i < s.size(); i++)
  {
    int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
    while (0 <= i - k && i + k < s.size() && s[i - k] == s[i + k])
      k++;
    d1[i] = k;
    k = k - 1;
    if (i + k > r)
      l = i - k, r = i + k;
  }
  l = 0, r = -1;
  for (int i = 0; i < s.size(); i++)
  {
    int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
    while (0 <= i - k - 1 && i + k < s.size() && s[i - k - 1] == s[i + k])
      k++;
    d2[i] = k;
    k = k - 1;
    if (i + k > r)
      l = i - k - 1, r = i + k;
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  manacher(s);
  bool ok = false;
  if (k & 1)
  {
    k = (k + 1) >> 1;
    for (int i = 0; i < n; i++)
      if (d1[i] >= k)
        ok = true;
  }
  else
  {
    k = k >> 1;
    for (int i = 0; i < n; i++)
      if (d2[i] >= k)
        ok = true;
  }
  (ok) ? cout << "Accept\n" : cout << "Reject\n";
  return 0;
}