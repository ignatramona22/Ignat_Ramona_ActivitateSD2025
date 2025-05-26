#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

Farmacie citesteFarmacieDinFisier(FILE* file) {
	char buffer[300];
	char sep[3] = ",\n";
	fgets(buffer, 300, file);
	char* aux;

	Farmacie farmacie;
	aux = strtok(buffer, sep);
	farmacie.id = (unsigned short int)atoi(aux);

	aux = strtok(NULL, sep);
	farmacie.denumire = (char*)malloc(strlen(aux) + 1);
	strcpy_s(farmacie.denumire, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	farmacie.cifraAfaceri = (float)atof(aux);

	aux = strtok(NULL, sep);
	farmacie.farmacistSef = (char*)malloc(strlen(aux) + 1);
	strcpy_s(farmacie.farmacistSef, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	farmacie.nrAngajati = (unsigned char)atoi(aux);

	aux = strtok(NULL, sep);
	farmacie.localitate = (char*)malloc(strlen(aux) + 1);
	strcpy_s(farmacie.localitate, strlen(aux) + 1, aux);
	
	return farmacie;
}

void afisareFarmacie(Farmacie f) {
	printf("\nId: %hu\n", f.id);
	printf("Denumire: %s\n", f.denumire);
	printf("Cifra afaceri: %.2f\n", f.cifraAfaceri);
	printf("Frmacist sef: %s\n", f.farmacistSef);
	printf("Nr angajati %hhu\n", f.nrAngajati);
	printf("Localitate: %s\n", f.localitate);
}

int calculInaltime(Nod* radacina) {
	if (radacina != NULL) {
		int inaltimeST = calculInaltime(radacina->st);
		int inaltimeDR = calculInaltime(radacina->dr);
		return 1 + (inaltimeST > inaltimeDR ? inaltimeST : inaltimeDR);
	}
	else
	{
		return 0;
	}
}

int gradEchilibru(Nod* radacina) {
	if (radacina != NULL) {
		return calculInaltime(radacina->st) - calculInaltime(radacina->dr);
	}
	else
	{
		return 0;
	}
}

Nod* rotireStanga(Nod* radacina) {
	if (radacina != NULL) {
		Nod* aux = radacina->dr;
		radacina->dr = aux->st;
		aux->st = radacina;
		return aux;
	}
	else
	{
		return NULL;
	}
}

Nod* rotireDreapta(Nod* radacina) {
	if (radacina != NULL) {
		Nod* aux = radacina->st;
		radacina->st = aux->dr;
		aux->dr = radacina;
		return aux;
	}
	else
	{
		return NULL;
	}
}

Nod* inserareInAVL(Nod* radacina, Farmacie f) {
	if (radacina != NULL) {
		if (radacina->info.id > f.id) {
			radacina->st = inserareInAVL(radacina->st, f);
		}
		else
		{
			radacina->dr = inserareInAVL(radacina->dr, f);
		}

		//dezechilibru stanga
		if (gradEchilibru(radacina) == 2) {
			if (gradEchilibru(radacina->st) != 1) {
				radacina->st = rotireStanga(radacina->st);
			}
			radacina = rotireDreapta(radacina);
		}

		//dezechilibru dreapta
		if (gradEchilibru(radacina) == -2) {
			if (gradEchilibru(radacina->dr) != -1) {
				radacina->dr = rotireDreapta(radacina->dr);
			}
			radacina = rotireStanga(radacina);
		}
		return radacina;
	}
	else
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = f;
		nou->dr = nou->st = NULL;
		return nou;
	}
}

Nod* citesteAVLDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(f)) {
		radacina = inserareInAVL(radacina, citesteFarmacieDinFisier(f));
	}
	fclose(f);
	return radacina;
}

void afisareInordine(Nod* radacina) {
	if (radacina != NULL) {
		afisareInordine(radacina->st);
		afisareFarmacie(radacina->info);
		afisareInordine(radacina->dr);
	}
}

