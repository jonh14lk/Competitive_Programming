#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
 
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
#define int long long int
#define pb push_back
#define mp make_pair
#define pi pair<int, int>
#define pii pair<pi, int>
#define pci pair<char, int>
#define fir first
#define sec second
#define DEBUG 0
#define MAXN 300001
#define mod 1000000007

int multiplicate(int x, int y)
{
  return (x * y) % mod;
}
int subtract(int a, int b)
{
  return (a - b < 0) ? a - b + mod : a - b;
}
int sum(int a, int b)
{
  return (a + b >= mod) ? a + b - mod : a + b;
}

namespace sh
{
  const int d = 227;
  vector<int> hashes(MAXN);
  vector<int> pref(MAXN);
  vector<int> pot(MAXN);
  vector<int> m[MAXN];
  
  int get_hash(string s)
  {
    int ans = 0;
    for (int i = 0; i < s.size(); i++)
    {
      int val = multiplicate(ans, d);
      ans = sum(s[i], val);
    }
    return ans;
  }
  void prefix_hash(string s)
  {
    pref[0] = 0;
    for (int i = 0; i < s.size(); i++)
    {
      int val = multiplicate(pref[i], d);
      pref[i + 1] = sum(s[i], val);
    }
  }
  int get_substring(int l, int r)
  {
    return subtract(pref[r + 1], multiplicate(pref[l], pot[r - l + 1]));
  }
  void calc()
  {
    pot[0] = 1;
    for (int i = 1; i < MAXN; i++)
      pot[i] = multiplicate(pot[i - 1], d);
  }
}
