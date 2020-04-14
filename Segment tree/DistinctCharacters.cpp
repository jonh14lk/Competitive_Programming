#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
 
set<int> s[26];
string st;
int q, t, l, r, k;
char c;
 
int main()
{
  cin >> st;
 
  for (int i = 0; i < st.size(); i++)
  {
    s[st[i] - 'a'].insert(i);
  }
 
  cin >> q;
 
  while (q--)
  {
    cin >> t;
 
    if (t == 1)
    {
      cin >> k >> c;
      k--;
 
      s[st[k] - 'a'].erase(k);
      s[c - 'a'].insert(k);
      st[k] = c;
    }
    else if (t == 2)
    {
      cin >> l >> r;
 
      l--;
      r--;
 
      int ans = 0;
 
      for (int i = 0; i < 26; i++)
      {
        auto it = s[i].lower_bound(l);
 
        if (it != s[i].end() && *it <= r)
        {
          ans++;
        }
      }
 
      cout << ans << endl;
    }
  }
  return 0;
}
