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
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

//creare structura pentru un nod dintr-o lista dublu inlantuita
struct Nod {
	Masina info;
	Nod* next;
	Nod* prev;
};

//creare structura pentru Lista Dubla 
struct ListaDubla
{
	Nod* cap;
	Nod* coada;
	int nrNoduri;
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


void afisareListaMasini(ListaDubla lista) {
	Nod* temp = lista.cap;
	while (temp)
	{
		afisareMasina(temp->info);
		temp = temp->next;
	}
}

void afisareListaMasiniDeLaFinal(ListaDubla lista) {
	Nod* temp = lista.coada;
	while (temp)
	{
		afisareMasina(temp->info);
		temp = temp->prev;
	}
}
void adaugaMasinaInLista(ListaDubla* lista, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	nou->prev = lista->coada;

	if (lista->cap == NULL) {
		lista->cap = nou;
	}
	else {
		lista->coada->next = nou;
	}

	lista->coada = nou;
	lista->nrNoduri++;
}

void adaugaLaInceputInLista(ListaDubla* lista, Masina masinaNoua) {
	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->prev = NULL;
	nou->next = lista->cap;

	if (lista->cap == NULL) {
		lista->coada = nou;
	}
	else
	{
		lista->cap->next = nou;
	}
}

ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {	
	FILE* file = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.cap = NULL;
	lista.coada = NULL;
	lista.nrNoduri = 0;

	if (!file) return lista;

	while (!feof(file))
	{	
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(file));
	}

	fclose(file);
	return lista;
}

void dezalocareLDMasini(ListaDubla* lista) {
	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
	Nod* temp;
	while (lista->cap)
	{
		temp = lista->cap;
		lista->cap = lista->cap->next;
		free(temp->info.model);
		free(temp->info.numeSofer);
		free(temp);
	}
	lista->coada = NULL;
	lista->cap = NULL;
	lista->nrNoduri = 0;
}

float calculeazaPretMediu(ListaDubla lista) {
	//calculeaza pretul mediu al masinilor din lista.
	float suma = 0;
	Nod* temp = lista.cap;

	while (temp)
	{
		suma += temp->info.pret;
		temp = temp->next;
	}

	return suma / lista.nrNoduri;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(ListaDubla lista) {

	Nod* temp = lista.cap;
	Nod* maxim = lista.cap;
	while (temp)
	{
		if (temp->info.pret > maxim->info.pret) {
			maxim = temp;
		}

		temp = temp->next;
	}
	
	char* numeSoferC = malloc(sizeof(char) * (strlen(maxim->info.numeSofer) + 1));
	strcpy_s(numeSoferC, (strlen(maxim->info.numeSofer) + 1), maxim->info.numeSofer);
	return numeSoferC;
}

void stergeNodPePozitie(ListaDubla* lista, int pozitie) {
	Nod* temp = lista->cap;

	//nodul de pe prima pozitie
	if (pozitie == 0) {
		lista->cap = temp->next;
		if (lista->cap) {
			lista->cap->prev = NULL;
		}
	}
	else
	{
		for (int i = 0; i < pozitie; i++) {
			temp = temp->next;
		}

		//nod intermediar sau ultimul
		if (temp->prev) {
			temp->prev->next = temp->next;
		}
		if (temp->next) {
			temp->next->prev = temp->prev;
		}
	}

	if (temp == lista->coada) {
		lista->coada = temp->prev;
	}

	free(temp->info.model);
	free(temp->info.numeSofer);
	free(temp);
	lista->nrNoduri--;
}
void adaugaMasinaSortata(ListaDubla* lista, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	// Ini?ializare nod nou
	nou->info.id = masinaNoua.id;
	nou->info.nrUsi = masinaNoua.nrUsi;
	nou->info.pret = masinaNoua.pret;
	nou->info.serie = masinaNoua.serie;
	nou->info.model = malloc(strlen(masinaNoua.model) + 1);
	if (nou->info.model == NULL) exit(1);
	strcpy(nou->info.model, masinaNoua.model);

	nou->info.numeSofer = malloc(strlen(masinaNoua.numeSofer) + 1);
	if (nou->info.numeSofer == NULL) exit(1);
	strcpy(nou->info.numeSofer, masinaNoua.numeSofer);

	nou->next = NULL;
	nou->prev = NULL;

	// daca lista este goala
	if (lista->cap == NULL) {
		lista->cap = lista->coada = nou;
	}
	else {
		Nod* temp = lista->cap;

		// inserare la inceputul listei 
		if (temp->info.pret >= masinaNoua.pret) {
			nou->next = lista->cap;
			lista->cap->prev = nou;
			lista->cap = nou;
		}
		else {
			// mijlocul sau finalul listei
			while (temp->next && temp->next->info.pret < masinaNoua.pret) {
				temp = temp->next;
			}

			// la final
			if (temp->next == NULL) {
				lista->coada->next = nou;
				nou->prev = lista->coada;
				lista->coada = nou;
			}
			// la mijloc
			else {
				nou->next = temp->next;
				nou->prev = temp;
				temp->next->prev = nou;
				temp->next = nou;
			}
		}
	}

	lista->nrNoduri++;
}


int main() {

	ListaDubla lista;
	lista.cap = NULL;
	lista.coada = NULL;
	lista = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasini(lista);

	printf("\nPRETUL MEDIU AL MASINILOR: %.2f", calculeazaPretMediu(lista));

	printf("\nSoferul care are cea mai scumpa masin este: %s\n", getNumeSoferMasinaScumpa(lista));

	printf("\nLista dupa stergerea masinii de pe pozitia 1\n");
	stergeNodPePozitie(&lista, 1);
	afisareListaMasini(lista);

	printf("\nInserare masina in lista sortata crescator dupa pret\n");
	Masina m = { 11, 4, 13000.3, "Break", "Ramona", 'Z'};
	adaugaMasinaSortata(&lista, m);
	afisareListaMasini(lista);

	printf("\nParcurgerea listei sortate crescator\n");
	afisareListaMasini(lista);

	printf("\nParcurgerea listei sortate descrescator\n");
	afisareListaMasiniDeLaFinal(lista);

	dezalocareLDMasini(&lista);

	return 0;
}