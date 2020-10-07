#include <bits/stdc++.h>
using namespace std;
 
int main ()
{
	int peso , i , j , status = 0;
	scanf("%d", &peso);
 
	for (j = 1 ; j < peso ; j++)
	{
		for (i = peso - 1 ; i > 0 ; i--)
		{
			if (j % 2 == 0 && i % 2 == 0 && j + i == peso) status = 1;
		}
	}
 
	(status == 1) ? printf("YES\n") : printf("NO\n");
	return 0 ;
}
