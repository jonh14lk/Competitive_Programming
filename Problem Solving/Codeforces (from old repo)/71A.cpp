#include <bits/stdc++.h>
using namespace std;
 
void loop (int i , int n)
{
	if (i < n)
	{
		char palavra [256];
		scanf(" %s", palavra);
		int tam = strlen (palavra) ;
 
		if (tam > 10)
		{
			printf("%c", palavra[0]);
			printf("%d", tam - 2);
			printf("%c\n", palavra[tam - 1]);
		}
		else printf("%s\n", palavra);
 
		loop (i + 1 , n) ;
	}
}
int main ()
{
	int n ;
	scanf("%d", &n);
 
	loop (0 , n);
	return 0 ;
}
