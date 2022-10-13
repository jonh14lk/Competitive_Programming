#include <bits/stdc++.h>

using namespace std;
#define int long long int
#define fir first
#define sec second
#define pb push_back
#define mod 1000000009
#define pi pair<int, int>
#define MAXN 100005

int sum;
int ans[MAXN];
int c1[MAXN];
int c2[MAXN];
vector<pi> adj[MAXN];
vector<int> v[MAXN];
int c[MAXN];
int sz[MAXN];

void add(int i)
{
    sum -= (c2[c[i]] * c1[c[i]]);
    c2[c[i]]--;
    c1[c[i]]++;
    sum += (c2[c[i]] * c1[c[i]]);
}
void rem(int i)
{
    sum -= (c2[c[i]] * c1[c[i]]);
    c2[c[i]]++;
    c1[c[i]]--;
    sum += (c2[c[i]] * c1[c[i]]);
}
void dfs_sz(int x, int p)
{
    sz[x] = 1;
    for (auto const &i : adj[x])
    {
        if (i.fir != p)
        {
            dfs_sz(i.fir, x);
            sz[x] += sz[i.fir];
        }
    }
}
void dfs(int x, int p, bool keep, int id)
{
    int best = -1, big_child = -1, arr = -1;
    for (auto const &i : adj[x])
    {
        if (i.fir != p && sz[i.fir] > best)
        {
            best = sz[i.fir];
            big_child = i.fir;
            arr = i.sec;
        }
    }
    for (auto const &i : adj[x])
    {
        if (i.fir != p && i.fir != big_child)
            dfs(i.fir, x, 0, i.sec);
    }
    if (big_child != -1)
    {
        dfs(big_child, x, 1, arr);
        swap(v[x], v[big_child]);
    }
    v[x].pb(x);
    add(x);
    for (auto const &i : adj[x])
    {
        if (i.fir != p && i.fir != big_child)
        {
            for (auto const &j : v[i.fir])
            {
                v[x].pb(j);
                add(j);
            }
        }
    }
    if (id != -1)
    {
        ans[id] = sum;
    } 
    if (!keep)
    {
        for (auto const &i : v[x])
            rem(i);
    }
}
signed main() 
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
        c2[c[i]]++;
    }
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb({b, i});
        adj[b].pb({a, i});
    }
    dfs_sz(0, -1);
    dfs(0,-1, 0, -1);
    for (int i = 0; i < n - 1; i++) 
        cout << ans[i] << " ";
    cout << endl;
}
// o treco vai ser
// caras da minha subtree
// com caras de fora da minha subtree
// ai passa pela minha aresta
// manter os caras da minha subtree com sack
// ok e o resto?
// preciso saber da questão das cores
// imagina que eu tinha um produto:
// x * y
// vai passar a ser 
// (x - 1) * (y + 1)

// como eu faço essa mudança?