//det nr noduri
int nrTotalNoduri(Nod* radacina) {
	if (radacina != NULL) {
		return 1 + nrTotalNoduri(radacina->st) + nrTotalNoduri(radacina->dr);
	}
	else
	{
		return 0;
	}
}
// calculeaza total cifra afaceri arbore
float totalCA(Nod* radacina) {
	if (radacina != NULL) {
		float totalST = totalCA(radacina->st);
		float totalDR = totalCA(radacina->dr);
		return totalST + totalDR + radacina->info.cifraAfaceri;
	}
	else
	{
		return 0.0f;
	}
}
////functia care determina nrTotal de angajati  la farmaciile dintr-o anumita localitate specificata ca param al functiei
int totalAngajati(Nod* radacina, const char* localitate) {
	if (radacina != NULL) {
		int total = 0;
		if (strcmp(radacina->info.localitate, localitate) == 0) {
			total += radacina->info.nrAngajati;
		}
		total += totalAngajati(radacina->st, localitate);
		total += totalAngajati(radacina->dr, localitate);
	}
	else
	{
		return 0;
	}
}
////fct care determina nr cifra de afaceri medie lunara pt o farmacie specificata prin id ca param
float medieCALunara(Nod* radacina, unsigned short int id) {
	if (radacina != NULL) {
		if (radacina->info.id == id) {
			return radacina->info.cifraAfaceri / 12.0f;
		}
		else if (radacina->info.id > id) {
			return medieCALunara(radacina->st, id);
		}
		else
		{
			medieCALunara(radacina->dr, id);
		}
	}
	else {
		return 0.0f;
	}

}
//get farmacie dupa id
Farmacie getFarmacieByID(Nod* radacina, unsigned short int id) {
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
			return getFarmacieByID(radacina->st, id);
		}
		else
		{
			return getFarmacieByID(radacina->st, id);
		}
	}
	else
	{
		Farmacie gol = { 0, NULL, 0.0f, NULL, 0, NULL };
		return gol;
	}
}
////functia care sterge toate nodurile frunza din structura arborescenta plasate pe un nivel specificat ca parametru al functiei
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
////functia care salveaza intr-o lista simpla toate valorile de tip id farmacie plasate pe un nivel specificat ca parametru al functiei
struct NodLista {
	unsigned short int id;
	struct NodLista* next;
};
typedef struct NodLista NodLista;

void inserareInLSLaInceput(Nod** cap, unsigned short int id) {
	NodLista* nou = (Nod*)malloc(sizeof(Nod));
	nou->id = id;
	nou->next = *cap;
	*cap = nou;
}

void inserareInLSLaSfarsit(Nod** cap, unsigned short int id) {
	NodLista* nou = (Nod*)malloc(sizeof(Nod));
	nou->id = id;
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

void salvareInLSLaNivel(Nod* radacina, NodLista** cap, int nivelCurent, int nivelTinta) {
	if (radacina != NULL) {
		if (nivelCurent == nivelTinta) {
			inserareInLSLaSfarsit(cap, radacina->info.id);
		}
		else
		{
			salvareInLSLaNivel(radacina->st, cap, nivelCurent + 1, nivelTinta);
			salvareInLSLaNivel(radacina->dr, cap, nivelCurent + 1, nivelTinta);
		}
	}
}

void afisareLista(NodLista* cap) {
	printf("ID-urile de pe nivelul specificat\n");
	while (cap)
	{
		printf("%hu ", cap->id);
		cap = cap->next;
	}
}

void dezalocareLista(NodLista** cap) {
	while ((*cap)!=NULL)
	{
		NodLista* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}
void dezalocare(Nod** radacina) {
	if ((*radacina) != NULL) {
		dezalocare(&(*radacina)->st);
		dezalocare(&(*radacina)->dr);
		free((*radacina)->info.denumire);
		free((*radacina)->info.farmacistSef);
		free((*radacina)->info.localitate);
	}
}
int main() {
	Nod* arbore = citesteAVLDinFisier("farmacie.txt");
	afisareInordine(arbore);

	printf("\nTotal noduri arbore: %d", nrTotalNoduri(arbore));
	printf("\nTotal cifra afaceri din arbore: %.2f", totalCA(arbore));
	printf("\nTotal angajati din Brasov: %d", totalAngajati(arbore, "Brasov"));
	unsigned short int idCautat = 142;
	float medieCA = medieCALunara(arbore, idCautat);
	printf("\nCifra de afaceri medie lunara a farmaciei cu id-ul %hu este: %.2f\n", idCautat, medieCA);

	printf("\n--Farmacia cu id-ul 142");
	Farmacie f = getFarmacieByID(arbore, 142);
	afisareFarmacie(f);

	

	printf("\nSalvare in LS\n");
	NodLista* cap = NULL;
	salvareInLSLaNivel(arbore, &cap, 0, 3);
	afisareLista(cap);

	printf("\nStergere frunze nivel 3\n");
	int nivel = 3;
	arbore = stergeNodFrunzaLaNivel(arbore, 0, nivel);
	if (arbore) {
		afisareInordine(arbore);
	}
	else
	{
		printf("\nPe nivelul %d nu exita noduri frunza", nivel);
	}
	return 0;

}