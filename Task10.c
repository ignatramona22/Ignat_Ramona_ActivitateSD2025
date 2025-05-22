#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-un arbore binar de cautare
typedef struct Nod Nod;
struct Nod {
	Nod* st;
	Nod* dr;
	Masina info;
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


void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte princiippile de arbore binar de cautare
	//dupa o anumita cheie pe care o decideti - poate fi ID
	if ((*radacina) != NULL) {
		if (masinaNoua.id < (*radacina)->info.id) { // daca e mai mic adaugam la stanga
			adaugaMasinaInArbore(&((*radacina)->st), masinaNoua); // gen dam adresa nodului parinte unde adaugam fiul in arbore
		}
		else if (masinaNoua.id > (*radacina)->info.id) { // daca e mai mare adaugam la dreapta
			adaugaMasinaInArbore(&((*radacina)->dr), masinaNoua);
		}
		else { // daca sunt egale
			if ((*radacina)->info.model) {
				free((*radacina)->info.model);
			}
			if ((*radacina)->info.numeSofer) {
				free((*radacina)->info.numeSofer);
			}
			(*radacina)->info.nrUsi = masinaNoua.nrUsi;
			(*radacina)->info.pret = masinaNoua.pret;
			(*radacina)->info.serie = masinaNoua.serie;
			(*radacina)->info.model = (char*)malloc(strlen(masinaNoua.model) + 1);
			strcpy_s((*radacina)->info.model, strlen(masinaNoua.model) + 1, masinaNoua.model);
			(*radacina)->info.numeSofer = (char*)malloc(strlen(masinaNoua.numeSofer) + 1);
			strcpy_s((*radacina)->info.numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
		}
	}
	else {
		(*radacina) = malloc(sizeof(Nod));
		(*radacina)->info = masinaNoua;
		(*radacina)->info.model = (char*)malloc(strlen(masinaNoua.model) + 1);
		strcpy_s((*radacina)->info.model, strlen(masinaNoua.model) + 1, masinaNoua.model);
		(*radacina)->info.numeSofer = (char*)malloc(strlen(masinaNoua.numeSofer) + 1);
		strcpy_s((*radacina)->info.numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
		(*radacina)->st = NULL;
		(*radacina)->dr = NULL;
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(file)) {
		Masina m = citireMasinaDinFisier(file);
		adaugaMasinaInArbore(&radacina, m);
		free(m.model);
		free(m.numeSofer);
	}
	fclose(file);
	return radacina;
}

void afisareArboreInOrdine(Nod* radacina) {
	if (radacina != NULL) {
		afisareArboreInOrdine(radacina->st);
		afisareMasina(radacina->info);
		afisareArboreInOrdine(radacina->dr);
	}
}

void afisareArborePreOrdine(Nod* radacina) {
	if (radacina != NULL) {
		afisareMasina(radacina->info);
		afisareArborePreOrdine(radacina->st);
		afisareArborePreOrdine(radacina->dr);
	}
}

void dezalocareArboreDeMasini(Nod** radacina) {
	if ((*radacina) != NULL) {
		dezalocareArboreDeMasini(&((*radacina)->st));
		dezalocareArboreDeMasini(&((*radacina)->dr));
		free((*radacina)->info.model);
		free((*radacina)->info.numeSofer);
		free(*radacina);
		*radacina = NULL;
	}
}

Masina getMasinaByID(Nod* radacina, int id) {
	Masina m;
	m.id = -1;
	if (id > radacina->info.id) {
		return getMasinaByID(radacina->dr, id);
	}
	else if (id < radacina->info.id) {
		return getMasinaByID(radacina->st, id);
	}
	else {
		m = radacina->info;
		m.numeSofer = (char*)malloc(strlen(radacina->info.numeSofer) + 1);
		strcpy_s(m.numeSofer, strlen(radacina->info.numeSofer) + 1, radacina->info.numeSofer);
		m.model = (char*)malloc(strlen(radacina->info.model) + 1);
		strcpy_s(m.model, strlen(radacina->info.model) + 1, radacina->info.model);
		return m;
	}
	return m;
}

int determinaNumarNoduri(Nod* radacina) {
	if (radacina != NULL) {
		return 1 + determinaNumarNoduri(radacina->st) + determinaNumarNoduri(radacina->dr);
	}
	return 0;
}



Nod* gasesteMinim(Nod* radacina) {
	while (radacina && radacina->st)
		radacina = radacina->st;
	return radacina;
}

Nod* stergeNod(Nod* radacina, int id) {
	if (radacina == NULL) return NULL;

	if (id < radacina->info.id) {
		radacina->st = stergeNod(radacina->st, id);
	}

	else if (id > radacina->info.id) {
		radacina->dr = stergeNod(radacina->dr, id);
	}

	else {
		// caz cu 0 sau 1 copil
		if (radacina->st == NULL) {
			Nod* temp = radacina->dr;
			free(radacina->info.model);
			free(radacina->info.numeSofer);
			free(radacina);
			return temp;
		}
		else if (radacina->dr == NULL) {
			Nod* temp = radacina->st;
			free(radacina->info.model);
			free(radacina->info.numeSofer);
			free(radacina);
			return temp;
		}

		// caz cu 2 copii
		Nod* minimDr = gasesteMinim(radacina->dr);
		radacina->info = minimDr->info;
		radacina->dr = stergeNod(radacina->dr, minimDr->info.id);
	}
	return radacina;
}



int calculeazaInaltimeArbore(Nod* radacina) {
	if(!radacina) return 0;
	int hSt = calculeazaInaltimeArbore(radacina->st);
	int hDr = calculeazaInaltimeArbore(radacina->dr);
	return 1 + (hSt > hDr ? hSt : hDr);

}

Nod* subarboreCuInaltimeaMaiMare(Nod* radacina) {
	if (!radacina)
		return NULL;
	int hSt = calculeazaInaltimeArbore(radacina->st);
	int hDr = calculeazaInaltimeArbore(radacina->dr);
	return hSt >= hDr ? radacina->st : radacina->dr;
}



Nod* subarboreCuMaiMulteNoduri(Nod* radacina) {
	if (!radacina)
		return NULL;
	int nrSt = determinaNumarNoduri(radacina->st);
	int nrDr = determinaNumarNoduri(radacina->dr);
	return nrSt >= nrDr ? radacina->st : radacina->dr;
}


float calculeazaPretTotal(Nod* radacina) {
	if (radacina == NULL)
		return 0;

	return radacina->info.pret +
		calculeazaPretTotal(radacina->st) +
		calculeazaPretTotal(radacina->dr);
}


float calculeazaPretulMasinilorUnuiSofer(Nod* radacina, const char* numeSofer) {
	if (radacina == NULL)
		return 0;

	float suma = 0;
	if (strcmp(radacina->info.numeSofer, numeSofer) == 0) {
		suma += radacina->info.pret;
	}
	suma += calculeazaPretulMasinilorUnuiSofer(radacina->st, numeSofer);
	suma += calculeazaPretulMasinilorUnuiSofer(radacina->dr, numeSofer);
	return suma;
}


int main() {
	Nod* arbore = citireArboreDeMasiniDinFisier("masini.txt");
	afisareArboreInOrdine(arbore);
	Masina m = getMasinaByID(arbore, 2);
	printf("\n\n-------------------\n");
	afisareMasina(m);

	printf("\n\n-------------------\n");
	int i = determinaNumarNoduri(arbore);
	printf("Nr noduri: %d", i);

	printf("\nSterge nod cu ID 2\n");
	arbore = stergeNod(arbore, 2);
	afisareArboreInOrdine(arbore);

	printf("\nSubarbore cu inaltimea mai mare\n");
	Nod* subInalt = subarboreCuInaltimeaMaiMare(arbore);
	afisareArboreInOrdine(subInalt);

	Nod* subMaiMulte = subarboreCuMaiMulteNoduri(arbore);
	printf("\nSubarbore cu mai multe noduri:\n");
	afisareArboreInOrdine(subMaiMulte);

	float pretTotal = calculeazaPretTotal(arbore);
	printf("\nPret total masini: %.2f\n", pretTotal);

	float pretSofer = calculeazaPretulMasinilorUnuiSofer(arbore, "Gigel");
	printf("Pret masini detinute de Gigel: %.2f\n", pretSofer);



	dezalocareArboreDeMasini(&arbore);
	return 0;
}