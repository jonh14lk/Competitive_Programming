#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define mp make_pair
#define pi pair<string, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 131072
#define MAXL 20
#define mod 998244353

vector<string> handles;
map<string, int> m;
map<string, int> m2;

signed main()
{
  int c, p, s;
  cin >> c >> p >> s;
  handles.resize(c);
  for (int i = 0; i < c; i++)
    cin >> handles[i], m.insert(mp(handles[i], 0));
  for (int i = 0; i < p; i++)
  {
    string a;
    int b;
    cin >> a >> b;
    m2.insert(mp(a, b));
  }
  for (int i = 0; i < s; i++)
  {
    string a, b, c;
    cin >> a >> b >> c;
    if (c == "AC")
      m[a] += m2[b];
  }
  for (auto const &i : handles)
    cout << i << " " << m[i] << endl;
  return 0;
}
