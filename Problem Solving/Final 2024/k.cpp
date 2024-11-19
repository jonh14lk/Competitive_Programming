#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pi pair<int, int>
#define fir first
#define sec second
#define pb push_back
#define PI acos(-1)

signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int k;
  string s;
  cin >> k >> s;
  if (k == 2)
  {
    string a, b;
    int aa = 0, bb = 0;
    for (int i = 0; i < s.size(); i++)
    {
      if (i % 2 == 0)
      {
        a.pb('0');
        b.pb('1');
      }
      else
      {
        a.pb('1');
        b.pb('0');
      }

      if (a[i] != s[i])
        aa++;
      if (b[i] != s[i])
        bb++;
    }
    if (aa < bb)
      cout << aa << " " << a << endl;
    else
      cout << bb << " " << b << endl;
    return 0;
  }
  int l = -1, r = -1;
  char curr = '?';
  vector<pi> vec;
  for (int i = 0; i < s.size(); i++)
  {
    if (curr != s[i])
    {
      if (l != -1)
        vec.pb({l, r});
      l = i, r = i;
    }
    else
    {
      r++;
    }
    curr = s[i];
  }
  vec.pb({l, r});
  int ops = 0;
  for (auto [l, r] : vec)
  {
    int pos = l + k - 1;
    while (pos <= r)
    {
      ops++;
      if (pos == r)
      {
        pos -= (k - 2);
      }
      s[pos] = (s[pos] == '0') ? '1' : '0';
      pos += k;
    }
  }
  cout << ops << " " << s << endl;
}