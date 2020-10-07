#include <bits/stdc++.h>
using namespace std;

void loop (int i , int t)
{
    if (i < t)
    {
        int n , x , y , l ;
        scanf("%d%d%d", &n , &x , &y);
        int array [n] ;

        for (l = 0 ; l < n ; l++) scanf("%d", &array[l]);

        if (array[0] == x && array[n - 1] == y) printf("BOTH\n");
        else if (array[0] == x && array[n - 1] != y) printf("EASY\n");
        else if (array[0] != x && array[n - 1] == y) printf("HARD\n");
        else if (array[0] != x && array[n - 1] != y) printf("OKAY\n");

        loop (i + 1 , t);
    }
}
int main ()
{
    int t ;
    scanf("%d", &t);

    loop (0 , t);
    return 0 ;
}
