#include <bits/stdc++.h>

using namespace std;

#define int long long int

const int inf = 1e18;

#define pi pair<int, int>
#define MAXN 100005
int n, m;
vector<pi> adj[MAXN];
bool visited[MAXN];


void dijk2(int s, vector<int>& dist, int g)
 {
    for(int i = 0; i < n; i++) {
        dist[i] = inf;
        visited[i] = false;
    }
    priority_queue<pi, vector<pi>, greater<pi>> q;

    dist[s] = 0;
    q.push({dist[s], s});
    while(!q.empty()) {
        int v = q.top().second;
        if(v == g) continue;
        q.pop();
        if(visited[v]) continue;

        visited[v] = true;
        for(auto const &u : adj[v]) {
            if(u.second == g) continue;
            if(dist[u.second] > dist[v] + u.first) {
                dist[u.second] = dist[v] + u.first;
                q.push({dist[u.second], u.second});
            }
        }
    }
 }


void dijk(int s, vector<int>& dist)
 {
    for(int i = 0; i < n; i++) {
        dist[i] = inf;
        visited[i] = false;
    }
    priority_queue<pi, vector<pi>, greater<pi>> q;

    dist[s] = 0;
    q.push({dist[s], s});
    while(!q.empty()) {
        int v = q.top().second;
        q.pop();
        if(visited[v]) continue;

        visited[v] = true;
        for(auto const &u : adj[v]) {
            if(dist[u.second] > dist[v] + u.first) {
                dist[u.second] = dist[v] + u.first;
                q.push({dist[u.second], u.second});
            }
        }
    }
 }
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    int p, g;
    cin >> p >> g;
    p--; g--;
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[a].push_back({c, b});
        adj[b].push_back({c, a});
    }
    vector<int> d_p(n + 1), d_g(n + 1), dist_sem_g(n + 1);
    dijk(p, d_p);
    dijk(g, d_g);
    dijk2(p, dist_sem_g, g);

    vector<int> ans;
    for(int x = 0; x < n; x++) {
        if(d_g[x] == d_p[g] && d_p[g] + d_g[x] == d_p[x] && dist_sem_g[x] != d_p[x]) ans.push_back(x + 1);
    }
    if(ans.empty()) cout << '*';
    else for(int a : ans) cout << a << " ";
    cout << endl;
}