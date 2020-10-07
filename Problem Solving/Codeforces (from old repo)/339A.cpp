#include <bits/stdc++.h>
using namespace std;
 
int main ()
{
    vector <int> v ;
    int i , x ;
    char lixo ;
 
    while(scanf("%d", &x) != EOF)
    {
        scanf(" %c", &lixo);
        v.push_back(x);
 
        if (lixo != '+') break;
    }
 
    sort(v.begin(), v.end());
 
    for (i = 0 ; i < v.size() ; i++)
    {
        if (i == 0)  printf("%d", v[i]);
        else printf("+%d", v[i]);
    }

    return 0 ;
}
