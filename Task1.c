#include<stdio.h>
#include<malloc.h>

//Ignat Ramona - Inventar

struct Inventar {
	int cod;
	char* denumireProdus;
	int nrProduse;
	float* preturi;
};

struct Inventar citireInventar()
{
	struct Inventar inv;
	printf("Introduceti codul: ");
	scanf("%d", &inv.cod);

	char buffer[100];
	printf("Introduceti denumirea produsului: ");
	scanf(" %[^\n]", buffer);
	inv.denumireProdus = malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy_s(inv.denumireProdus, (strlen(buffer) + 1), buffer);

	printf("Introduceti numarul de produse: ");
	scanf("%d", &inv.nrProduse);

	inv.preturi = malloc(sizeof(float) * inv.nrProduse);
	for (int i = 0; i < inv.nrProduse; i++)
	{
		printf("Introduceti pretul produsului %d", i + 1);
		scanf("%f", &inv.preturi[i]);
	}

	return inv;
}


int main()
{
	struct Inventar inv = citireInventar();

	return 0;
}