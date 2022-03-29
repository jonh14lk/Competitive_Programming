#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class string>
using ordered_set = tree<string, null_type, less<string>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 2001
#define mod 1000000007

int max_suffix(string s, bool mi = false)
{
  s.push_back(*min_element(s.begin(), s.end()) - 1);
  int ans = 0;
  for (int i = 1; i < s.size(); i++)
  {
    int j = 0;
    while (ans + j < i and s[i + j] == s[ans + j])
      j++;
    if (s[i + j] > s[ans + j])
    {
      if (!mi or i != s.size() - 2)
        ans = i;
    }
    else if (j)
      i += j - 1;
  }
  return ans;
}
int min_suffix(string s)
{
  for (auto &i : s)
    i *= -1;
  s.push_back(*max_element(s.begin(), s.end()) + 1);
  return max_suffix(s, true);
}
int max_cyclic_shift(string s)
{
  int n = s.size();
  for (int i = 0; i < n; i++)
    s.pb(s[i]);
  return max_suffix(s);
}
int min_cyclic_shift(string s)
{
  for (auto &i : s)
    i *= -1;
  return max_cyclic_shift(s);
}
// retorna a posicao de inicio menor/maior sufixo/shift de uma string