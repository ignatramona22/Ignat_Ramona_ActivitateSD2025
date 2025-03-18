#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
#include <string.h>

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
	scanf_s("%d", &inv.cod);

	char buffer[100];
	printf("Introduceti denumirea produsului: ");
	scanf_s(" %[^\n]", buffer, (unsigned int)sizeof(buffer));

	inv.denumireProdus = malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy_s(inv.denumireProdus, (strlen(buffer) + 1), buffer);

	printf("Introduceti numarul de produse: ");
	scanf_s("%d", &inv.nrProduse);

	inv.preturi = malloc(sizeof(float) * inv.nrProduse);
	for (int i = 0; i < inv.nrProduse; i++)
	{
		printf("Introduceti pretul produsului %d: ", i + 1);
		scanf_s("%f", &inv.preturi[i]);
	}

	return inv;
}


float calculMediePreturi(struct Inventar inv)
{
	float suma = 0;
	for (int i = 0; i < inv.nrProduse; i++)
	{
		suma += inv.preturi[i];
	}
	return suma / inv.nrProduse;
}

void modificareNumarProduse(struct Inventar* inv, int _nrProduse)
{
	inv->nrProduse = _nrProduse;
	inv->preturi = realloc(inv->preturi, sizeof(float) * _nrProduse);
	printf("Noul numar de produse este: %d", inv->nrProduse);
}

void afisareInventar(struct Inventar inv)
{
	printf("\nInventar:\n");
	printf("Cod: %d\n", inv.cod);
	printf("Denumire produs: %s\n", inv.denumireProdus);
	printf("Numar produse: %d\n", inv.nrProduse);
	printf("Preturi:");
	for (int i = 0; i < inv.nrProduse; i++)
	{
		printf("%.2f ", inv.preturi[i]);
	}
	printf("\n");
}

void afisareVectorInventar(struct Inventar* vector, int dim)
{
	for (int i = 0; i < dim; i++)
	{
		afisareInventar(vector[i]);
	}
}

//Functie care creeaza un nou vector cu obiectele ce au mai mult de 5 produse
struct Inventar* filtrareProduseDinInv(struct Inventar* vector, int dim, int* dimNoua)
{
	struct Inventar* inventar = malloc(sizeof(struct Inventar) * dim);
	*dimNoua = 0;
	for (int i = 0; i < dim; i++)
	{
		if (vector[i].nrProduse > 5)
		{
			inventar[*dimNoua] = vector[i];
			(*dimNoua)++;
		}
		
	}
	return inventar;
}

//functie care muta intr-un nou vector obiectele cu pretul mediu > 20
struct Inventar* mutaPreturiMari(struct Inventar* vector, int* dim, int* dimNoua)
{
	struct Inventar* inventar = malloc(sizeof(struct Inventar) * (*dim));
	*dimNoua = 0;
	for (int i = 0; i < *dim; i++)
	{
		float suma = 0;
		for (int j = 0; j < vector[i].nrProduse; j++)
		{
			suma += vector[i].preturi[j];
		}
		
		float medie = suma / vector[i].nrProduse;

		if (medie > 20)
		{
			inventar[*dimNoua] = vector[i];
			(*dimNoua)++;
		}
	}

}

//functie care concateneaza doi vectori
struct Inventar* concateneazaVectori(struct Inventar* v1, int dim1, struct Inventar* v2, int dim2, int* dimNoua)
{
	*dimNoua = dim1 + dim2;
	struct Inventar* inventar = malloc(sizeof(struct Inventar) * (*dimNoua));

	for (int i = 0; i < dim1; i++)
	{
		inventar[i] = v1[i];
	}
	for (int i = 0; i < dim2; i++)
	{
		inventar[i] = v2[i];
	}

	return inventar;
}

void dezalocare(struct Inventar** vector, int* nrElemente) {
	for (int i = 0; i < *nrElemente; i++)
	{
		free((*vector)[i].denumireProdus);
		free((*vector)[i].preturi);
	}

	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

//Scrieti intr-un program C functia care sa citeasca obiectele din fisier si sa le salveze intr-un vector
void adaugaInventarInVector(struct Inventar** inventare, int* nrInventare, struct Inventar inventarNou)
{
	struct Inventar* aux = (struct Inventar*)malloc(sizeof(struct Inventar) * ((*nrInventare) + 1));
	for (int i = 0; i < *nrInventare; i++)
	{
		aux[i] = (*inventare)[i];
	}
	aux[(*nrInventare)] = inventarNou;
	free(*inventare);
	(*inventare) = aux;
	(*nrInventare)++;
}

struct Inventar citireInventarDinFisier(FILE* file)
{
	struct Inventar inv;

	char buffer[200];
	char separator[] = ",;\n";
	fgets(buffer, 100, file);

	//int
	char* token = strtok(buffer, separator);
	inv.cod = atoi(token);
	//char*
	token = strtok(NULL, separator);
	inv.denumireProdus = (char*)malloc(strlen(token) + 1);
	strcpy(inv.denumireProdus, token);

	token = strtok(NULL, separator);
	inv.nrProduse = atoi(token);

	//float*
	inv.preturi = (float*)malloc(sizeof(float) * inv.nrProduse);
	for (int i = 0; i < inv.nrProduse; i++)
	{
		token = strtok(NULL, separator);
		inv.preturi[i] = atof(token);
	}

	return inv;
}
struct Inventar* citireVectorInventareFisier(const char* numeFisier, int* nrInventareCitite) {
	FILE* file = fopen(numeFisier, "r");
	if (!file) {
		printf("Eroare la deschiderea fisierului!\n");
		return NULL;
	}

	struct Inventar* inventare = NULL;
	*nrInventareCitite = 0;

	char buffer[200];
	while (fgets(buffer, sizeof(buffer), file)) { 
		struct Inventar inv = citireInventarDinFisier(file);
		adaugaInventarInVector(&inventare, nrInventareCitite, inv);
	}

	fclose(file);
	return inventare;
}


//Scrieti o functie care va salva un obiect  intr-un fisier text.

//Scrieti o functie care va salva un vector de obiecte intr-un fisier text. 


int main()
{
	FILE* file = fopen("inventare.txt", "r");
	struct Inventar inv = citireInventarDinFisier(file);
	afisareInventar(inv);

	int nrInventare = 0;
	struct Inventar* inv1 = citireVectorInventareFisier("inventare.txt", &nrInventare);
	afisareVectorInventar(inv1, nrInventare);
	dezalocare(&inv1, &nrInventare);

	return 0;
}