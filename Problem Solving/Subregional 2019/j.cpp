#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define DEBUG false

//A23456789DQJK
map<char, int> baralho = {
    {'0', 0},
    {'A', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'D', 10},
    {'Q', 11},
    {'J', 12},
    {'K', 13},
};

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n >> k;
  k--;
  vector<int> adj[n];
  adj[k].pb(0);
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      char c;
      cin >> c;
      adj[i].pb(baralho[c]);
    }
  }
  vector<bool> coringa(n, false);
  coringa[k] = true;
  if (DEBUG)
  {
    for (int k = 0; k < n; k++)
    {
      for (auto const &j : adj[k])
        cout << j << " ";
      cout << endl;
    }
    cout << endl;
  }
  for (int f = k;; f++)
  {
    f = f % n;
    map<int, int> cnt;
    for (auto const &j : adj[f])
      cnt[j]++;
    int best = INT_MAX, aux = INT_MAX, idx = 0, curr = 0;
    for (auto const &j : adj[f])
    {
      if (j == 0)
      {
        if (coringa[f])
          coringa[f] = false;
        else
        {
          coringa[(f + 1) % n] = true;
          idx = curr;
          best = cnt[j];
          aux = j;
          break;
        }
      }
      else if (cnt[j] < best || (cnt[j] == best && j < aux))
      {
        idx = curr;
        best = cnt[j];
        aux = j;
      }
      curr++;
    }
    adj[f].erase(adj[f].begin() + idx);
    adj[(f + 1) % n].pb(aux);
    if (DEBUG)
    {
      cout << f << endl;
      for (int k = 0; k < n; k++)
      {
        for (auto const &j : adj[k])
          cout << j << " ";
        cout << endl;
      }
      cout << endl;
    }
    for (int k = 0; k < n; k++)
    {
      set<int> s;
      for (auto const &j : adj[k])
        s.insert(j);
      if (s.size() == 1)
      {
        cout << k + 1 << endl;
        return 0;
      }
    }
  }
  return 0;
}