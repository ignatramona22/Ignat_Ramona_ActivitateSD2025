#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Farmacie {
	unsigned short int id;
	char* denumire;
	float cifraAfaceri;
	char* farmacistSef;
	unsigned char nrAngajati;
	char* localitate;
};
typedef struct Farmacie Farmacie;

struct Nod {
	Farmacie info;
	struct Nod* st;
	struct Nod* dr;
};

typedef struct Nod Nod;

Farmacie citesteFarmacieDinFisier(FILE* f) {
	char buffer[300];
	char sep[3] = ",\n";
	char* aux;

	// Cite?te o linie din fi?ier
	if (fgets(buffer, sizeof(buffer), f) == NULL) {
		Farmacie gol = { 0, NULL, 0.0f, NULL, 0, NULL };
		return gol;
	}

	Farmacie farmacie;

	// ID
	aux = strtok(buffer, sep);
	farmacie.id = (unsigned short int)atoi(aux);

	// Denumire
	aux = strtok(NULL, sep);
	farmacie.denumire = (char*)malloc(strlen(aux) + 1);
	strcpy(farmacie.denumire, aux);

	// Cifra de afaceri
	aux = strtok(NULL, sep);
	farmacie.cifraAfaceri = (float)atof(aux);

	// Farmacist ?ef
	aux = strtok(NULL, sep);
	farmacie.farmacistSef = (char*)malloc(strlen(aux) + 1);
	strcpy(farmacie.farmacistSef, aux);

	// Num?r angaja?i
	aux = strtok(NULL, sep);
	farmacie.nrAngajati = (unsigned char)atoi(aux);

	// Localitate
	aux = strtok(NULL, sep);
	farmacie.localitate = (char*)malloc(strlen(aux) + 1);
	strcpy(farmacie.localitate, aux);

	return farmacie;
}


void afisareFarmacie(Farmacie farmacie) {
	printf("Id: %hu\n", farmacie.id);
	printf("Denumire %s\n", farmacie.denumire);
	printf("Cifra de Afaceri: %.2f\n", farmacie.cifraAfaceri);
	printf("Farmacist Sef: %s\n", farmacie.farmacistSef);
	printf("Numar angajati: %hhu\n", farmacie.nrAngajati);
	printf("Localitate: %s\n\n", farmacie.localitate);
}

Nod* inserareInABC(Nod* radacina, Farmacie f) {
	if (radacina != NULL) {
		if (radacina->info.id > f.id) {
			radacina->st = inserareInABC(radacina->st, f);
		}
		else
		{
			radacina->dr = inserareInABC(radacina->dr, f);
		}
		return radacina;
	}
	else
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = f;
		nou->st = nou->dr = NULL;
		return nou;
	}
}

Nod* citireABCDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(f))
	{
		radacina = inserareInABC(radacina, citesteFarmacieDinFisier(f));
	}
	fclose(f);
	return radacina;
}

//parcurgeri
//preordine
void afisarePreordine(Nod* radacina) {
	if (radacina != NULL) {
		afisareFarmacie(radacina->info);
		afisarePreordine(radacina->st);
		afisarePreordine(radacina->dr);
	}
}

//inordine
void afisareInordine(Nod* radacina) {
	if (radacina != NULL) {
		afisareInordine(radacina->st);
		afisareFarmacie(radacina->info);
		afisareInordine(radacina->dr);
	}
}
//postordine
void afisarePostordine(Nod* radacina) {
	if (radacina != NULL) {
		afisarePostordine(radacina->st);
		afisarePostordine(radacina->dr);
		afisareFarmacie(radacina->info);
	}
}


void dezalocare(Nod** radacina) {
	if ((*radacina) != NULL) {
		dezalocare(&(*radacina)->st);
		dezalocare(&(*radacina)->dr);
		free((*radacina)->info.denumire);
		free((*radacina)->info.farmacistSef);
		free((*radacina)->info.localitate);
		*radacina = NULL;
	}
}

//functia care determina nrTotal de angajati  la farmaciile dintr-o anumita localitate specificata ca param al functiei
int nrTotalAngajatiLocalitate(Nod* radacina, const char* localitate) {
	if (radacina != NULL) {
		int total = 0;
		if (strcmp(radacina->info.localitate, localitate) == 0) {
			total += radacina->info.nrAngajati;
		}
		total += nrTotalAngajatiLocalitate(radacina->st, localitate);
		total += nrTotalAngajatiLocalitate(radacina->dr, localitate);
		return total;
	}
	return 0;
}

//fct care determina nr cifra de afaceri medie lunara pt o farmacie specificata prin id ca param
float medie(Nod* radacina, unsigned short int idCautat) {
	if (radacina != NULL) {
		if (radacina->info.id == idCautat) {
			return radacina->info.cifraAfaceri / 12.0f;
		}
		if (idCautat < radacina->info.id) {
			return medie(radacina->st, idCautat);
		}
		else
		{
			return medie(radacina->dr, idCautat);
		}
	}
	else
	{
		return 0.0f;
	}
}

