#include <bits/stdc++.h>

using namespace std;
#define int long long int
#define fir first
#define sec second
#define pb push_back
#define mod 1000000009
#define pi pair<int, int>
#define MAXN 10005

bool vis[MAXN];
int root[MAXN];
bool is[MAXN];
bool d[MAXN];
bool d2[MAXN];
vector<int> order;
vector<int> comp;
vector<int> adj[MAXN];
vector<int> adj_rev[MAXN];

void dfs(int v)
{
    vis[v] = 1;
    for (auto const &u : adj[v])
    {
        if (!vis[u])
            dfs(u);
    }
    order.pb(v);
}
void dfs2(int v)
{
    comp.pb(v);
    vis[v] = 1;
    for (auto const &u : adj_rev[v])
    {
        if (!vis[u])
            dfs2(u);
    }
}
signed main() 
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj_rev[b].pb(a);
    }
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
            dfs(i);
    }
    reverse(order.begin(), order.end());
    memset(vis, false, sizeof(vis));
    int ans = 0;
    for (auto const &v : order)
    {
        if (!vis[v])
        {
            ans++;
            comp.clear();
            dfs2(v);
        }
        int r = comp.back();
        is[r] = 1;
        for (auto const &u : comp)
        {
            root[u] = r;
        }
    }
    if (ans == 1)
    {
        cout << "0\n";
        return 0;
    }
    for (int v = 0; v < n; v++)
    {
        for (auto const &u : adj[v])
        {
            int ru = root[u];
            int rv = root[v];
            if (rv != ru)
            {
                d[rv] = 1;
                d2[ru] = 1;
            }
        }
    }
    int a = 0, b = 0;
    for (int i = 0; i < n; i++)
    {
        if (is[i])
        {
            if (!d[i])
                a++;
            if (!d2[i])
                b++;
        }
    }
    int c = min(a, b);
    ans = c;
    a -= c;
    b -= c;
    ans += a;
    ans += b;
    cout << ans << endl;
}