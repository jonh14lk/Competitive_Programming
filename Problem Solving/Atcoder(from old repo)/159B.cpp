#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
 
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
 
  string s, r;
  cin >> s;
  r = s;
 
  reverse(r.begin(), r.end());
 
  bool can = true;
 
  if (s != r)
  {
    can = false;
  }
 
  int i = (s.size() - 1) / 2, f;
 
  string s2 = s.substr(0, i);
  string r2 = s2;
  reverse(r2.begin(), r2.end());
 
  if (s2 != r2)
  {
    can = false;
  }
 
  i = (s.size() + 3) / 2;
  f = s.size() - i;
 
  s2 = s.substr(i - 1, f + 1);
  r2 = s2;
  reverse(r2.begin(), r2.end());
 
  if (s2 != r2)
  {
    can = false;
  }
 
  (can) ? cout << "Yes\n" : cout << "No\n";
  return 0;
}
