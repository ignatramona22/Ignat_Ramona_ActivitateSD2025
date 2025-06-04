#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

typedef struct NodListaPrincipala NodListaPrincipala;
typedef struct NodListaSecundara  NodListaSecundara;

struct NodListaPrincipala {
	NodListaPrincipala* next;
	NodListaSecundara* vecini;
	Masina info;

};

struct NodListaSecundara {
	NodListaPrincipala* info;
	NodListaSecundara* next;
};


Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//1. 
// structuri necesare
//dorim stocarea unui graf intr-o lista de liste
//astfel avem nod ListaPrincipala si NodListaSecundara



//2.
//functii de inserare in liste
//si in principala si in secundara
NodListaPrincipala* inserareListaPrincipala(NodListaPrincipala* cap, Masina info)
{
	NodListaPrincipala* nou = (NodListaPrincipala*)malloc(sizeof(NodListaPrincipala));
	nou->info = info;
	nou->vecini = NULL;
	nou->next = NULL;

	if (!cap) return nou;

	NodListaPrincipala* p = cap;
	while (p->next)p = p->next;
	p->next = nou;
	return cap;
}

NodListaSecundara* inserareListaSecundara(NodListaSecundara* cap, NodListaPrincipala* info)
{
	NodListaSecundara* nou = (NodListaSecundara*)malloc(sizeof(NodListaSecundara));
	nou->info = info;
	nou->next = NULL;

	nou->next = cap;
	return nou;

}
//3.
//functie de cautarea in lista principala dupa ID
NodListaPrincipala* cautaNodDupaID(NodListaPrincipala* listaPrincipala, int id) {
	while (listaPrincipala && listaPrincipala->info.id != id) {
		listaPrincipala = listaPrincipala->next;
	}
	return listaPrincipala;
	
}

//4.
//inserare muchie
void inserareMuchie(NodListaPrincipala* listaPrincipala, int idStart, int idStop) {
	NodListaPrincipala* nodStart = cautaNodDupaID(listaPrincipala, idStart);
	NodListaPrincipala* nodStop = cautaNodDupaID(listaPrincipala, idStop);
	if (nodStart && nodStop) {
		nodStart->vecini = inserareListaSecundara(nodStart->vecini, nodStop);
		nodStop->vecini = inserareListaSecundara(nodStop->vecini, nodStart);
	}
}


NodListaPrincipala* citireNoduriMasiniDinFisier(const char* numeFisier) {
	NodListaPrincipala* listaPrincipala = NULL;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		inserareListaPrincipala(listaPrincipala, citireMasinaDinFisier(f));
	}
	fclose(f);
	return listaPrincipala;
}

void citireMuchiiDinFisier(NodListaPrincipala* listaPrincipala, const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		int idStart;
		int idStop;
		fscanf(f, "%d %d", &idStart, &idStop);
		inserareMuchie(listaPrincipala, idStart, idStop);
	}
	fclose(f);
}

void stergereListaSecundara(NodListaSecundara** cap) {
	NodListaSecundara* aux;
	while ((*cap)) {
		aux = (*cap)->next;
		free((*cap));
		(*cap) = aux;
	}
}

void dezalocareNoduriGraf(NodListaPrincipala** listaPrincipala) {
	NodListaPrincipala* aux;
	while ((*listaPrincipala)) {
		aux = (*listaPrincipala)->next;
		stergereListaSecundara(&(*listaPrincipala)->vecini);
		if ((*listaPrincipala)->info.model) {
			free((*listaPrincipala)->info.model);
		}
		if ((*listaPrincipala)->info.numeSofer) {
			free((*listaPrincipala)->info.numeSofer);
		}
		free(*listaPrincipala);
		(*listaPrincipala) = aux;
	}
}


//Parcurgere in adancime.......................................................................................................
//creare structura Stiva
//push si pop pentru stiva
struct Stiva {
	int id;
	struct Stiva* next;
};
typedef struct Stiva Stiva;

void push(Stiva** cap, int idNou) {
	Stiva* nodStivaNoud = (Stiva*)malloc(sizeof(Stiva));
	nodStivaNoud->id = idNou;
	nodStivaNoud->next = (*cap);
	(*cap) = nodStivaNoud;
}

int popStiva(Stiva** cap) {
	Stiva* temp = (*cap);
	if (*cap) {
		*cap = (*cap)->next;
		int id = temp->id;
		free(temp);
		return id;
	}
	else
	{
		return -1;
	}
}
int calculeazaNrNoduriGraf(NodListaPrincipala* listaPrincipala) {
	int count = 0;
	while (listaPrincipala)
	{
		count++;
		listaPrincipala = listaPrincipala->next;
	}
	return count;
}
void afisareGrafInAdancime(NodListaPrincipala* listaPrincipala, int idPlecare) {
	Stiva* stiva = NULL;
	int nrNoduri = calculeazaNrNoduriGraf(listaPrincipala);
	int* vizitate = (int*)malloc(sizeof(int) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++){
		vizitate[i] = 0;
	}
	vizitate[idPlecare - 1] = 1;
	push(&stiva, idPlecare);
	while (stiva)
	{

		int idCurent = popStiva(&stiva);
		NodListaPrincipala* nodCurent = cautaNodDupaID(listaPrincipala, idCurent);
		afisareMasina(nodCurent->info);
		NodListaSecundara* p = nodCurent->vecini;
		while (p)
		{
			if (vizitate[p->info->info.id - 1] == 0) {

				push(&stiva, p->info->info.id);
				vizitate[p->info->info.id - 1] = 1;
			}
			p = p->next;

		}

	}

}


//Parcurgere in latime
void enqueue(Stiva** cap, int id) {
	Stiva* nou= (Stiva*)malloc(sizeof(Stiva));
	nou->id = id;
	nou->next = NULL;
	if (*cap) {
		Stiva* p = (*cap);
		while (p->next)
		{
			p = p->next;
		}
		p->next = nou;
	}
	else
	{
		(*cap) = nou;
	}
}

int dequeue(Stiva** cap)
{
	Stiva* temp = (*cap);
	if (*cap) {
		*cap = (*cap)->next;
		int id = temp->id;																																												
		free(temp);
		return id;
	}
	else
	{
		return -1;
	}
}
//creare structura coada
//enqueue si dequeue pentru coada

void afisareGrafInLatime(NodListaPrincipala* listaPrincipala, int idPlecare) {
	Stiva* stiva = NULL;
	int nrNoduri = calculeazaNrNoduriGraf(listaPrincipala);
	int* vizitate = (int*)malloc(sizeof(int) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	vizitate[idPlecare - 1] = 1;
	enqueue(&stiva, idPlecare);
	while (stiva)
	{

		int idCurent = dequeue(&stiva);
		NodListaPrincipala* nodCurent = cautaNodDupaID(listaPrincipala, idCurent);
		afisareMasina(nodCurent->info);
		NodListaSecundara* p = nodCurent->vecini;
		while (p)
		{
			if (vizitate[p->info->info.id - 1] == 0) {

				enqueue(&stiva, p->info->info.id);
				vizitate[p->info->info.id - 1] = 1;
			}
			p = p->next;

		}

	}
}


int main() {
	NodListaPrincipala* graf = citireNoduriMasiniDinFisier("masini.txt");
	citireMuchiiDinFisier(graf, "muchii.txt");
	afisareGrafInAdancime(graf, 1);
	dezalocareNoduriGraf(&graf);
	return 0;
}