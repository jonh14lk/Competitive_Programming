#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int 
#define pb push_back 
#define in (int i = 0 ; i < n ; i++)
#define jm (int j = 0 ; j < m ; j++)
 
int main ()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
 
    char str [10000];
    int n ;
    scanf("%d", &n);
    scanf(" %s", str);
 
    for (int i = 0 ; i < strlen(str) ; i++)
    {
        int value ;
 
        if (str[i] == 'A')
        {
            value = 1 ;
        }
        if (str[i] == 'B')
        {
            value = 2 ;
        }
        if (str[i] == 'C')
        {
            value = 3 ;
        }
        if (str[i] == 'D')
        {
            value = 4 ;
        }
        if (str[i] == 'E')
        {
            value = 5;
        }
        if (str[i] == 'F')
        {
            value = 6;
        }
        if (str[i] == 'G')
        {
            value = 7;
        }
        if (str[i] == 'H')
        {
            value = 8;
        }
        if (str[i] == 'I')
        {
            value = 9;
        }
        if (str[i] == 'J')
        {
            value = 10;
        }
        if (str[i] == 'K')
        {
            value = 11;
        }
        if (str[i] == 'L')
        {
            value = 12;
        }
        if (str[i] == 'M')
        {
            value = 13;
        }
        if (str[i] == 'N')
        {
            value = 14;
        }
        if (str[i] == 'O')
        {
            value = 15;
        }
        if (str[i] == 'P')
        {
            value = 16;
        }
        if (str[i] == 'Q')
        {
            value = 17;
        }
        if (str[i] == 'R')
        {
            value = 18;
        }
        if (str[i] == 'S')
        {
            value = 19;
        }
        if (str[i] == 'T')
        {
            value = 20;
        }
        if (str[i] == 'U')
        {
            value = 21;
        }
        if (str[i] == 'V')
        {
            value = 22;
        }
        if (str[i] == 'W')
        {
            value = 23;
        }
        if (str[i] == 'X')
        {
            value = 24;
        }
        if (str[i] == 'Y')
        {
            value = 25;
        }
        if (str[i] == 'Z')
        {
            value = 26;
        }
 
        value = value + n ;
        value--;
 
        if (value % 26 == 0)
        {
            str[i] = 'A';
        }
        if (value % 26 == 1)
        {
            str[i] = 'B';
        }
         if (value % 26 == 2)
        {
            str[i] = 'C';
        }
         if (value % 26 == 3)
        {
            str[i] = 'D';
        }
         if (value % 26 == 4)
        {
            str[i] = 'E';
        }
         if (value % 26 == 5)
        {
            str[i] = 'F';
        }
         if (value % 26 == 6)
        {
            str[i] = 'G';
        }
        if (value % 26 == 7)
        {
            str[i] = 'H';
        }
        if (value % 26 == 8)
        {
            str[i] = 'I';
        }
        if (value % 26 == 9)
        {
            str[i] = 'J';
        }
        if (value % 26 == 10)
        {
            str[i] = 'K';
        }
        if (value % 26 == 11)
        {
            str[i] = 'L';
        }
        if (value % 26 == 12)
        {
            str[i] = 'M';
        }
        if (value % 26 == 13)
        {
            str[i] = 'N';
        }
        if (value % 26 == 14)
        {
            str[i] = 'O';
        }
        if (value % 26 == 15)
        {
            str[i] = 'P';
        }
        if (value % 26 == 16)
        {
            str[i] = 'Q';
        }
        if (value % 26 == 17)
        {
            str[i] = 'R';
        }
        if (value % 26 == 18)
        {
            str[i] = 'S';
        }
        if (value % 26 == 19)
        {
            str[i] = 'T';
        }
        if (value % 26 == 20)
        {
            str[i] = 'U';
        }
        if (value % 26 == 21)
        {
            str[i] = 'V';
        }
        if (value % 26 == 22)
        {
            str[i] = 'W';
        }
        if (value % 26 == 23)
        {
            str[i] = 'X';
        }
        if (value % 26 == 24)
        {
            str[i] = 'Y';
        }
        if (value % 26 == 25)
        {
            str[i] = 'Z';
        }
    }
 
    printf("%s\n", str);
    return 0 ;
}
