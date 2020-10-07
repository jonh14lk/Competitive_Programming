#include <bits/stdc++.h>
using namespace std;
 
int main ()
{
	char string [256];
	scanf(" %s", string);
	int i ;
	int tam = strlen(string);
 
	for (i = 0 ; i < tam ; i++)
	{
		if(tolower(string[i]) != 'a' && tolower(string[i]) != 'o' && tolower(string[i]) != 'y' && tolower(string[i]) != 'e' && tolower(string[i]) != 'u' && tolower(string[i]) != 'i') 
			{
				printf(".");
				printf("%c", tolower(string[i])) ;
			}
	}
 
	printf("\n");
	return 0 ;
}
