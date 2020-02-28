#include <stdio.h>
#include <stdlib.h>



int main()
{
	char caracter;
	char majuscule;
	int decalage;

	printf("Entrer une phrase : ");
	do
	{
		scanf("%c",&caracter);
		if ((caracter >= 'a') && (caracter <='z'))
		{
			decalage = caracter - 'a';
			majuscule = 'A' + decalage;
			printf("%c",majuscule);
		}
		else
		{
			printf("%c",caracter);
		}

	}while (caracter != '.');
	printf("\n");

	return 0;
}
