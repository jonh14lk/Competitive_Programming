#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, x;
  cin >> n >> x;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
  }
  double half = (double)x / 2;
  vector<int> le, gt;
  int eq = 0;
  for (int i = 0; i < n; i++)
  {
    if (v[i] > half)
      gt.push_back(v[i]);
    else if (v[i] < half)
      le.push_back(v[i]);
    else
      eq++;
  }
  sort(le.begin(), le.end());
  sort(gt.begin(), gt.end());
  if (le.size() > 0 && gt.size() > 0 && (le.back() + gt.front()) == x && (le.back() + gt.back()) == x)
  {
    reverse(le.begin(), le.end());
  }
  vector<int> merged1 = le;
  if (gt.size() > 0)
  {
    int id = 0;
    for (int i = 0; i < gt.size(); i++)
    {
      if (merged1.size() > 0 && (merged1.back() + gt[i]) != x)
      {
        id = i;
        break;
      }
    }
    merged1.push_back(gt[id]);
    for (int i = 0; i < gt.size(); i++)
    {
      if (i != id)
        merged1.push_back(gt[i]);
    }
  }
  // tem no maximo 1 par de adjacentes com soma == x
  // se tiver, tento ajeitar ele com um x / 2 no meio
  for (int i = 1; i < merged1.size(); i++)
  {
    if ((merged1[i] + merged1[i - 1]) == x && eq > 0)
    {
      merged1.insert(merged1.begin() + i, x / 2);
      eq--;
      break;
    }
  }
  // inserir os demais x / 2
  // nao pode ter dois (x / 2) adjacentes
  vector<int> merged2;
  int ptr = 0;
  for (int i = 0; i < n; i++)
  {
    bool can = (eq > 0);
    if (merged2.size() > 0 && (merged2.back() == (x / 2)))
    {
      can = false;
    }
    if (ptr < merged1.size() && (merged1[ptr] == (x / 2)))
    {
      can = false;
    }
    if (can)
    {
      merged2.push_back(x / 2);
      eq--;
    }
    else if (ptr < merged1.size())
    {
      merged2.push_back(merged1[ptr]);
      ptr++;
    }
    else
    {
      cout << "*\n";
      return 0;
    }
  }
  bool ok = 1;
  for (int i = 1; i < n; i++)
  {
    if ((merged2[i] + merged2[i - 1]) == x)
      ok = 0;
  }
  if (ok)
  {
    for (int i = 0; i < n; i++)
      cout << merged2[i] << " ";
    cout << endl;
  }
  else
  {
    cout << "*\n";
  }
}