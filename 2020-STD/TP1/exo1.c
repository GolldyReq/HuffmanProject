#include <stdio.h>
#include <stdlib.h>



int main()
{
	
	const float POUCE = 2.54;

	float lg;
	char unite;
	float lg_cm, lg_p;

	printf("Entrer une longueur: ");
	scanf("%f",&lg);
	scanf("%c",&unite);
	switch (unite)
	{
		case 'P':
		case 'p':
			lg_p = lg;
			lg_cm = POUCE * lg_p;
			break;	
		case 'C':
		case 'c':
			lg_cm = lg;
			lg_p = lg_cm / POUCE;
			break;
		case 'M':
		case 'm':
			lg_cm = lg * 100;
			lg_p = lg_cm / POUCE;
			break;	
		default:
			lg_p = 0;
			lg_cm = 0;
			break;
	}
	printf("%f p = %f cm\n", lg_p, lg_cm);
	return 0;
}
