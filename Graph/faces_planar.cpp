#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 100005
#define mod 998244353

struct pt
{
    int x, y;
    pt() {}
    pt(int x_, int y_) : x(x_), y(y_) {}
    bool operator<(const pt p) const
    {
        if (x != p.x)
            return x < p.x;
        return y < p.y;
    }
    bool operator==(const pt p) const
    {
        return x == p.x and y == p.y;
    }
    pt operator+(const pt p) const { return pt(x + p.x, y + p.y); }
    pt operator-(const pt p) const { return pt(x - p.x, y - p.y); }
    pt operator*(const int c) const { return pt(x * c, y * c); }
    int operator*(const pt p) const { return x * (int)p.x + y * (int)p.y; }
    int operator^(const pt p) const { return x * (int)p.y - y * (int)p.x; }
    int cross(const pt &p) const
    {
        return x * p.y - y * p.x;
    }
    int cross(const pt &p, const pt &q) const
    {
        return (p - *this).cross(q - *this);
    }
    int half() const
    {
        return (y < 0 || (y == 0 && x < 0));
    }
};

// se o ponto ta dentro do poligono: retorna 0 se ta fora,
// 1 se ta no interior e 2 se ta na borda
// vale para poligono simples
int inpol(vector<pt> &v, pt p) // O(n)
{
    int qt = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (p == v[i])
            return 2;
        int j = (i + 1) % v.size();
        if (p.y == v[i].y and p.y == v[j].y)
        {
            if ((v[i] - p) * (v[j] - p) <= 0)
                return 2;
            continue;
        }
        bool baixo = v[i].y < p.y;
        if (baixo == (v[j].y < p.y))
            continue;
        auto t = (p - v[i]) ^ (v[j] - v[i]);
        if (!t)
            return 2;
        if (baixo == (t > 0))
            qt += baixo ? 1 : -1;
    }
    return qt != 0;
}
// acha as faces do grafo planar
// dado o grafo planar
// e a localizacao (x, y) de cada vertice do grafo
vector<vector<int>> find_faces(vector<pt> vertices, vector<vector<int>> adj)
{
    int n = vertices.size();
    vector<vector<char>> used(n);
    for (int i = 0; i < n; i++)
    {
        used[i].resize(adj[i].size());
        used[i].assign(adj[i].size(), 0);
        auto compare = [&](int l, int r)
        {
            pt pl = vertices[l] - vertices[i];
            pt pr = vertices[r] - vertices[i];
            if (pl.half() != pr.half())
                return pl.half() < pr.half();
            return pl.cross(pr) > 0;
        };
        sort(adj[i].begin(), adj[i].end(), compare);
    }
    vector<vector<int>> faces;
    for (int i = 0; i < n; i++)
    {
        for (int edge_id = 0; edge_id < adj[i].size(); edge_id++)
        {
            if (used[i][edge_id])
            {
                continue;
            }
            vector<int> face;
            int v = i;
            int e = edge_id;
            while (!used[v][e])
            {
                used[v][e] = true;
                face.push_back(v);
                int u = adj[v][e];
                int e1 = lower_bound(adj[u].begin(), adj[u].end(), v, [&](int l, int r)
                                     {
                    pt pl = vertices[l] - vertices[u];
                    pt pr = vertices[r] - vertices[u];
                    if (pl.half() != pr.half())
                        return pl.half() < pr.half();
                    return pl.cross(pr) > 0; }) -
                         adj[u].begin() + 1;
                if (e1 == adj[u].size())
                {
                    e1 = 0;
                }
                v = u;
                e = e1;
            }
            reverse(face.begin(), face.end());
            pt p1 = vertices[face[0]];
            __int128 sum = 0;
            for (int j = 0; j < face.size(); ++j)
            {
                pt p2 = vertices[face[j]];
                pt p3 = vertices[face[(j + 1) % face.size()]];
                sum += (p2 - p1).cross(p3 - p2);
            }
            if (sum <= 0)
            {
                faces.insert(faces.begin(), face);
            }
            else
            {
                faces.emplace_back(face);
            }
        }
    }
    return faces;
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    assert(m <= (4 * n));
    vector<pt> vv(n);
    for (int i = 0; i < n; i++)
    {
        cin >> vv[i].x >> vv[i].y;
    }
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    auto faces = find_faces(vv, adj);
    int qq;
    cin >> qq;
    vector<pt> qry(qq);
    for (int i = 0; i < qq; i++)
    {
        cin >> qry[i].x >> qry[i].y;
    }
    string ans(qq, 'G');
    for (auto const &f : faces)
    {
        vector<pt> curr(f.size());
        for (int i = 0; i < f.size(); i++)
        {
            curr[i].x = vv[f[i]].x;
            curr[i].y = vv[f[i]].y;
        }
        for (int i = 0; i < qq; i++)
        {
            if (ans[i] == 'G')
            {
                if (inpol(curr, qry[i]) == 1)
                    ans[i] = 'P';
            }
        }
    }
    cout << ans << endl;
    return 0;
}
// https://codeforces.com/gym/106598/problem/F
// o grafo tem que ser planar pela definicao
// entao o numero de edges eh O(m)
// entao n e m sao pequenos