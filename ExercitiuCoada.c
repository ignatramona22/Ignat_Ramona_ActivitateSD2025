#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//COADA - FIFO
struct Comanda {
	int id;
	char* numeClient;
	int nrProduse;
	float sumaDePlata;
};
typedef struct Comanda Comanda;

struct NodCoada {
	Comanda info;
	struct NodCoada* next;
};
typedef struct NodCoada NodCoada;

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

//Functia de inserare a unei comenzi intr-o structura Coada
void enqueue(NodCoada** coada, Comanda comanda) {
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->info = comanda;
	nou->next = NULL;
	if ((*coada)) {
		NodCoada* p = (*coada);
		while (p->next)
		{
			p = p->next;
		}
		p->next = nou;
	}
	else
	{
		(*coada) = nou;
	}
}

NodCoada* citesteCoada(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	NodCoada* coada = NULL;
	while (!feof(f))
	{
		enqueue(&coada, citesteComandaDinFisier(f));
	}
	fclose(f);
	return coada;
}

void afisareCoada(NodCoada* coada) {
	while (coada!=NULL)
	{
		afiseazaComanda(coada->info);
		coada = coada->next;
	}
}
Comanda dequeue(NodCoada** coada) {
	if ((*coada) != NULL) {
		Comanda nou = (*coada)->info;
		NodCoada* aux = (*coada);
		(*coada) = (*coada)->next;
		free(aux);
		return nou;
	}
	else
	{
		Comanda gol = { 0, " ", 0, 0.0 };
		return gol;
	}
}

void dezalocareCoada(NodCoada** coada) {
	while ((*coada)!=NULL)
	{
		Comanda c = dequeue(coada);
		free(c.numeClient);
	}
}

Comanda getComandaByID(NodCoada* coada, int id) {
	while (coada!=NULL)
	{
		if (coada->info.id == id) {
			Comanda c;
			c.id = coada->info.id;
			c.nrProduse = coada->info.nrProduse;
			c.sumaDePlata = coada->info.sumaDePlata;
			c.numeClient = (char*)malloc(strlen(coada->info.numeClient) + 1);
			strcpy_s(c.numeClient, strlen(coada->info.numeClient) + 1, coada->info.numeClient);
			return c;
		}
		coada = coada->next;
	}
	Comanda gol = { 0, NULL, 0, 0.0 };
	return gol;
}

float calculeazaSumaTotala(NodCoada** coada) {
	float suma = 0;
	NodCoada* aux = NULL;
	while ((*coada)!=NULL)
	{
		Comanda c = dequeue(coada);
		suma += c.sumaDePlata;
		enqueue(&aux, c);
	}
	(*coada) = aux;
	return suma;
}

////Implementati functia care determina toate comenzile a caror suma de plata depaseste valoarea de 100 si le salveaza intr-un vector alocat dinamin
////Vectorul este sortat descrescator dupa nr de produse si este afisat la consola.
int comparaComenziDupaNrProduse(const void* a, const void* b) {
	Comanda* c1 = (Comanda*)a;
	Comanda* c2 = (Comanda*)b;
	return c2->nrProduse - c1->nrProduse;
}

Comanda* filtreazaSiSorteazaComenzi(NodCoada* coada, int *dim) {
	int count = 0;
	NodCoada* aux = coada;
	while (aux)
	{
		if (aux->info.sumaDePlata > 100) {
			count++;
		}
		aux = aux->next;
	}

	if (count > 0) {
		Comanda* vector = (Comanda*)malloc(sizeof(Comanda) * count);
		int i = 0;
		aux = coada;
		while(aux)
		{
			if (aux->info.sumaDePlata > 100) {
				vector[i].id = aux->info.id;
				vector[i].numeClient = (char*)malloc(strlen(aux->info.numeClient) + 1);
				strcpy_s(vector[i].numeClient, strlen(aux->info.numeClient) + 1, aux->info.numeClient);
				vector[i].nrProduse = aux->info.nrProduse;
				vector[i].sumaDePlata = aux->info.sumaDePlata;
				i++;
			}
			aux = aux->next;
		}
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

int main() {
	NodCoada* coada = citesteCoada("comenzi.txt");
	afisareCoada(coada);

	Comanda c = dequeue(&coada);
	printf("\nComanda extrasa\n");
	afiseazaComanda(c);

	int idCautat = 1010;
	printf("\nComanda cu ID-ul %d", idCautat);
	afiseazaComanda(getComandaByID(coada, idCautat));

	printf("\nSuma totala: %.2f\n", calculeazaSumaTotala(&coada));


	printf("\nComenzi filtrate");
	int dim;
	Comanda* vector = filtreazaSiSorteazaComenzi(coada, &dim);
	if (vector) {
		for (int i = 0; i < dim; i++) {
			afiseazaComanda(vector[i]);
		}
		for (int i = 0; i < dim; i++) {
			free(vector[i].numeClient);
		}
		free(vector);
	}
	else {
				printf("\nNu exista comenzi cu suma de plata > 100.\n");
			}
	
	dezalocareCoada(&coada);
	return 0;
}