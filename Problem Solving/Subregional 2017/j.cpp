#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 100002
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  int acc = 0;
  for (int i = 0; i < s.size(); i++)
    acc += (s[i] - '0');
  cout << acc % 3 << endl;
}
// 1 - 2 - 1 - 2 - 1