#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1000004
#define mod 998244353

vector<string> dale = {"010",
                       "110",
                       "111",
                       "101",
                       "100",
                       "000",
                       "001",
                       "011"};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  int rot = -1;
  for (int i = 0; i < dale.size(); i++)
  {
    if (dale[i] == s)
    {
      rot = i;
      break;
    }
  }
  assert(rot != -1);
  rotate(dale.begin(), dale.begin() + rot, dale.end());
  for (auto const &i : dale)
  {
    cout << i << endl;
  }
  cout << s << endl;
  return 0;
}