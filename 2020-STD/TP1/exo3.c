#include <stdio.h>
#include <stdlib.h>



void calculInteret(float capital, float taux, int annee)
{
	int i;
	for (i = 0; i < annee; i++)
	{
		capital = (1 + taux) * capital;		
	}

	printf("Capital final apres %d annees est %f \n", annee, capital);

}

void calculDouble(float capital, float taux)
{
	int nb_annee =0;
	float capitaldouble = capital;
	do 
	{
		capitaldouble = (1 + taux) * capitaldouble;
		nb_annee++;	
	} while (capitaldouble < capital * 2);

	printf("Nb_annee = %d \n", nb_annee);
}



int main()
{
	float taux;
	float capital;
	int nb_annee;

	
	printf("capital : ");
	scanf("%f",&capital);

	printf("taux : ");
	scanf("%f",&taux);

	printf("nb_annee : ");
	scanf("%d",&nb_annee);

	taux = taux /100;

	//calculInteret(capital, taux, nb_annee);
	calculDouble(capital, taux);
	

	return 0;
}