Farmacie getFarmacieDupaId(Nod* radacina, unsigned short int id) {
	if (radacina != NULL) {
		if (radacina->info.id == id) {
			Farmacie farmacie;
			farmacie = radacina->info;
			farmacie.denumire = (char*)malloc(strlen(radacina->info.denumire) + 1);
			strcpy_s(farmacie.denumire, strlen(radacina->info.denumire) + 1, radacina->info.denumire);
			farmacie.farmacistSef = (char*)malloc(strlen(radacina->info.farmacistSef) + 1);
			strcpy_s(farmacie.farmacistSef, strlen(radacina->info.farmacistSef) + 1, radacina->info.farmacistSef);
			farmacie.localitate = (char*)malloc(strlen(radacina->info.localitate) + 1);
			strcpy_s(farmacie.localitate, strlen(radacina->info.localitate) + 1, radacina->info.localitate);
			return farmacie;
		}
		else if (radacina->info.id > id) {
			return getFarmacieDupaId(radacina->st, id);
		}
		else
		{
			return getFarmacieDupaId(radacina->dr, id);
		}
	}
	else
	{
		Farmacie gol = { 0, NULL, 0.0f, NULL, 0, NULL };
		return gol;
	}
}

//functia care sterge toate nodurile frunza din structura arborescenta plasate pe un nivel specificat ca parametru al functiei
Nod* stergeNodFrunzaLaNivel(Nod* radacina, int nivelCurent, int nivelTinta) {
	if (radacina != NULL) {
		//daca este nod frunza si se afla pe nivelul specificat
		if (radacina->st == NULL && radacina->dr == NULL && nivelCurent == nivelTinta) {
			free(radacina->info.denumire);
			free(radacina->info.farmacistSef);
			free(radacina->info.localitate);
			free(radacina);
			return NULL;
		}
		else
		{
			//continuam recursiv in arbori
			radacina->st = stergeNodFrunzaLaNivel(radacina->st, nivelCurent + 1, nivelTinta);
			radacina->dr = stergeNodFrunzaLaNivel(radacina->dr, nivelCurent + 1, nivelTinta);
		}
		return radacina;
	}
	else
	{
		return NULL;
	}
}

//functia care salveaza intr-o lista simpla toate valorile de tip id farmacie plasate pe un nivel specificat ca parametru al functiei
struct NodLista {
	unsigned short int id;
	struct NodLista* next;
};

typedef struct NodLista NodLista;

void inserareInLista(NodLista** cap, unsigned short int idFarmacie) {
	NodLista* nou = (NodLista*)malloc(sizeof(NodLista));
	nou->id = idFarmacie;
	nou->next = NULL;
	if (*cap) {
		NodLista* p = *cap;
		while (p->next)
		{
			p = p->next;
		}
		p->next = nou;
	}
	else
	{
		*cap = nou;
	}
}

void salvareIdLaNivel(Nod* radacina, int nivelCurent, int nivelTinta, NodLista** cap) {
	if (radacina != NULL) {
		if (nivelCurent == nivelTinta) {
			inserareInLista(cap, radacina->info.id);
		}
		else
		{
			salvareIdLaNivel(radacina->st, nivelCurent + 1, nivelTinta, cap);
			salvareIdLaNivel(radacina->dr, nivelCurent + 1, nivelTinta, cap);

		}
	}
}

void afisareLista(NodLista* cap) {
	printf("Id-uri de pe nivelul specificat: \n");
	while (cap!=NULL)
	{
		printf("%hu ", cap->id);
		cap = cap->next;
	}
	printf("\n");
}

void dezalocareLista(NodLista** cap) {
	while (*cap)
	{
		NodLista* temp = *cap;
		*cap = (*cap)->next;
		free(temp);
	}
}


int main() {
	Nod* arbore = citireABCDinFisier("farmacie.txt");
	afisareInordine(arbore);

	printf("\n--------\n");
	const char* localitate = "Brasov";
	printf("Nr total angajati din localitatea %s: %d", localitate, nrTotalAngajatiLocalitate(arbore, localitate));


	printf("\n--------\n");
	unsigned short int idCautat = 142;
	float medieLunara = medie(arbore, idCautat);
	printf("\nFarmacie cu id-ul %hu are o medie lunare a cifrei de afaceri de: %.2f", idCautat, medieLunara);

	printf("\n--------\n");
	int  nivelTinta = 3;
	printf("\nStergere noduri frunza\n");
	arbore = stergeNodFrunzaLaNivel(arbore, 0, nivelTinta);
	afisareInordine(arbore);

	printf("\n--------\n");
	printf("\nFarmacia cu id-ul 121\n");
	Farmacie f = getFarmacieDupaId(arbore, 121);
	afisareFarmacie(f);

	printf("\n--------\n");
	printf("\nSalvarea in lista\n");
	int nivel = 2;
	NodLista* lista = NULL;
	salvareIdLaNivel(arbore, 0, nivel, &lista);
	afisareLista(lista);
	dezalocareLista(&lista);
	dezalocare(&arbore);


	return 0;
}