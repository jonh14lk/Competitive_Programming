#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 50001
#define mod 1000000007

struct item
{
  int t, i;
  string s;
};

vector<item> save;
vector<pair<string, int>> all_words;
vector<int> priority;

namespace aho
{
  const int K = 26;
  struct trie
  {
    char me;
    set<pi> idxs;
    int down[K];
    trie(char ch = '$') : me(ch)
    {
      fill(begin(down), end(down), -1);
    }
  };
  vector<trie> ac;
  void init()
  {
    ac.resize(1);
  }
  void add_string(int idx)
  {
    int v = 0;
    for (auto const &ch : save[idx].s)
    {
      int c = ch - 'a';
      if (ac[v].down[c] == -1)
      {
        ac[v].down[c] = ac.size();
        ac.emplace_back(ch);
      }
      v = ac[v].down[c];
      ac[v].idxs.insert({priority[idx], idx});
    }
  }
  void rem_string(int idx)
  {
    int v = 0;
    for (auto const &ch : save[idx].s)
    {
      int c = ch - 'a';
      v = ac[v].down[c];
      ac[v].idxs.erase({priority[idx], idx});
    }
  }
  void query(int idx)
  {
    int v = 0;
    for (auto const &ch : save[idx].s)
    {
      int c = ch - 'a';
      if (ac[v].down[c] == -1)
      {
        cout << -1 << endl;
        return;
      }
      v = ac[v].down[c];
    }
    if (!ac[v].idxs.size())
    {
      cout << -1 << endl;
    }
    else
    {
      pi ans = *ac[v].idxs.begin();
      cout << ans.sec + 1 << endl;
    }
  }
} // namespace aho
bool cmp(pair<string, int> a, pair<string, int> b)
{
  if (a.fir.size() != b.fir.size())
    return a.fir.size() < b.fir.size();
  return a.fir < b.fir;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  aho::init();
  int q;
  cin >> q;
  save.resize(q);
  priority.resize(q);
  for (int i = 0; i < q; i++)
  {
    cin >> save[i].t;
    if (save[i].t == 1)
    {
      cin >> save[i].s;
      all_words.pb({save[i].s, i});
    }
    else if (save[i].t == 2)
    {
      cin >> save[i].i;
      save[i].i--;
    }
    else
    {
      cin >> save[i].s;
    }
  }
  sort(all_words.begin(), all_words.end(), cmp);
  int curr = 0;
  for (auto const &i : all_words)
  {
    priority[i.sec] = curr;
    curr++;
  }
  for (int i = 0; i < q; i++)
  {
    if (save[i].t == 1)
    {
      aho::add_string(i);
    }
    else if (save[i].t == 2)
    {
      aho::rem_string(save[i].i);
    }
    else
    {
      aho::query(i);
    }
  }
  return 0;
}