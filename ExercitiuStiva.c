#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//STIVA - LIFO
struct Comanda {
	int id;
	char* numeClient;
	int nrProduse;
	float sumaDePlata;
};
typedef struct Comanda Comanda;

struct NodStiva {
	Comanda info;
	struct NodStiva* next;
};
typedef struct NodStiva NodStiva;

Comanda citesteComandaDinFisier(FILE* f) {
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	fgets(buffer, 100, f);

	Comanda comanda;
	aux = strtok(buffer, sep);
	comanda.id = (int)atoi(aux);

	aux = strtok(NULL, sep);
	comanda.numeClient = (char*)malloc(strlen(aux) + 1);
	strcpy_s(comanda.numeClient, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	comanda.nrProduse = (int)atoi(aux);

	aux = strtok(NULL, sep);
	comanda.sumaDePlata = (float)atof(aux);

	return comanda;
}

void afiseazaComanda(Comanda comanda) {
	printf("\nID: %d", comanda.id);
	printf("\nNume client: %s", comanda.numeClient);
	printf("\nNumar produse: %d", comanda.nrProduse);
	printf("\nSuma de plata: %.2f\n", comanda.sumaDePlata);
}

//Implementati functia de inserare a unei comenzi intr-o structura de tip Stiva
void pushStackLaInceput(NodStiva** stiva, Comanda comanda) {
	NodStiva* nou = (NodStiva*)malloc(sizeof(NodStiva));
	nou->info = comanda;
	nou->next = (*stiva);
	(*stiva) = nou;
}

NodStiva* citesteStivaDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	NodStiva* stiva = NULL;
	while (!feof(f))
	{
		pushStackLaInceput(&stiva, citesteComandaDinFisier(f));
	}
	fclose(f);
	return stiva;
}

//Functia de traversare a structurii de tip stiva
void afiseazaStiva(NodStiva* stiva) {
	while (stiva!=NULL)
	{
		afiseazaComanda(stiva->info);
		stiva = stiva->next;
	}
}

int stackSize(NodStiva* stiva) {
	int nr = 0;
	while (stiva!=NULL)
	{
		nr++;
		stiva = stiva->next;
	}
	return nr;
}

//Functia care extrage cu stergere si returnare un nod din stiva
Comanda popStack(NodStiva** stiva) {
	if ((*stiva != NULL)) {
		Comanda nou = (*stiva)->info;
		NodStiva* aux = (*stiva);
		(*stiva) = (*stiva)->next;
		free(aux);
		return nou;
	}
	Comanda m;
	m.id = -1;
	return m;
}

//Implementati functia care determina toate comenzile a caror suma de plata depaseste valoarea de 100 si le salveaza intr-un vector alocat dinamin
//Vectorul este sortat descrescator dupa nr de produse si este afisat la consola.
int comparaComenziDupaNrProduse(const void* a, const void* b) {
	Comanda* c1 = (Comanda*)a;
	Comanda* c2 = (Comanda*)b;
	return c2->nrProduse - c1->nrProduse;
}

Comanda* filtreazaSiSorteazaComenzi(NodStiva* stiva, int* dim) {
	int count = 0;
	NodStiva* aux = stiva;

	while (aux) //prima parcurgere: numaram comenzile > 100
	{
		if (aux->info.sumaDePlata > 100) {
			count++;
		}
		aux = aux->next;
	}
	if (count > 0) {
		Comanda* vector = (Comanda*)malloc(sizeof(Comanda) * count);
		int i = 0;
		aux = stiva;

		//a doua parcurgere: copiem comenzile eligibile
		while (aux)
		{
			if (aux->info.sumaDePlata > 100) {
				vector[i].id = aux->info.id;
				vector[i].nrProduse = aux->info.nrProduse;
				vector[i].sumaDePlata = aux->info.sumaDePlata;
				vector[i].numeClient = (char*)malloc(strlen(aux->info.numeClient) + 1);
				strcpy_s(vector[i].numeClient, strlen(aux->info.numeClient) + 1, aux->info.numeClient);
				i++;
			}
			aux = aux->next;
		}

		//sortam descrescator dupa nr prod
		qsort(vector, count, sizeof(Comanda), comparaComenziDupaNrProduse);
		*dim = count;
		return vector;
	}
	else
	{
		*dim = 0;
		return NULL;
	}
}

unsigned char emptyStack(NodStiva** stiva) {
	return (*stiva == NULL);
}

void dezalocareStiva(NodStiva** stiva) {
	while ((*stiva) != NULL)
	{
		Comanda c = popStack(stiva);
		free(c.numeClient);
	}
}


int main() {
	NodStiva* stiva = citesteStivaDinFisier("comenzi.txt");
	afiseazaStiva(stiva);

	printf("\nNumar elemente din stiva: %d\n", stackSize(stiva));
	printf("\nComanda extrasa:");
	Comanda c = popStack(&stiva);
	afiseazaComanda(c);
	free(c.numeClient);

	printf("\nStiva de comenzi dupa extragere");
	afiseazaStiva(stiva);


	int nrComenzi;
	Comanda* vectorC = filtreazaSiSorteazaComenzi(stiva, &nrComenzi);
	if (vectorC) {
		printf("\nComenzi cu suma > 100, sortate descrescator dupa nrProduse:\n");
		for (int i = 0; i < nrComenzi; i++) {
			afiseazaComanda(vectorC[i]);
		}
		for (int i = 0; i < nrComenzi; i++) {
			free(vectorC[i].numeClient);
		}
		free(vectorC);
	}
	else {
		printf("\nNu exista comenzi cu suma de plata > 100.\n");
	}

	if (emptyStack(&stiva)) {
		printf("Stiva este goala.\n");
	}
	else
	{
		printf("Stiva nu este goala\n");
	}

	dezalocareStiva(&stiva);
	return 0;
}