#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500009
#define mod 1000000001

vector<int> v = {2, 3, 4, 5, 6};
unordered_map<int, bool> vis;
unordered_map<int, int> dp;

int g(int x) // achar o grundy number na marra
{
    if (x == 0)
        return 0;
    vector<bool> ok(4, 0);
    int mex = 0;
    for (auto const &i : v)
    {
        int curr = g(x / i);
        if (curr < 4)
            ok[curr] = 1;
        while (ok[mex])
            mex++;
    }
    vis[x] = 1;
    return dp[x] = mex;
}
int solve(int x) // padraozin
{
    vector<int> ini = {0, 1, 2, 2, 3, 3, 0, 0, 0, 0, 0, 0};
    while (x >= 12)
        x /= 12;
    return ini[x];
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin >> q;
    while (q--)
    {
        int n;
        cin >> n;
        int x = 0;
        for (int i = 0; i < n; i++)
        {
            int k;
            cin >> k;
            x ^= solve(k);
        }
        (x > 0) ? cout << "Henry\n" : cout << "Derek\n";
    }
    return 0;
}
/*
game theory (um exemplo simples de problema pra ficar no repo)

- pro nim classico
- existem n pilhas cada uma possui x[i] blocos
- em uma play posso escolher uma pilha e tirar uma quantidade qualquer de blocos dela
- quem ganha?
- o jogador que começa ganha se o xor dos tamanhos das pilhas for != 0

- teorema sprague-grundy (transformar um jogo qualquer em nim)
- seja v um estado que eu tou do jogo, podemos calcular o grundy number desse estado
- seja o conjuntos de estados adjacentes a v {u1, u2, ..., un}
- g(v) = mex(g(u1), g(u2), ..., g(un))
- se v não tem nenhum extado adjacente, então g(v) = 0
- g(v) -> grundy number do estado v
- com isso se tivemos varios estados iniciais (varias pilhas)
- podemos simplesmente achar o grundy number de cada um deles e depois saber quem ganha
- pelo valor do xor dos grundy numbers

- exemplo: floor division game
- existem n numeros e em uma play posso escolher um deles e dividir por 2, 3, 4, 5 ou 6
- quem ganha?
- achar o grundy number de cada um dos n numeros
- se o xor for != 0, ganha quem começa jogando
- caso contrário, o outro jogador ganha

- as vzs é util tbm ver se existe um padrão (em caso de altas constantes)
- notando o padrão, da pra achar o grundy number de forma mais eficiente e resolver o problema
*/