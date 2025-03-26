#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, pi>
#define fir first
#define sec second
#define MAXN 1000006
#define mod 1000000007

list<int> v;
list<int>::iterator ptr[MAXN];
bool on[MAXN];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  srand(time(NULL));
  int n;
  cin >> n;
  vector<int> p(n);
  for (int i = 0; i < n; i++)
  {
    cin >> p[i];
    v.pb(p[i]);
    on[p[i]] = 1;
  }
  auto it = v.begin();
  while (it != v.end())
  {
    ptr[*it] = it;
    it++;
  }
  int q;
  cin >> q;
  while (q--)
  {
    char c;
    cin >> c;
    if (c == '?')
    {
      int m;
      cin >> m;
      vector<int> a(m);
      for (int i = 0; i < m; i++)
        cin >> a[i];
      for (int i = 0; i < m; i++)
        a.pb(a[i]);
      int ans = 0, curr = 0;
      auto prv_it = v.begin();
      for (auto const &i : a)
      {
        if (!on[i])
        {
          curr = 0;
        }
        else
        {
          if (curr == 0)
          {
            curr++;
            prv_it = ptr[i];
          }
          else
          {
            auto aux = prv_it;
            aux++;
            if (aux == v.end())
              aux = v.begin();
            if ((*aux) == i)
            {
              curr++;
              prv_it = aux;
            }
            else
            {
              curr = 1;
              prv_it = ptr[i];
            }
          }
        }
        ans = max(ans, curr);
      }
      if (ans > m)
        cout << "*\n";
      else
        cout << ans << endl;
    }
    else if (c == '-')
    {
      int x;
      cin >> x;
      v.erase(ptr[x]);
      on[x] = 0;
    }
    else
    {
      int a, b;
      cin >> a >> b;
      ptr[a] = v.insert(ptr[b], a);
      on[a] = 1;
    }
  }
  return 0;
}