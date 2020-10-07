#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 100001
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<string> notas = {"do", "do#", "re", "re#", "mi", "fa", "fa#", "sol", "sol#", "la", "la#", "si"};
  vector<int> curr = {2, 2, 1, 2, 2, 2, 1};
  vector<int> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    v[i]--;
    v[i] = v[i] % notas.size();
  }
  for (int i = 0; i < notas.size(); i++)
  {
    bool can = true;
    set<int> s;
    int pref = i;
    s.insert(pref);
    for (auto const &j : curr)
    {
      pref = (pref + j) % notas.size();
      s.insert(pref);
    }
    for (auto const &j : v)
      if (s.find(j) == s.end())
        can = false;
    if (can)
    {
      cout << notas[i] << endl;
      return 0;
    }
  }
  cout << "desafinado\n";
}