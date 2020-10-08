#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 101
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    string s;
    cin >> s;
    int best = -1;
    for (int i = 0; i < s.size(); i++)
    {
      string t = s;
      s.erase(s.begin() + i);
      int curr = stoll(s);
      best = max(best, curr);
      s = t;
    }
    cout << best << endl;
  }
}