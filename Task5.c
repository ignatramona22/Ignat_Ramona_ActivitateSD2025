#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

typedef struct StructuraMasina Masina;
typedef struct Nod Nod;

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};

struct Nod
{
	Masina info;
	Nod* next;
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
	m1.pret= atof(strtok(NULL, sep));
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

void afisareListaMasini(Nod* cap) {
	while (cap != NULL)
	{
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;

	if ((*cap) == NULL)
	{
		*cap = nou;
	}
	else 
	{
		Nod* p = *cap;
		while (p->next)
		{
			p = p->next;
		}
		p->next = nou;
	}
	
}

void adaugaLaInceputInLista(Nod** cap,  Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = *cap;
	*cap = nou;
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while (!feof(f))
	{
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(f)); //daca am fi facut deep copy ar fi trebuit sa stergem aici 
	}
	fclose(f);
	return lista;
}

void dezalocareListaMasini(Nod** cap) {
	while (*cap!=NULL)
	{
		Nod* aux = (*cap);
		(*cap) = (*cap)->next;
		free(aux->info.model);
		free(aux->info.numeSofer);
		free(aux);
	}
}

float calculeazaPretMediu(Nod* lista) {
	//calculeaza pretul mediu al masinilor din lista.
	if (!lista) return 0;

	int count = 0;
	float suma = 0;
	while (lista)
	{
		suma += lista->info.pret;
		count++;
		lista = lista->next;
	}
	
	if (count > 0)
	{
		return suma / count;
	}
	else
	{
		return 0;
	}
}

void stergeMasiniDinSeria(Nod** cap,  const char* serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie


	while ((*cap) != NULL && (*cap)->info.serie == serieCautata)
	{
		Nod* p = (*cap);
		(*cap) = (*cap)->next;
		free(p->info.model);
		free(p->info.numeSofer);
		free(p);
	}


	Nod* p = (*cap);
	while ( p !=NULL)
	{
		while (p->next && p->next->info.serie != serieCautata)
		{
			p = p->next;
		}
		if (p->next!= NULL)
		{
			Nod* temp = p->next;
			p->next = temp->next;
			free(temp->info.model);
			free(temp->info.numeSofer);
			free(temp);
		}
		else
		{
			p = p->next;
		}
	}


}

float calculeazaPretulMasinilorUnuiSofer(Nod* lista, const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	if (!lista) return 0;

	float suma = 0;
	while (lista)
	{
		if (strcmp(lista->info.numeSofer, numeSofer) == 0)
		{
			suma += lista->info.pret;
		}
		lista = lista->next;
	}

	return suma;
}

void stergeNodPePozitie(Nod** cap, int pozitie) {
	if (*cap == NULL || pozitie < 0) return NULL;

	//Caz 1 - stergem primul nod
	Nod* temp = *cap;
	if (pozitie == 0) {
		*cap = temp->next;
		free(temp->info.model);
		free(temp->info.numeSofer);
		free(temp);
		return;
	}

	//Caz 2 - stergem un nod intermediar sau final
	Nod* p = *cap;
	int index = 0;
	while (p!=NULL)
	{
		while (p->next && index + 1 != pozitie) {
			p = p->next;
			index++;
		}
		if (p->next != NULL) {
			Nod* temp = p->next;
			p->next = temp->next;
			free(temp->info.model);
			free(temp->info.numeSofer);
			free(temp);
			return;
		}
		else
		{
			p = p->next;
		}
	}
}

int main() {
	Nod* lista = NULL;
	lista = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(lista);

	printf("\n=== Stergere nod de pe pozitia 1 ===\n");
	stergeNodPePozitie(&lista, 1);
	afisareListaMasini(lista);

	dezalocareListaMasini(&lista);
	return 0;
}